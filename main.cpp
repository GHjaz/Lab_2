#include <iostream>
#include <string>
#include "codegen.h"

int main()
{
    ICodeFactory* icd = new CFactory();
    CodeGenerator* cd = new CodeGenerator(icd);
    std::cout << cd->generateProgram() << std::endl;
    delete icd;
    delete cd;
    return 0;
}
