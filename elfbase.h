#ifndef __ELFBASE_H__
#define __ELFBASE_H__
#pragma pack(push, 4)

#include "common.h"
//=========================================================================
struct elf_ident_t
{
  u4 magic;
#if __MF__
#  define ELF_MAGIC 0x7F454C46 // big endian \x7FELF
#else
#  define ELF_MAGIC 0x464C457F // litte endian \x7FELF
#endif
  u1 elf_class;
#define   ELFCLASSNONE  0    // Invalid class
#define   ELFCLASS32    1    // 32bit object
#define   ELFCLASS64    2    // 64bit object
  u1 bytesex;
#define   ELFDATANONE    0   // Invalid data encoding
#define   ELFDATA2LSB    1   // low byte first
#define   ELFDATA2MSB    2   // high byte first
  u1 version;             // file version
  u1 osabi;               // Operating System/ABI indication
#define   ELFOSABI_NONE          0 // UNIX System V ABI
#define   ELFOSABI_HPUX          1 // HP-UX operating system
#define   ELFOSABI_NETBSD        2 // NetBSD
#define   ELFOSABI_LINUX         3 // GNU/Linux
#define   ELFOSABI_HURD          4 // GNU/Hurd
#define   ELFOSABI_SOLARIS       6 // Solaris
#define   ELFOSABI_AIX           7 // AIX
#define   ELFOSABI_IRIX          8 // IRIX
#define   ELFOSABI_FREEBSD       9 // FreeBSD
#define   ELFOSABI_TRU64        10 // TRU64 UNIX
#define   ELFOSABI_MODESTO      11 // Novell Modesto
#define   ELFOSABI_OPENBSD      12 // OpenBSD
#define   ELFOSABI_OPENVMS      13 // OpenVMS
#define   ELFOSABI_NSK          14 // Hewlett-Packard Non-Stop Kernel
#define   ELFOSABI_AROS         15 // Amiga Research OS
#define   ELFOSABI_C6000_ELFABI 64 // Texas Instruments TMS320C6 bare-metal
#define   ELFOSABI_C6000_LINUX  65 // TI TMS320C6 MMU-less Linux platform
#define   ELFOSABI_ARM          97 // ARM
#define   ELFOSABI_STANDALONE   255 // Standalone (embedded) application
  u1 abiversion;          // ABI version
  u1 pad[7];
};

struct Elf32_Ehdr
{
  elf_ident_t e_ident;
  u2  e_type;               // enum ET
  u2  e_machine;            // enum EM
  u4  e_version;            // enum EV
  u4  e_entry;              // virtual start address
  u4  e_phoff;              // off to program header table's (pht)
  u4  e_shoff;              // off to section header table's (sht)
  u4  e_flags;              // EF_machine_flag
  u2  e_ehsize;             // header's size
  u2  e_phentsize;          // size of pht element
  u2  e_phnum;              // entry counter in pht
  u2  e_shentsize;          // size of sht element
  u2  e_shnum;              // entry count in sht
  u2  e_shstrndx;           // sht index in name table
};


enum elf_ET
{
  ET_NONE = 0,    // No file type
  ET_REL  = 1,    // Relocatable file
  ET_EXEC = 2,    // Executable file
  ET_DYN  = 3,    // Share object file
  ET_CORE = 4,    // Core file
  ET_LOOS   = 0xfe00u,  // OS specific
  ET_HIOS   = 0xfeffu,  // OS specific
  ET_LOPROC = 0xff00u,  // Processor specific
  ET_HIPROC = 0xffffu   // Processor specific
};

