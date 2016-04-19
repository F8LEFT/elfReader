//
// Created by F8LEFT on 2016/4/19.
//

#include "MemReader.h"

#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

bool MemReader::fromFile(const char *fileName) {
    if (pMap.get() != NULL) {
        return false;
    }
    ifstream file(fileName, ios::binary);
    if (file.is_open()) {
        file.seekg(0, ios::end);
        mapSize = file.tellg();
        file.seekg(0, ios::beg);
        pMap.reset(new u1[mapSize]);
        file.read((char *) pMap.get(), mapSize);
        file.close();
        end = pMap.get() + mapSize;
        return true;
    }
    return false;
}

bool MemReader::fromMem(u1 *mem, u4 len) {
    if (pMap.get() != NULL) {
        return false;
    }
    mapSize = len;
    pMap.reset(new u1[len]);
    memcpy(pMap.get(), mem, len);
    end = pMap.get() + mapSize;

    return true;
}

u4 MemReader::safeRead(void *buf, u4 size, bool isBigEndian) {
    u4 rBytes = 0;
    if (isBigEndian) {
        rBytes = (readPointer + size > end) ? end - readPointer : size;
        memcpy_rs(buf, readPointer, rBytes);
        readPointer += rBytes;
    } else {
        rBytes = (readPointer + size > end) ? end - readPointer : size;
        memcpy(buf, readPointer, rBytes);
        readPointer += rBytes;
    }
    return rBytes;
}

u4 MemReader::safeWrite(void *buf, u4 size, bool isBigEndian) {
    u4 rWrites = 0;
    if (isBigEndian) {
        rWrites = (writePointer + size > end) ? end - writePointer : size;
        memcpy_rs(writePointer, buf, rWrites);
        writePointer += rWrites;
    } else {
        rWrites = (writePointer + size > end) ? end - writePointer : size;
        memcpy(writePointer, buf, rWrites);
        writePointer += rWrites;
    }
    return rWrites;
}

u1* MemReader::seekg(u4 off, u4 type) {
    switch (type) {
        case ios::beg:
            readPointer = pMap.get() + off;
            break;
        case ios::cur:
            readPointer += off;
            break;
        case ios::end:
            readPointer = end + off;
            break;
    }
    if (readPointer < pMap.get()) {
        readPointer = pMap.get();
    } else if (readPointer > end) {
        readPointer = end;
    }
    return readPointer;
}

u1* MemReader::seekp(u4 off, u4 type) {
    switch (type) {
        case ios::beg:
            writePointer = pMap.get() + off;
            break;
        case ios::cur:
            writePointer += off;
            break;
        case ios::end:
            writePointer = end + off;
            break;
    }
    if (writePointer < pMap.get()) {
        writePointer = pMap.get();
    } else if (writePointer > end) {
        writePointer = end;
    }
    return writePointer;
}

void *memcpy_r(void *dst, const void *src, size_t MaxCount) {
    u1* pEnd = (u1*)src + MaxCount;
    u1* pStart = (u1*)dst;
    for (size_t i= 0; i < MaxCount; ++i) {
        *pStart = *pEnd;
        pStart++; pEnd--;
    }
    return dst;
}

void *memcpy_rs(void *dst, const void *src, size_t MaxCount) {
    if (abs((int)((u1*)dst - (u1*)src)) < MaxCount) {     //存在重叠地方
        shared_ptr<u1> pTmp(new u1[MaxCount]);
        memcpy(pTmp.get(), src, MaxCount);
        dst = memcpy_r(dst, pTmp.get(), MaxCount);
    } else {
        dst = memcpy_r(dst, src, MaxCount);
    }
    return dst;
}
