//
// Created by F8LEFT on 2016/4/18.
//

#ifndef ELFREADER_ELFREADER_H
#define ELFREADER_ELFREADER_H

#include "elfbase.h"
#include <iostream>
#include <string>
#include <c++/memory>
#include "MemReader.h"

using namespace std;

class ElfReader {
public:
    enum errcode_t {
/*
		* The "class" of the ELF module is not properly defined. It
		* should really be one of (ELFCLASS32, ELFCLASS64).
		* We will fallback to the ELFCLASS32 class.
		*   - uint8: the ELF class, as defined in the file.
		*/
                BAD_CLASS = 1,

        /*
        * The size of the ELF header conflicts with what was expected.
        *   - uint16: the size of the ELF header, as defined in the file
        *             (i.e., eh_ehsize)
        *   - uint16: the expected size.
        */
                BAD_EHSIZE,

        /*
        * The byte ordering is not properly defineed. It should
        * really be one of (ELFDATA2LSB, ELFDATA2MSB).
        * We will fallback to the ELFDATA2LSB ordering.
        *   - uint8: the byte ordering, as defined in the file.
        */
                BAD_ENDIANNESS,

        /*
        * The ELF module defines there are Program Header entries,
        * but it defines an entry size to be of an odd size.
        * We will fallback to the default size for program header
        * entries, which depends on the "class" of this ELF module.
        *   - uint16: the size of a program header entry, as defined in
        *     the file.
        *   - uint16: the expected size (to which we will fallback).
        */
                BAD_PHENTSIZE,

        /*
        * The ELF module either:
        * 1) defines an offset for the Program Header entries data but a
        *    count of 0 entries, or
        * 2) defines no offset for the Program Header entries data but a
        *    count of 1+ entries.
        * We will set the program header entries count to 0.
        *   - uint16: the number of entries, as defined in the file.
        *   - uint64: the offset for the entries data.
        */
                BAD_PHLOC,

        /*
        * The ELF module defines there are Section Header entries,
        * but it defines an entry size to be of an odd size.
        * We will fallback to the default size for section header
        * entries, which depends on the "class" of this ELF module.
        *   - uint16: the size of a section header entry, as defined in
        *     the file.
        *   - uint16: the expected size (to which we will fallback).
        */
                BAD_SHENTSIZE,

        /*
        * The ELF module:
        * 1) defines an offset for the Section Header entries data but a
        *    count of 0 entries, or
        * 2) defines no offset for the Section Header entries data but a
        *    count of 1+ entries, or
        * 3) defines too many entries, which would cause an EOF to occur
        *    while reading those.
        * We will set the section header entries count to 0.
        *   - uint16: the number of entries, as defined in the file.
        *   - uint64: the offset for the entries data.
        *   - int32 : the size of the file.
        */
                BAD_SHLOC,

        /*
        * The reader has encountered an unhandled section.
        *   - uint16     : The index of the section header.
        *   - Elf64_Shdr*: A pointer to the section header structure.
        * If handled, this notification should return a
        * "unhandled_section_handling_t", specifying how the
        * reader should proceed with it.
        */
                UNHANDLED_SECHDR,

        /*
        * The reader has encountered an unhandled section,
        * which even the reader instance user couldn't handle.
        *   - uint16     : The index of the section header.
        *   - Elf64_Shdr*: A pointer to the section header structure.
        */
                UNKNOWN_SECHDR,

        /*
        * The reader has spotted that the section's address
        * in memory (i.e., sh_addr) is not aligned on the
        * specified alignment (i.e., sh_addralign).
        *   - uint16     : The index of the section header.
        *   - Elf64_Shdr*: A pointer to the section header structure.
        */
                BAD_SECHDR_ALIGN,

        /*
        * The section header 0 is supposed to be SHT_NULL. But it wasn't.
        */
                BAD_SECHDR0,

        /*
        * The type of file (e_type) appears to be ET_CORE, and the
        * machine is SPARC. Those files usually have wrong SHT's. We
        * will rather opt for the PHT view.
        */
                USING_PHT_SPARC_CORE,

        /*
        * TLS definitions occured more than once in the file.
        */
                EXCESS_TLS_DEF,