enum elf_EM
{
  EM_NONE  = 0,   // No machine
  EM_M32   = 1,   // AT & T WE 32100
  EM_SPARC = 2,   // Sparc
  EM_386   = 3,   // Intel 80386
  EM_68K   = 4,   // Motorola 68000
  EM_88K   = 5,   // Motorola 88000
  EM_486   = 6,
  //ATTENTION!!! in documentation present next values
  //  EM_860   = 6,   // Intel 80860
  //  EM_MIPS  = 7,    // MIPS RS3000
  //in linux RS3000 = 8, !!!
  // ¤ «ìè¥ ¢§ïâ?¨§ linux
  EM_860      =  7,
  EM_MIPS     =  8, // Mips 3000 (officialy, big-endian only)
  EM_S370     =  9, // IBM System370
  EM_MIPS_RS3_BE = 10,  //MIPS R3000 Big Endian
  //  EM_SPARC_64 = 11,  // SPARC v9
  EM_PARISC   = 15, // HPPA
  EM_VPP550   = 17, // Fujitsu VPP500
  EM_SPARC32PLUS = 18,  // Sun's v8plus
  EM_I960     = 19, // Intel 960
  EM_PPC      = 20, // Power PC
  EM_PPC64    = 21, // 64-bit PowerPC
  EM_S390     = 22, // IBM S/390
  EM_SPU      = 23, // Cell Broadband Engine Synergistic Processor Unit
  EM_CISCO7200 = 25, // Cisco 7200 Series Router (MIPS)
  EM_CISCO3620 = 30, // Cisco 3620/3640 Router (MIPS, IDT R4700)
  EM_V800     = 36, // NEC V800 series
  EM_FR20     = 37, // Fujitsu FR20
  EM_RH32     = 38, // TRW RH32
  EM_MCORE    = 39, // Motorola M*Core (May also be taken by Fujitsu MMA)
  EM_ARM      = 40, // ARM
  EM_OLD_ALPHA = 41,// Digital Alpha
  EM_SH       = 42, // Renesas (formerly Hitachi) / SuperH SH
  EM_SPARC64  = 43, // Sparc v9 64-bit
  EM_TRICORE  = 44, // Siemens Tricore embedded processor
  EM_ARC      = 45, // ARC Cores
  EM_H8300    = 46, // Renesas (formerly Hitachi) H8/300
  EM_H8300H   = 47, // Renesas (formerly Hitachi) H8/300H
  EM_H8S      = 48, // Renesas (formerly Hitachi) H8S
  EM_H8500    = 49, // Renesas (formerly Hitachi) H8/500
  EM_IA64     = 50, // Intel Itanium IA64
  EM_MIPS_X   = 51, // Stanford MIPS-X
  EM_COLDFIRE = 52, // Motorola Coldfire
  EM_6812     = 53, // Motorola MC68HC12
  EM_MMA      = 54, // Fujitsu Multimedia Accelerator
  EM_PCP      = 55, // Siemens PCP
  EM_NCPU     = 56, // Sony nCPU embedded RISC processor
  EM_NDR1     = 57, // Denso NDR1 microprocesspr
  EM_STARCORE = 58, // Motorola Star*Core processor
  EM_ME16     = 59, // Toyota ME16 processor
  EM_ST100    = 60, // STMicroelectronics ST100 processor
  EM_TINYJ    = 61, // Advanced Logic Corp. TinyJ embedded processor
  EM_X86_64   = 62, // Advanced Micro Devices X86-64 processor
  EM_PDSP     = 63, // Sony DSP Processor
  EM_PDP10    = 64, // DEC PDP-10
  EM_PDP11    = 65, // DEC PDP-11
  EM_FX66     = 66, // Siemens FX66 microcontroller
  EM_ST9      = 67, // STMicroelectronics ST9+ 8/16 bit microcontroller
  EM_ST7      = 68, // STMicroelectronics ST7 8-bit microcontroller
  EM_68HC16   = 69, // Motorola MC68HC16
  EM_6811     = 70, // Motorola MC68HC11
  EM_68HC08   = 71, // Motorola MC68HC08
  EM_68HC05   = 72, // Motorola MC68HC05
  EM_SVX      = 73, // Silicon Graphics SVx
  EM_ST19     = 74, // STMicroelectronics ST19 8-bit cpu
  EM_VAX      = 75, // Digital VAX
  EM_CRIS     = 76, // Axis Communications 32-bit embedded processor
  EM_JAVELIN  = 77, // Infineon Technologies 32-bit embedded cpu
  EM_FIREPATH = 78, // Element 14 64-bit DSP processor
  EM_ZSP      = 79, // LSI Logic's 16-bit DSP processor
  EM_MMIX     = 80, // Donald Knuth's educational 64-bit processor
  EM_HUANY    = 81, // Harvard's machine-independent format
  EM_PRISM    = 82, // SiTera Prism
  EM_AVR      = 83, // Atmel AVR 8-bit microcontroller
  EM_FR       = 84, // Fujitsu FR Family
  EM_D10V     = 85, // Mitsubishi D10V
  EM_D30V     = 86, // Mitsubishi D30V
  EM_V850     = 87, // NEC v850 (GNU compiler)
  EM_NECV850  = 28927, // NEC v850 (NEC compilers)
  EM_NECV850E1= 28924, // NEC v850 ES/E1
  EM_NECV850E2= 29162, // NEC v850 E2
  EM_NECV850Ex= 29646, // NEC v850 ???
  EM_M32R     = 88, // Renesas M32R (formerly Mitsubishi M32R)
  EM_MN10300  = 89, // Matsushita MN10300
  EM_MN10200  = 90, // Matsushita MN10200
  EM_PJ       = 91, // picoJava
  EM_OPENRISC = 92, // OpenRISC 32-bit embedded processor
  EM_ARCOMPACT= 93, // ARC Cores (ARCompact ISA)
  EM_XTENSA   = 94, // Tensilica Xtensa Architecture
  EM_VIDEOCORE= 95, // Alphamosaic VideoCore processor
  EM_TMM_GPP  = 96, // Thompson Multimedia General Purpose Processor
  EM_NS32K    = 97, // National Semiconductor 32000 series
  EM_TPC      = 98, // Tenor Network TPC processor
  EM_SNP1K    = 99, // Trebia SNP 1000 processor
  EM_ST200    =100, // STMicroelectronics ST200 microcontroller
  EM_IP2K     =101, // Ubicom IP2022 micro controller
  EM_MAX      =102, // MAX Processor
  EM_CR       =103, // National Semiconductor CompactRISC
  EM_F2MC16   =104, // Fujitsu F2MC16
  EM_MSP430   =105, // TI msp430 micro controller
  EM_BLACKFIN =106, // ADI Blackfin
  EM_SE_C33   =107, // S1C33 Family of Seiko Epson processors
  EM_SEP      =108, // Sharp embedded microprocessor
  EM_ARCA     =109, // Arca RISC Microprocessor
  EM_UNICORE  =110, // Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University
  EM_EXCESS   =111, // eXcess: 16/32/64-bit configurable embedded CPU
  EM_DXP      =112, // Icera Semiconductor Inc. Deep Execution Processor
  EM_ALTERA_NIOS2=113, // Altera Nios II soft-core processor
  EM_CRX      =114, // National Semiconductor CRX
  EM_XGATE    =115, // Motorola XGATE embedded processor
  EM_C166     =116, // Infineon C16x/XC16x processor
  EM_M16C     =117, // Renesas M16C series microprocessors
  EM_DSPIC30F =118, // Microchip Technology dsPIC30F Digital Signal Controller
  EM_CE       =119, // Freescale Communication Engine RISC core
  EM_M32C     =120, // Renesas M32C series microprocessors
  EM_TSK3000  =131, // Altium TSK3000 core
  EM_RS08     =132, // Freescale RS08 embedded processor
  EM_ECOG2    =134, // Cyan Technology eCOG2 microprocessor
  EM_SCORE    =135, // Sunplus Score
  EM_DSP24    =136, // New Japan Radio (NJR) 24-bit DSP Processor
  EM_VIDEOCORE3 =137, // Broadcom VideoCore III processor
  EM_LATTICEMICO32 =138, // RISC processor for Lattice FPGA architecture
  EM_SE_C17   =139, // Seiko Epson C17 family
  EM_TI_C6000 =140, // Texas Instruments TMS320C6000 family
  EM_MMDSP_PLUS =160, // STMicroelectronics 64bit VLIW Data Signal Processor
  EM_CYPRESS_M8C =161, // Cypress M8C microprocessor
  EM_R32C     =162, // Renesas R32C series microprocessors
  EM_TRIMEDIA =163, // NXP Semiconductors TriMedia architecture family
  EM_QDSP6    =164, // QUALCOMM DSP6 Processor
  EM_8051     =165, // Intel 8051 and variants
  EM_STXP7X   =166, // STMicroelectronics STxP7x family
  EM_NDS32    =167, // Andes Technology compact code size embedded RISC processor family
  EM_ECOG1    =168, // Cyan Technology eCOG1X family
  EM_ECOG1X   =168, // Cyan Technology eCOG1X family
  EM_MAXQ30   =169, // Dallas Semiconductor MAXQ30 Core Micro-controllers
  EM_XIMO16   =170, // New Japan Radio (NJR) 16-bit DSP Processor
  EM_MANIK    =171, // M2000 Reconfigurable RISC Microprocessor
  EM_CRAYNV2  =172, // Cray Inc. NV2 vector architecture
  EM_RX       =173, // Renesas RX family
  EM_METAG    =174, // Imagination Technologies META processor architecture
  EM_MCST_ELBRUS =175, // MCST Elbrus general purpose hardware architecture
  EM_ECOG16   =176, // Cyan Technology eCOG16 family
  EM_CR16     =177, // National Semiconductor CompactRISC 16-bit processor
  EM_ETPU     =178, // Freescale Extended Time Processing Unit
  EM_SLE9X    =179, // Infineon Technologies SLE9X core
  EM_L1OM     =180, // Intel L1OM (Larrabee)
  EM_K1OM     =181, // Intel K1OM
  EM_INTEL182 =182, // Reserved by Intel
  EM_AARCH64  =183, // ARM 64-bit architecture
  EM_ARM184   =184, // Reserved by ARM
  EM_AVR32    =185, // Atmel Corporation 32-bit microprocessor family
  EM_STM8     =186, // STMicroeletronics STM8 8-bit microcontroller
  EM_TILE64   =187, // Tilera TILE64 multicore architecture family
  EM_TILEPRO  =188, // Tilera TILEPro multicore architecture family
  EM_MICROBLAZE=189, // Xilinx MicroBlaze 32-bit RISC soft processor core
  EM_CUDA      =190, // NVIDIA CUDA architecture
  EM_TILEGX    =191, // Tilera TILE-Gx multicore architecture family
  EM_CLOUDSHIELD=192, // CloudShield architecture family
  EM_COREA_1ST =193, // KIPO-KAIST Core-A 1st generation processor family
  EM_COREA_2ND =194, // KIPO-KAIST Core-A 2nd generation processor family
  EM_ARC_COMPACT2=195, //Synopsys ARCompact V2
  EM_OPEN8     =196, // Open8 8-bit RISC soft processor core
  EM_RL78      =197, // Renesas RL78 family
  EM_VIDEOCORE5=198, // Broadcom VideoCore V processor
  EM_78K0R     =199, // Renesas 78K0R family
  EM_56800EX   =200, // Freescale 56800EX Digital Signal Controller
  EM_BA1       =201, // Beyond BA1 CPU architecture
  EM_BA2       =202, // Beyond BA2 CPU architecture
  EM_XCORE     =203, // XMOS xCORE processor family
  EM_CYGNUS_POWERPC = 0x9025, // Cygnus PowerPC ELF backend
  EM_ALPHA    = 0x9026 // DEC Alpha
};

