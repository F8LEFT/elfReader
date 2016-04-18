#pragma once
//---------------------------------------------------------------------------
// Linux C mode compiler already has these types defined
#if !defined(__LINUX__) || defined(__cplusplus)
typedef unsigned char  uchar;   ///< unsigned 8 bit value
typedef unsigned short ushort;  ///< unsigned 16 bit value
typedef unsigned int   uint;    ///< unsigned 32 bit value
#endif

typedef          char   int8;   ///< signed 8 bit value
typedef signed   char   sint8;  ///< signed 8 bit value
typedef unsigned char   uint8;  ///< unsigned 8 bit value
typedef          short  int16;  ///< signed 16 bit value
typedef unsigned short  uint16; ///< unsigned 16 bit value
typedef          int    int32;  ///< signed 32 bit value
typedef unsigned int    uint32; ///< unsigned 32 bit value

								//---------------------------------------------------------------------------
#if defined(__BORLANDC__)

#define __HAS_LONGLONG__
								//#define __HAS_INT128__
typedef unsigned __int64 ulonglong;
typedef          __int64 longlong;

#elif defined(_MSC_VER)

#define __HAS_LONGLONG__
typedef unsigned __int64 ulonglong;
typedef          __int64 longlong;

#elif defined(__GNUC__)

#define __HAS_LONGLONG__
typedef unsigned long long ulonglong;
typedef          long long longlong;

#endif

typedef longlong        int64;  ///< signed 64 bit value
typedef ulonglong       uint64; ///< unsigned 64 bit value

#ifndef MAXSTR
#define MAXSTR 1024                ///< maximum string size
#endif

#ifndef FMT_64
#define FMT_64 "L"
#endif // !FMT_64

#define PAGE_SHIFT    12
#define PAGE_SIZE    (1UL << PAGE_SHIFT) //就是它，这里是4096个字节

#define PAGE_MASK    (~(PAGE_SIZE-1))
								// Returns the address of the page containing address 'x'.
#define PAGE_START(x)  ((x) & PAGE_MASK)

								// Returns the offset of address 'x' in its page.
#define PAGE_OFFSET(x) ((x) & ~PAGE_MASK)

								// Returns the address of the next page after address 'x', unless 'x' is
								// itself at the start of a page.
#define PAGE_END(x)    PAGE_START((x) + (PAGE_SIZE-1))

#define SOINFO_NAME_LEN 128

