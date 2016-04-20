//
// Created by F8LEFT on 2016/4/18.
//

#include <assert.h>
#include "ElfReader.h"
#include <fstream>

//-------------Error handler------------
bool silentHandler(const ElfReader &reader, ElfReader::errcode_t code, ...) {
    return true; // resume after warnings
}

//与混淆对抗的handler，会对内存中的so文件进行一定程度上的修复
bool obfuseHandler(const ElfReader &reader, ElfReader::errcode_t code, ...) {
    return true;
}

void ElfReader::setHandler(bool (*_handler)(const ElfReader &, errcode_t, ...)) {
    handle_error = _handler == NULL ? silentHandler : _handler;
}

//----------------Elf Reader --------------------------
bool ElfReader::parseFromMem(u1 *mem, u4 len) {
    if (reader.fromMem(mem, len)) {
        return parseElf();
    }
    return false;
}

bool ElfReader::parseFromFile(const char *fileName) {
    if (reader.fromFile(fileName)) {
        return parseElf();
    }
    return false;
}

bool ElfReader::parseElf() {

    return true;
}

bool ElfReader::readIdent() {
    u4 bytesLeft = reader.size();
    reader.seekg(0);

    if (bytesLeft < sizeof(ident)) {
        return false;
    }

    ident = (elf_ident_t *) reader.seekg(0);

    if (!isValid()) {
        return false;
    }

    size_t ehdrsize = is64() ? sizeof(Elf64_Ehdr) : sizeof(Elf32_Ehdr);
    if (bytesLeft < ehdrsize) {
        return false;
    }

    if (!is64()) {
        stdsizes.ehdr = sizeof(Elf32_Ehdr);
        stdsizes.phdr = sizeof(Elf32_Phdr);
        stdsizes.shdr = sizeof(Elf32_Shdr);
        stdsizes.entries.sym = sizeof(Elf32_Sym);
        stdsizes.entries.dyn = sizeof(Elf32_Dyn);
        stdsizes.entries.rel = sizeof(Elf32_Rel);
        stdsizes.entries.rela = sizeof(Elf32_Rela);
        stdsizes.types.elf_addr = 4;
        stdsizes.types.elf_off = 4;
        stdsizes.types.elf_xword = 4;
        stdsizes.types.elf_sxword = 4;
    } else {
        stdsizes.ehdr = sizeof(Elf64_Ehdr);
        stdsizes.phdr = sizeof(Elf64_Phdr);
        stdsizes.shdr = sizeof(Elf64_Shdr);
        stdsizes.entries.sym = sizeof(Elf64_Sym);
        stdsizes.entries.dyn = sizeof(Elf64_Dyn);
        stdsizes.entries.rel = sizeof(Elf64_Rel);
        stdsizes.entries.rela = sizeof(Elf64_Rela);
        stdsizes.types.elf_addr = 8;
        stdsizes.types.elf_off = 8;
        stdsizes.types.elf_xword = 8;
        stdsizes.types.elf_sxword = 8;
    }
    stdsizes.dyn.sym = stdsizes.entries.sym;
    stdsizes.dyn.rel = stdsizes.entries.rel;
    stdsizes.dyn.rela = stdsizes.entries.rela;
    return true;
}

bool ElfReader::readHeader() {
    if (!is64()) {
        Elf32_Ehdr *et = (Elf32_Ehdr *) reader.seekg(0);
        return readHeader(et);
    } else {
        Elf64_Ehdr * et = (Elf64_Ehdr *) reader.seekg(0);
        return readHeader(et);
    }
}


bool ElfReader::readSectionHeader() {
    u4 sec = getSectionOff();
    if (!sec) return false;
    assert(phdrs.get() != NULL);
    if (!is64()) {
        Elf32_Shdr *st = (Elf32_Shdr *) reader.seekg(sec);
        Elf32_Phdr *pt = phdrs.get()->_32;
        return readSectionHeader(ehdr._32, st, pt);
    } else {
        Elf64_Shdr *st = (Elf64_Shdr *) reader.seekg(sec);
        Elf64_Phdr *pt = phdrs.get()->_64;
        return readSectionHeader(ehdr._64, st, pt);
    }
}

bool ElfReader::readProgramheader() {
    u4 sec = getProgramOff();
    if (!sec) return false;
    if (!is64()) {
        Elf32_Phdr *phdrStart = (Elf32_Phdr *) reader.seekg(sec);
        return readProgramheader(ehdr._32, phdrStart);
    } else {
        Elf64_Phdr *phdrStart = (Elf64_Phdr *) reader.seekg(sec);
        return readProgramheader(ehdr._64, phdrStart);
    }
}


