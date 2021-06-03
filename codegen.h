#pragma once
#include "methodunit.h"
#include "printoperatorunit.h"
#include "classunit.h"

class ICodeFactory
{
public:
    virtual std::shared_ptr<ClassUnit> createClassUnit(std::string name, ClassUnit::Flags modifier = 0, ClassUnit::Flags access_modifier = 0) = 0;
    virtual std::shared_ptr<MethodUnit> createMethodUnit(std::string name, std::string returnType, MethodUnit::Flags flags) = 0;
    virtual std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(std::string text) = 0;
    virtual ~ICodeFactory() {}
};

class CFactory : public ICodeFactory
{
public:
    explicit CFactory() {}
    ~CFactory() {}
    std::shared_ptr<ClassUnit> createClassUnit(std::string name, ClassUnit::Flags modifier = 0, ClassUnit::Flags access_modifier = 0) {
        return std::make_shared<CClassUnit>(name);
    }
    std::shared_ptr<MethodUnit> createMethodUnit(std::string name, std::string returnType, MethodUnit::Flags flags) {
        return std::make_shared<CMethodUnit>(name, returnType, flags);
    }
    std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(std::string text) {
        return std::make_shared<CPrintOperatorUnit>(text);
    }
};

class SFactory : public ICodeFactory
{
public:
   explicit SFactory() {}
   ~SFactory() {}
   std::shared_ptr<ClassUnit> createClassUnit(std::string name, ClassUnit::Flags modifier = 0, ClassUnit::Flags access_modifier = 0) {
       return std::make_shared<SClassUnit>(name, modifier, access_modifier);
   }
   std::shared_ptr<MethodUnit> createMethodUnit(std::string name, std::string returnType, MethodUnit::Flags flags) {
       return std::make_shared<SMethodUnit>(name, returnType, flags);
   }
   std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(std::string text) {
       return std::make_shared<SPrintOperatorUnit>(text);
   }
};

class JFactory : public ICodeFactory
{
public:
   explicit JFactory() {}
   ~JFactory() {}
   std::shared_ptr<ClassUnit> createClassUnit(std::string name, ClassUnit::Flags modifier = 0, ClassUnit::Flags access_modifier = 0) {
       return std::make_shared<JClassUnit>(name, modifier, access_modifier);
   }
   std::shared_ptr<MethodUnit> createMethodUnit(std::string name, std::string returnType, MethodUnit::Flags flags) {
       return std::make_shared<JMethodUnit>(name, returnType, flags);
   }
   std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(std::string text) {
       return std::make_shared<JPrintOperatorUnit>(text);
   }
};


class CodeGenerator
{
private:
    ICodeFactory* p;
public:
    CodeGenerator(ICodeFactory* factory) : p(factory) {}
    std::string generateProgram() {
        auto myclass = p->createClassUnit("MyClass", 0, JClassUnit::PUBLIC);

        auto methodUnit1 = p->createMethodUnit("testFunc1", "void", 0);
        myclass->add(methodUnit1, CClassUnit::PUBLIC);

        auto methodUnit2 = p->createMethodUnit("testFunc2", "void", CMethodUnit::STATIC);
        myclass->add(methodUnit2, CClassUnit::PRIVATE);

        auto methodUnit3 = p->createMethodUnit("testFunc3", "void", CMethodUnit::VIRTUAL | CMethodUnit::CONST);
        myclass->add(methodUnit3, CClassUnit::PUBLIC);

        auto methodUnit4 = p->createMethodUnit("testFunc4", "void", CMethodUnit::STATIC);
        auto printUnit = p->createPrintOperatorUnit(R"(Hello, World!\n)");

        methodUnit4->add(printUnit);

        myclass->add(methodUnit4, CClassUnit::PROTECTED);

        return myclass->compile();
    }
};