enum elf_EV
{
  EV_NONE    = 0, // None version
  EV_CURRENT = 1  // Current version
  // in linux header
  // EV_NUM      = 2
};
#define VER_FLG_BASE    0x1   // in vd_flags
#define VER_FLG_WEAK    0x2   // -"-

// special section indexes
enum elh_SHN
{
  SHN_UNDEF     = 0,       // undefined/missing/...
  SHN_LORESERVE = 0xff00,
  SHN_LOPROC    = 0xff00,
  SHN_HIPROC    = 0xff1f,
  SHN_ABS       = 0xfff1,  // absolute value
  SHN_COMMON    = 0xfff2,  //common values (fortran/c)
  SHN_HIRESERVE = 0xffff
};
//==========

struct Elf32_Shdr
{
  u4 sh_name;      // index in string table
  u4 sh_type;      // enum SHT
  u4 sh_flags;     // enum SHF
  u4 sh_addr;      // address in memmory (or 0)
  u4 sh_offset;    // offset in file
  u4 sh_size;      // section size in bytes
  u4 sh_link;      // index in symbol table
  u4 sh_info;      // extra information
  u4 sh_addralign; // 0 & 1 => no alignment
  u4 sh_entsize;   // size symbol table or eq.
};


enum elf_SHT
{
  SHT_NULL      = 0,    // inactive - no assoc. section
  SHT_PROGBITS  = 1,    // internal program information
  SHT_SYMTAB    = 2,    // symbol table (static)
  SHT_STRTAB    = 3,    // string table
  SHT_RELA      = 4,    // relocation entries
  SHT_HASH      = 5,    // symbol hash table
  SHT_DYNAMIC   = 6,    // inf. for dynamic linking
  SHT_NOTE      = 7,    // additional info
  SHT_NOBITS    = 8,    // no placed in file
  SHT_REL       = 9,    // relocation entries without explicit address
  SHT_SHLIB     = 10,   // RESERVED
  SHT_DYNSYM    = 11,   // Dynamic Symbol Table
  // abi 3
  SHT_INIT_ARRAY    = 14, // Array of ptrs to init functions
  SHT_FINI_ARRAY    = 15, // Array of ptrs to finish functions
  SHT_PREINIT_ARRAY = 16, // Array of ptrs to pre-init funcs
  SHT_GROUP         = 17, // Section contains a section group
  SHT_SYMTAB_SHNDX  = 18, // Indicies for SHN_XINDEX entries
  //  SHT_NUM       = 12,
  SHT_LOOS      = 0x60000000ul,
  SHT_HIOS      = 0x6ffffffful,
  SHT_LOPROC    = 0x70000000ul,
  SHT_HIPROC    = 0x7ffffffful,
  SHT_LOUSER    = 0x80000000ul,
  SHT_HIUSER    = 0xfffffffful,
  //
  // The remaining values are not in the standard.
  // Incremental build data.
  SHT_GNU_INCREMENTAL_INPUTS = 0x6fff4700,
  // Object attributes.
  SHT_GNU_ATTRIBUTES = 0x6ffffff5,
  // GNU style dynamic hash table.
  SHT_GNU_HASH = 0x6ffffff6,
  // List of prelink dependencies.
  SHT_GNU_LIBLIST = 0x6ffffff7,

