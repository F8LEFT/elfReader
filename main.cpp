#include <iostream>
#include "ElfReader.h"
using namespace std;

int main() {
    ElfReader reader;
    reader.parseFromFile("F:\\CodeSrc\\FDA\\elfReader\\res\\libcocos2dlua.so");
    reader.readIdent();
    reader.readHeader();
    cout << "Hello, World!" << endl;
    return 0;
}