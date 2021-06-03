#pragma once

#include "unit.h"


class PrintOperatorUnit : public Unit
{
public:
    std::string compile(unsigned int level = 0) const = 0;
};

class CPrintOperatorUnit : public PrintOperatorUnit {
private:
    std::string m_text;
public:
    explicit CPrintOperatorUnit(const std::string& text) : m_text(text) { }
    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "printf( \"" + m_text + "\");\n";
    }
};

class SPrintOperatorUnit : public PrintOperatorUnit {
private:
    std::string m_text;
public:
    explicit SPrintOperatorUnit(const std::string& text) : m_text(text) { }
    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "Console.WriteLine(\"" + m_text + "\");\n";
    }
};

class JPrintOperatorUnit : public PrintOperatorUnit {
private:
    std::string m_text;
public:
    explicit JPrintOperatorUnit(const std::string& text) : m_text(text) { }
    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "System.out.println(\"" + m_text + "\");\n";
    }
};