  // The next three section types are defined by Solaris, and are named SHT_SUNW*.  We use them in GNU code, so we also define SHT_GNU*
  SHT_SUNW_verdef   = 0x6ffffffd, // Versions defined by file
  SHT_SUNW_verneed  = 0x6ffffffe, // Versions needed by file
  SHT_SUNW_versym   = 0x6fffffff  // Symbol versions
};

// section by index 0 ==
// { 0, SHT_NULL, 0, 0, 0, 0, SHN_UNDEF, 0, 0, 0 };

enum elf_SHF
{
  SHF_WRITE     = (1 << 0),     // writable data
  SHF_ALLOC     = (1 << 1),     // occupies memory
  SHF_EXECINSTR = (1 << 2),     // machine instruction

  SHF_MERGE     = (1 << 4),     // can be merged
  SHF_STRINGS   = (1 << 5),     // contains nul-terminated strings
  SHF_INFO_LINK = (1 << 6),     // sh_info contains SHT index
  SHF_LINK_ORDER= (1 << 7),     // preserve order after combining
  SHF_OS_NONCONFORMING = (1 << 8), // non-standard os specific handling required
  SHF_GROUP     = (1 << 9),     // section is memory of a group
  SHF_TLS       = (1 << 10),    // section holds thread-local data