        /*
        * The section with the given name is being redefined.
        *   - const char *: The name of the section
        */
                SECTION_REDEFINED,

        /*
        * While parsing the dynamic_info_t, the reader spotted
        * an invalid value for the DT_PLTREL entry.
        *   - uint32: The 'value' of that entry.
        */
                BAD_DYN_PLT_TYPE,

        /*
        * One of the symbols in the symbols tables has a bad binding.
        *   - unsigned char: The binding.
        */
                BAD_SYMBOL_BINDING,

        /*
        * The ELF module has a Section Header String Table index, but
        * it is out-of-bounds.
        *   - uint16: the section header string table index (i.e., e_shstrndx).
        *   - uint16: the number of section header entries (i.e., e_shnum).
        */
                BAD_SHSTRNDX,

        /*
        * The ELF module has Program Header entries, which means it's
        * ready to be loaded as a process image, but claims it is of
        * type ET_REL which makes it a relocatable object file.
        *   - uint16: the number of program header entries (i.e., e_phnum).
        *   - uint16: the type of the ELF module (i.e., e_type).
        */
                CONFLICTING_FILE_TYPE,

        LAST_WARNING = CONFLICTING_FILE_TYPE,

        /*
        * Couldn't read as many bytes as required.
        * This is a fatal issue, and should be treated as such.
        *  - size_t: expected bytes.
        *  - size_t: actually read.
        *  - int32 : position in file when reading was initiated.
        */
                ERR_READ,

        LAST_ERROR = ERR_READ
    };

    struct {
        u4 ehdr;
        u4 phdr;
        u4 shdr;

        struct {
            u4 sym;
            u4 dyn;
            u4 rel;
            u4 rela;
        } entries;

        struct {
            u4 sym;     //DT_SYMENT
            u4 rel;     //DT_RELENT
            u4 rela;    //DT_RELAENT
        } dyn;

        struct {
            u4 elf_addr;
            u4 elf_off;
            u4 elf_xword;
            u4 elf_sxword;
        } types;
    } stdsizes;

public:
    MemReader reader;
public:
    ElfReader() { setHandler(NULL); }

    bool parseFromFile(const char *fileName);

    bool parseFromMem(u1 *mem, u4 len);

private:
    elf_ident_t *ident;
    union {
        Elf32_Ehdr *_32;
        Elf64_Ehdr *_64;
    } ehdr;
    union {
        Elf32_Shdr *_32;        //start of shdr
        Elf64_Shdr *_64;
    } shdr;
    union {
        Elf32_Phdr *_32;        //start of phdr
        Elf64_Phdr *_64;
    } phdr;

public:
    // error handler, 可以用来修复reader过程中的bug，毕竟某些东西带混淆的
    void setHandler(bool(*_handler)(const ElfReader &reader, errcode_t code, ...));

    // 尝试处理错误，返回true将从错误中恢复，继续进行解析
    bool(*handle_error)(const ElfReader &reader, errcode_t notif, ...);

    //-----------for ident------------
    bool readIdent();

    const elf_ident_t *getIdent() { return ident; }

    bool isValid();

    bool isMsb() { return ident->bytesex == ELFDATA2MSB; }

    bool is64() { return ident->elf_class == ELFCLASS64; }

    //----------for elf ehdr------------
    bool readHeader();
    bool readSectionHeader();
    bool readProgramheader();

    template<typename ehdrx>
    bool readHeader(ehdrx *ehdr);
    template<typename ehdrx, typename phdrx>
    bool readProgramheader(ehdrx *ehdr, phdrx* phdr);
    template<typename ehdrx, typename shdrx, typename phdrx>
    bool readSectionHeader(ehdrx *ehdr, shdrx shdr, phdrx phdr);

    u4 getSectionOff();
    u4 getProgramOff();
public:
    int readEndian(void *buf, int size);

    int readAddr(void *buf);

    int readOff(void *buf);

    int readXword(void *buf);

    int readSxword(void *buf);

    int readWord(u4 *buf);

    int readHalf(u2 *buf);

    int readByte(u1 *buf);

private:
    bool parseElf();
};


#endif //ELFREADER_ELFREADER_H
