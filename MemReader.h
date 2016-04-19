//
// Created by F8LEFT on 2016/4/19.
//

#ifndef ELFREADER_MEMREADER_H
#define ELFREADER_MEMREADER_H

#include "common.h"
#include <c++/memory>
#include <c++/bits/ios_base.h>
#include <iostream>
using namespace std;

class MemReader {
private:
    shared_ptr <u1> pMap;
    u4 mapSize = 0;

    u1 *readPointer;
    u1 *writePointer;
    u1 *end;
public:             //reader function
    u4 safeRead(void* buf, u4 size, bool isBigEndian = false);
    u4 safeWrite(void* buf, u4 size, bool isBigEndian = false);
    u4 size() { return mapSize; }
    u4 tellg() { return readPointer - pMap.get(); }
    u4 tellp() { return writePointer - pMap.get(); }
    u1* seekg(u4 off, u4 type = ios::beg);
    u1* seekp(u4 off, u4 type = ios::beg);

    bool fromFile(const char *fileName);
    bool fromMem(u1 *mem, u4 len);
};

// 反向copy, 非buf安全,对同一内存操作会产生覆盖
void *__cdecl memcpy_r(void* dst,const void* src, size_t MaxCount);
// 反向copy，buf安全，对同一内存操作也不至于覆盖掉
void *__cdecl memcpy_rs(void* dst,const void* src, size_t MaxCount);

#endif //ELFREADER_MEMREADER_H