  SHF_MASKOS    = 0x0ff00000,   // os specific
  SHF_MASKPROC  = 0xf0000000,   // processor specific
};

enum elf_GRP
{
  GRP_COMDAT   = 0x00000001,  // This is a COMDAT group.
  GRP_MASKOS   = 0x0ff00000,  // OS-specific flags
  GRP_MASKPROC = 0xf0000000,  // Processor-specific flags
};

struct Elf32_Sym
{
  u4    st_name;        //index in string table
  u4    st_value;       //absolute value or addr
  u4    st_size;        //0-unknow or no, elsewere symbol size in bytes
  unsigned char st_info;        //type and attribute (thee below)
  unsigned char st_other;       //==0
  u2    st_shndx;       //index in section header table
};

#define ELF_ST_BIND(i)    ((i)>>4)
#define ELF_ST_TYPE(i)    ((i)&0xf)
#define ELF_ST_INFO(b,t)  (((b)<<4)+((t)&0xf))
/* This macro disassembles and assembles a symbol's visibility into
   the st_other field.  The STV_ defines specificy the actual visibility.  */
#define ELF_ST_VISIBILITY(v)            ((v) & 0x3)

enum elf_ST_BIND
{
  STB_LOCAL   = 0,
  STB_GLOBAL  = 1,
  STB_WEAK    = 2,
  STB_LOOS    = 10,              //OS-specific
  STB_GNU_UNIQUE = 10,           // Symbol is unique in namespace
  STB_HIOS    = 12,
  STB_LOPROC  = 13,              //processor-
  STB_HIPROC  = 15,               //          specific
  STB_INVALID = 254
};

enum elf_ST_TYPE
{
  STT_NOTYPE    = 0,
  STT_OBJECT  = 1,              // associated with data object
  STT_FUNC    = 2,              // associated with function or execut. code
  STT_SECTION = 3,
  STT_FILE    = 4,              // name of source file
  STT_COMMON  = 5,              // Uninitialized common section
  STT_TLS     = 6,              // TLS-data object
  STT_LOOS   = 10,              //OS-
  STT_HIOS   = 12,              //   specific
  STT_LOPROC = 13,              //processor-
  STT_HIPROC = 15,              //          specific
  STT_GNU_IFUNC = 10,           // Symbol is an indirect code object
};

enum elf_ST_VISIBILITY
{
  STV_DEFAULT    = 0,               /* Visibility is specified by binding type */
  STV_INTERNAL   = 1,               /* OS specific version of STV_HIDDEN */
  STV_HIDDEN     = 2,               /* Can only be seen inside currect component */
  STV_PROTECTED  = 3,               /* Treat as STB_LOCAL inside current component */
};

/* Special values for the st_other field in the symbol table.  These
   are used in an Irix 5 dynamic symbol table.  */
enum elf_ST_OTHER
{
  STO_DEFAULT             = STV_DEFAULT,
  STO_INTERNAL            = STV_INTERNAL,
  STO_HIDDEN              = STV_HIDDEN,
  STO_PROTECTED           = STV_PROTECTED,
/* This bit is used on Irix to indicate a symbol whose definition
   is optional - if, at final link time, it cannot be found, no
   error message should be produced.  */
  STO_OPTIONAL            = (1 << 2),
};

// relocation
struct Elf32_Rel
{
  u4    r_offset;       //virtual address
  u4    r_info;         //type of relocation
};

#define ELF32_R_SYM(i)    ((i)>>8)
#define ELF32_R_TYPE(i)   ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

struct Elf32_Rela
{
  u4    r_offset;
  u4    r_info;
  s4   r_addend;       //constant to compute
};

//=================Loading & dynamic linking========================
// program header
struct Elf32_Phdr
{
  u4    p_type;         //Segment type. see below
  u4    p_offset;       //from beginning of file at 1 byte of segment resides
  u4    p_vaddr;        //virtual addr of 1 byte
  u4    p_paddr;        //reserved for system
  u4    p_filesz;       //may be 0
  u4    p_memsz;        //may be 0
  u4    p_flags;        // for PT_LOAD access mask (PF_xxx)
  u4    p_align;        //0/1-no,
};