template<typename ehdrx>
#ifdef BPROC
bool ElfReader::readHeader(ehdrx *header) {
#else
bool ElfReader::readHeader(ehdrx *header1) {
    Elf32_Ehdr *header;
#endif
    ehdr.p = header;
    if (header->e_ehsize != stdsizes.ehdr) {
        if (!handle_error(*this, BAD_EHSIZE, header->e_ehsize, stdsizes.ehdr)) {
            return false;
        }
    }
    // Sanitize SHT string table index
    if (header->e_shstrndx && header->e_shstrndx >= header->e_shnum) {
        if (!handle_error(*this, BAD_SHSTRNDX, header->e_shstrndx, header->e_shnum)) {
            return false;
        }
    }
    // Sanitize PHT parameters
    if (header->e_phnum && header->e_phentsize != stdsizes.phdr) {
        if (!handle_error(*this, BAD_PHENTSIZE, header->e_phentsize, stdsizes.phdr)) {
            return false;
        }
    }
    if ((header->e_phnum == 0) != (header->e_phoff == 0)) {
        if (!handle_error(*this, BAD_PHLOC, header->e_phnum, header->e_phoff)) {
            return false;
        }
    }

    // Sanitize SHT parameters
    if (header->e_shnum != 0 && header->e_shentsize != stdsizes.shdr) {
        if (!handle_error(*this, BAD_SHENTSIZE, header->e_shentsize, stdsizes.shdr)) {
            return false;
        }
    }
    u4 sections_start = header->e_shoff;
    u4 sections_finish = header->e_shoff + header->e_shnum * header->e_shentsize;
    if ((header->e_shnum == 0) != (header->e_shoff == 0)
        || sections_start > sections_finish
        || sections_finish > reader.size()) {
        if (!handle_error(*this, BAD_SHLOC, header->e_shnum, header->e_shoff, reader.size())) {
            return false;
        }
    }

    if (header->e_phnum && header->e_type == ET_REL) {
        if (!handle_error(*this, CONFLICTING_FILE_TYPE, header->e_phnum, header->e_type)) {
            return false;
        }
    }
    return true;
}


u4 ElfReader::getSectionOff() {
    if (!is64()) {
        return ehdr._32->e_shoff;
    } else {
        return ehdr._64->e_shoff;
    }
}

u4 ElfReader::getProgramOff() {
    if (!is64()) {
        return ehdr._32->e_phoff;
    } else {
        return ehdr._64->e_phoff;
    }
}


template<typename ehdrx, typename shdrx, typename phdrx>
#ifdef BPROC
bool ElfReader::readSectionHeader(ehdrx *ehdr, shdrx shdr, phdrx phdr) {
#else
bool ElfReader::readSectionHeader(ehdrx *ehdr1, shdrx shdr1, phdrx phdr1) {
    Elf32_Ehdr *ehdr;
    Elf32_Shdr *shdr;
    Elf32_Phdr *phdr;
#endif
    decltype(shdr) pShdr = shdr;

    u4 count = ehdr->e_shnum;

    shdrs.reset(new shdr_t[count], [](shdr_t*p) { delete[]p; });
    shdr_t *st = shdrs.get();
    for (int i = 0; i < count; ++i) {
        st->p = pShdr;      //Addresss
        pShdr = (decltype(pShdr))((u1*)pShdr + stdsizes.shdr);
        st++;
    }

    return true;
}

template<typename ehdrx, typename phdrx>
#ifdef BPROC
bool ElfReader::readProgramheader(ehdrx *ehdr, phdrx *phdr) {
#else
bool ElfReader::readProgramheader(ehdrx *ehdr1, phdrx *phdr1) {
    Elf32_Ehdr *ehdr;
    Elf32_Phdr *phdr;
#endif
    decltype(phdr) pPhdr = phdr;
    u4 count = ehdr->e_phnum;
    phdrs.reset(new phdr_t[count], [](phdr_t* p) { delete[]p; });
    phdr_t* pt = phdrs.get();
    for (int i = 0; i < count; ++i) {
        pt->p = pPhdr;      //Addresss
        pPhdr = (decltype(pPhdr))((u1*)pPhdr + stdsizes.phdr);
        pt++;
    }
    return true;
}


int ElfReader::readEndian(void *buf, int size) {
    return reader.safeRead(buf, size, isMsb());
}

int ElfReader::readAddr(void *buf) {
    return readEndian(buf, stdsizes.types.elf_addr);
}

int ElfReader::readOff(void *buf) {
    return readEndian(buf, stdsizes.types.elf_off);
}

int ElfReader::readXword(void *buf) {
    return readEndian(buf, stdsizes.types.elf_xword);
}

int ElfReader::readSxword(void *buf) {
    return readEndian(buf, stdsizes.types.elf_sxword);
}

int ElfReader::readWord(u4 *buf) {
    return readEndian(buf, 4);
}

int ElfReader::readHalf(u2 *buf) {
    return readEndian(buf, 4);
}

int ElfReader::readByte(u1 *buf) {
    return readEndian(buf, 4);
}

bool ElfReader::isValid() {
    if (ident == NULL) {
        return false;
    }
    if (ident->magic != ELF_MAGIC) return false;
    if (ident->bytesex != ELFDATA2LSB && ident->bytesex != ELFDATA2MSB) {
        return false;
    }
    if (ident->elf_class != ELFCLASS64 && ident->elf_class != ELFCLASS32) {
        return false;
    }
    return true;
}

















