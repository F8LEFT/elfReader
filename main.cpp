#include <iostream>
#include "ElfReader.h"
using namespace std;

int main() {
#ifndef BPROC
    cout << "Please set BPROC option to build!!!" << endl ;
    return 0;
#endif

    ElfReader reader;
    reader.parseFromFile("F:\\CodeSrc\\FDA\\elfReader\\res\\libcocos2dlua.so");
    reader.readIdent();
    reader.readHeader();
    reader.readProgramheader();
    reader.readSectionHeader();
    cout << "Hello, World!" << endl;
    return 0;
}