enum elf_SEGFLAGS
{
  PF_X          = (1 << 0),       // Segment is executable
  PF_W          = (1 << 1),       // Segment is writable
  PF_R          = (1 << 2),       // Segment is readable

  // PaX flags (for PT_PAX_FLAGS)
  PF_PAGEEXEC   = (1 << 4),       // Enable  PAGEEXEC
  PF_NOPAGEEXEC = (1 << 5),       // Disable PAGEEXEC
  PF_SEGMEXEC   = (1 << 6),       // Enable  SEGMEXEC
  PF_NOSEGMEXEC = (1 << 7),       // Disable SEGMEXEC
  PF_MPROTECT   = (1 << 8),       // Enable  MPROTECT
  PF_NOMPROTECT = (1 << 9),       // Disable MPROTECT
  PF_RANDEXEC   = (1 << 10),      // Enable  RANDEXEC
  PF_NORANDEXEC = (1 << 11),      // Disable RANDEXEC
  PF_EMUTRAMP   = (1 << 12),      // Enable  EMUTRAMP
  PF_NOEMUTRAMP = (1 << 13),      // Disable EMUTRAMP
  PF_RANDMMAP   = (1 << 14),      // Enable  RANDMMAP
  PF_NORANDMMAP = (1 << 15),      // Disable RANDMMAP

  PF_MASKOS     = 0x0FF00000,     // OS-specific reserved bits
  PF_MASKPROC   = 0xF0000000,     // Processor-specific reserved bits
};

enum elf_SEGTYPE
{
  PT_NULL    = 0,               //ignore entries in program table
  PT_LOAD    = 1,               //loadable segmen described in _filesz & _memsz
  PT_DYNAMIC = 2,               //dynamic linking information
  PT_INTERP  = 3,               //path name to interpreter (loadable)
  PT_NOTE    = 4,               //auxilarry information
  PT_SHLIB   = 5,               //reserved. Has no specified semantics
  PT_PHDR    = 6,               //location & size program header table
  PT_TLS     = 7,               //Thread local storage segment
  PT_LOOS    = 0x60000000ul,    // OS-
  PT_HIOS    = 0x6ffffffful,    //    specific
  PT_LOPROC  = 0x70000000ul,    // processor-
  PT_HIPROC  = 0x7ffffffful,    //           specific
  //
  PT_GNU_EH_FRAME = (PT_LOOS + 0x474e550ul),
  PT_GNU_STACK    = (PT_LOOS + 0x474e551ul),
  PT_GNU_RELRO    = (PT_LOOS + 0x474e552), // Read-only after relocation
  PT_PAX_FLAGS    = (PT_LOOS + 0x5041580), // PaX flags
};

//=================Dynamic section===============================
struct Elf32_Dyn
{
  s4   d_tag;          //see below
  union
  {
    u4  d_val;          //integer value with various interpretation
    u4  d_ptr;          //programm virtual adress
  } d_un;
};
//extern Elf32_Dyn _DYNAMIC[];

