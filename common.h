#pragma once
//---------------------------------------------------------------------------
// Linux C mode compiler already has these types defined
#include <c++/cstdint>

#if !defined(__LINUX__) || defined(__cplusplus)
typedef unsigned char  uchar;   ///< unsigned 8 bit value
typedef unsigned short ushort;  ///< unsigned 16 bit value
typedef unsigned int   uint;    ///< unsigned 32 bit value
#endif

typedef uint8_t             u1;
typedef uint16_t            u2;
typedef uint32_t            u4;
typedef uint64_t            u8;
typedef int8_t              s1;
typedef int16_t             s2;
typedef int32_t             s4;
typedef int64_t             s8;

#ifndef MAXSTR
#define MAXSTR 1024                ///< maximum string size
#endif

#ifndef FMT_64
#define FMT_64 "L"
#endif // !FMT_64

// 补充一些Android的定义
#ifdef __ANDROID__
#include <android/log.h>
#define FLOG_TAG "F8LEFT"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, FLOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, FLOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, FLOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, FLOG_TAG, __VA_ARGS__)
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, FLOG_TAG, __VA_ARGS__)
#else
#define LOGE printf
#define LOGD printf
#define LOGW printf
#define LOGI printf
#define LOGV printf
#endif

#define ALOGE LOGE
#define ALOGV LOGV
#define ALOGW LOGW
#define ALOGD LOGD
#define ALOGI LOGI

#define PAGE_SHIFT    12
#define PAGE_SIZE    (1UL << PAGE_SHIFT) //就是它，这里是4096个字节

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif
#ifndef PAGESIZE
#define PAGESIZE PAGE_SIZE
#endif
#define PAGE_MASK (~(PAGE_SIZE) - 1)

#define PAGE_START(x)  ((x) & PAGE_MASK)
#define PAGE_OFFSET(x) ((x) & ~PAGE_MASK)
#define PAGE_END(x)    PAGE_START((x) + (PAGE_SIZE-1))


#define SOINFO_NAME_LEN 128