enum elf_DTAG
{
  DT_NULL     = 0,              //(-) end ofd _DYNAMIC array
  DT_NEEDED   = 1,              //(v) str-table offset name to needed library
  DT_PLTRELSZ = 2,              //(v) tot.size in bytes of relocation entries
  DT_PLTGOT   = 3,              //(p) see below
  DT_HASH     = 4,              //(p) addr. of symbol hash teble
  DT_STRTAB   = 5,              //(p) addr of string table
  DT_SYMTAB   = 6,              //(p) addr of symbol table
  DT_RELA     = 7,              //(p) addr of relocation table
  DT_RELASZ   = 8,              //(v) size in bytes of DT_RELA table
  DT_RELAENT  = 9,              //(v) size in bytes of DT_RELA entry
  DT_STRSZ    = 10,             //(v) size in bytes of string table
  DT_SYMENT   = 11,             //(v) size in byte of symbol table entry
  DT_INIT     = 12,             //(p) addr. of initialization function
  DT_FINI     = 13,             //(p) addr. of termination function
  DT_SONAME   = 14,             //(v) offs in str.-table - name of shared object
  DT_RPATH    = 15,             //(v) offs in str-table - search patch
  DT_SYMBOLIC = 16,             //(-) start search of shared object
  DT_REL      = 17,             //(p) similar to DT_RELA
  DT_RELSZ    = 18,             //(v) tot.size in bytes of DT_REL
  DT_RELENT   = 19,             //(v) size in bytes of DT_REL entry
  DT_PLTREL   = 20,             //(v) type of relocation (DT_REL or DT_RELA)
  DT_DEBUG    = 21,             //(p) not specified
  DT_TEXTREL  = 22,             //(-) segment permisson
  DT_JMPREL   = 23,             //(p) addr of dlt procedure (if present)
  DT_BIND_NOW         = 24,
  DT_INIT_ARRAY       = 25,
  DT_FINI_ARRAY       = 26,
  DT_INIT_ARRAYSZ     = 27,
  DT_FINI_ARRAYSZ     = 28,
  DT_RUNPATH          = 29,
  DT_FLAGS            = 30,
#define DF_ORIGIN         0x01
#define DF_SYMBOLIC       0x02
#define DF_TEXTREL        0x04
#define DF_BIND_NOW       0x08
#define DF_STATIC_TLS     0x10
  DT_ENCODING         = 31,
  DT_PREINIT_ARRAY    = 32,
  DT_PREINIT_ARRAYSZ  = 33,
  DT_LOOS       = 0x60000000ul,  // OS-specific
  DT_HIOS       = 0x6ffffffful,  //
  //
  DT_VALRNGLO       = 0x6ffffd00ul,   // solaris
  DT_GNU_PRELINKED  = 0x6ffffdf5ul,   // solaris
  DT_GNU_CONFLICTSZ = 0x6ffffdf6ul,   // solaris
  DT_GNU_LIBLISTSZ  = 0x6ffffdf7ul,   // solaris
  DT_CHECKSUM       = 0x6ffffdf8ul,
  DT_PLTPADSZ       = 0x6ffffdf9ul,
  DT_MOVEENT        = 0x6ffffdfaul,
  DT_MOVESZ         = 0x6ffffdfbul,
  DT_FEATURE        = 0x6ffffdfcul,
#define DTF_1_PARINIT   0x00000001
#define DTF_1_CONFEXP   0x00000002
  DT_POSFLAG_1      = 0x6ffffdfdul,
#define DF_P1_LAZYLOAD  0x00000001
#define DF_P1_GROUPPERM 0x00000002
  DT_SYMINSZ        = 0x6ffffdfeul,
  DT_SYMINENT       = 0x6ffffdfful,
  DT_VALRNGHI       = 0x6ffffdfful,
  DT_ADDRRNGLO      = 0x6ffffe00ul,
  DT_GNU_HASH       = 0x6ffffef5ul,  // GNU-style hash table.
  DT_TLSDESC_PLT    = 0x6ffffef6ul,
  DT_TLSDESC_GOT    = 0x6ffffef7ul,
  DT_GNU_CONFLICT   = 0x6ffffef8ul,  // Start of conflict section
  DT_GNU_LIBLIST    = 0x6ffffef9ul,
  DT_CONFIG         = 0x6ffffefaul,
  DT_DEPAUDIT       = 0x6ffffefbul,
  DT_AUDIT          = 0x6ffffefcul,
  DT_PLTPAD         = 0x6ffffefdul,
  DT_MOVETAB        = 0x6ffffefeul,
  DT_SYMINFO        = 0x6ffffefful,
  DT_ADDRRNGHI      = 0x6ffffefful,
  DT_RELACOUNT      = 0x6ffffff9ul,
  DT_RELCOUNT       = 0x6ffffffaul,
  DT_FLAGS_1        = 0x6ffffffbul,
#define DF_1_NOW        0x00000001
#define DF_1_GLOBAL     0x00000002
#define DF_1_GROUP      0x00000004
#define DF_1_NODELETE   0x00000008
#define DF_1_LOADFLTR   0x00000010
#define DF_1_INITFIRST  0x00000020
#define DF_1_NOOPEN     0x00000040
#define DF_1_ORIGIN     0x00000080
#define DF_1_DIRECT     0x00000100
#define DF_1_TRANS      0x00000200
#define DF_1_INTERPOSE  0x00000400
#define DF_1_NODEFLIB   0x00000800
#define DF_1_NODUMP     0x00001000
#define DF_1_CONLFAT    0x00002000
  DT_VERDEF         = 0x6ffffffcul,
  DT_VERDEFNUM      = 0x6ffffffdul,
  DT_VERNEED        = 0x6ffffffeul,
  DT_VERNEEDNUM     = 0x6ffffffful,
  DT_VERSYM         = 0x6ffffff0ul,   // solaris
  //
  DT_LOPROC   = 0x70000000ul,   //(?) processor-
  DT_HIPROC   = 0x7ffffffful,   //(?)           specific
  //
  DT_AUXILIARY    = 0x7ffffffdul,
  DT_USED         = 0x7ffffffeul,
  DT_FILTER       = 0x7ffffffful,
};

//===============================elf64 types=============================
struct Elf64_Ehdr
{
  elf_ident_t e_ident;
  u2    e_type;
  u2    e_machine;
  u4    e_version;
  u8    e_entry;          // Entry point virtual address
  u8    e_phoff;          // Program header table file offset
  u8    e_shoff;          // Section header table file offset
  u4    e_flags;
  u2    e_ehsize;
  u2    e_phentsize;
  u2    e_phnum;
  u2    e_shentsize;
  u2    e_shnum;
  u2    e_shstrndx;
};

struct Elf64_Shdr
{
  u4    sh_name;      // Section name, index in string tbl
  u4    sh_type;      // Type of section
  u8    sh_flags;     // Miscellaneous section attributes
  u8    sh_addr;      // Section virtual addr at execution
  u8    sh_offset;    // Section file offset
  u8    sh_size;      // Size of section in bytes
  u4    sh_link;      // Index of another section
  u4    sh_info;      // Additional section information
  u8    sh_addralign; // Section alignment
  u8    sh_entsize;   // Entry size if section holds table
};

//
struct Elf64_Sym
{
  u4    st_name;    // Symbol name, index in string tbl
  u1     st_info;    // Type and binding attributes
  u1     st_other;   // No defined meaning, 0
  u2    st_shndx;   // Associated section index
  u8    st_value;   // Value of the symbol
  u8    st_size;    // Associated symbol size
};

struct Elf64_Rel
{
  u8    r_offset;  // Location at which to apply the action
  u8    r_info;    // index and type of relocation
};

struct Elf64_Rela
{
  u8    r_offset;    // Location at which to apply the action
  u8    r_info;      // index and type of relocation
  s8     r_addend;    // Constant addend used to compute value
};


//#define ELF64_R_SYM(i)           ((i) >> 32)
//#define ELF64_R_TYPE(i)    ((i) & 0xffffffff)
//#define ELF64_R_INFO(s,t)  (((bfd_vma) (s) << 32) + (bfd_vma) (t))
#define ELF64_R_SYM(i)     u4((i) >> 32)
#define ELF64_R_TYPE(i)    u4(i)


struct Elf64_Phdr
{
  u4    p_type;
  u4    p_flags;
  u8    p_offset;   // Segment file offset
  u8    p_vaddr;    // Segment virtual address
  u8    p_paddr;    // Segment physical address
  u8    p_filesz;   // Segment size in file
  u8    p_memsz;    // Segment size in memory
  u8    p_align;    // Segment alignment, file & memory
};

struct Elf64_Dyn
{
  u8 d_tag;   // entry tag value
  union
  {
	  u8  d_val;          //integer value with various interpretation
	  u8  d_ptr;          //programm virtual adress
  } d_un;
};
//extern Elf64_Dyn _DYNAMIC[];

//=======================================================================
// Definitions for other modules

#define ELFNODE         "$ elfnode"       // value: Elf64_Ehdr
#define ELF_PHT_TAG     'p'               // supval(idx): Elf64_Phdr
#define ELF_SHT_TAG     's'               // supval(idx): Elf64_Shdr
#define GOTNODE         "$ got"           // altval(0): GOT address + 1
                                          // altval(-1): size of the local GOT part (MIPS only)
#define ATTRNODE        "$ attributes"    // hashval(vendorname) - nodeidx of netnode with attribute list
                                          // in that node:
                                          //   supval(tag): string value
                                          //   altval(tag): integer value + 1
                                          // Tag_compatibility uses both
                                          // Tag_also_compatible_with (for 'aeabi') stores sub-tag number in default altval
                                          //   and its value in supval('c') or altval('c')
#define ELFSEGMMAPPINGS "$ elfsegmmap"    // Holds a list of mappings for segments, conceptually of the form:
                                          // (wanted_startEA, wanted_size, mapped_startEA)
                                          // Note: Only the segments whose mapped EA is *not* the EA that the
                                          // binary file advertises for that segment will be present in
                                          // this netnode, not all segments.
                                          // This netnode should be iterated on using alt1st/altnxt.
                                          //
                                          // idx: wanted_startEA
                                          // altval(idx): mapped_startEA
                                          // altval(idx, 's'): wanted_size

#define ATTR_VENDOR_EABI "aeabi"
#define ATTR_VENDOR_GNU  "gnu"
#define ATTR_VENDOR_ARM  "ARM"

// WARNING: Don't move this 'pop' directive below the
// inclusion of 'elf.h'. See elf.h for more info.
#pragma pack(pop)


#ifdef _NETNODE_HPP
#include "elf.h"
inline int is_linux_elf(void) // -1:no, 0-unknwon,1-yes
{
  netnode n(ELFNODE);
  elf_ident_t ident;
  if ( n.valobj(&ident, sizeof(ident)) != sizeof(ident) )
    return 0; // unknown
  switch ( ident.osabi )
  {
    case ELFOSABI_LINUX:
      return 1;
    case ELFOSABI_NONE:
      return 0;
    default:
      return -1; // definitely not
  }
}
#endif

#endif // __ELFBASE_H__
