#pragma once

#include "unit.h"
#include <vector>


class MethodUnit : public Unit
{
public:
    using Flags = unsigned int;
    virtual void add(const std::shared_ptr<Unit>& unit, Flags flags = 0);
    virtual std::string compile(unsigned int level = 0) const = 0;
    virtual ~MethodUnit() = default;
};

class CMethodUnit : public MethodUnit
{
private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;

    std::vector<std::shared_ptr<Unit> > m_body;
public:
    enum Modifier {
        STATIC  = 1,
        VIRTUAL = 1 << 1,
        CONST   = 1 << 2
        };
public:
    CMethodUnit(const std::string& name, const std::string& returnType, Flags flags) :
            m_name(name), m_returnType(returnType), m_flags(flags) { }
    void add(const std::shared_ptr<Unit>& unit, Flags flags = 0) {
        m_body.push_back(unit);
    }
    std::string compile(unsigned int level = 0) const {
        std::string result = generateShift(level);
        if (m_flags & STATIC) {
            result += "static ";
        } else if (m_flags & VIRTUAL) {
            result += "virtual ";
        }
        result += m_returnType + " ";
        result += m_name + "()";
        if (m_flags & CONST) {
            result += " const";
        }
        result += " {\n";
        for (const auto& b : m_body) {
            result += b->compile(level + 1);
        }
        result += generateShift(level) + "}\n";
        return result;
    }

};

class SMethodUnit : public MethodUnit
{
private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;

    std::vector<std::shared_ptr<Unit> > m_body;
public:
    enum Modifier {
        STATIC   = 1,
        VIRTUAL  = 1 << 1,
        ABSTRACT = 1 << 3,
        OVERRIDE = 1 << 4,
        SEALED   = 1 << 5
    };
public:
    SMethodUnit(const std::string& name, const std::string& returnType, Flags flags) :
            m_name(name), m_returnType(returnType), m_flags(flags) { }
    void add(const std::shared_ptr<Unit>& unit, Flags flags = 0) {
        m_body.push_back(unit);
    }
    std::string compile(unsigned int level = 0) const {
        std::string result;
        if (m_flags & STATIC) {
            result += "static ";
        }
        else if (m_flags & VIRTUAL) {
            result += "virtual ";
        }
        else if (m_flags & ABSTRACT) {
            result += "abstract ";
        }
        if (m_flags & OVERRIDE) {
            result += "override ";
        }
        else if (m_flags & SEALED) {
            result += "sealed ";
        }
        result += m_returnType + " ";
        result += m_name + "()";
        result += " {\n";
        for (const auto& b : m_body) {
            result += b->compile(level + 1);
        }
        result += generateShift(level) + "}\n";
        return result;
    }

};

class JMethodUnit : public MethodUnit
{
private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;

    std::vector<std::shared_ptr<Unit> > m_body;
public:
    enum Modifier {
        STATIC   = 1,
        ABSTRACT = 1 << 3,
        FINAL    = 1 << 6
    };
public:
    JMethodUnit(const std::string& name, const std::string& returnType, Flags flags) :
            m_name(name), m_returnType(returnType), m_flags(flags) { }
    void add(const std::shared_ptr<Unit>& unit, Flags flags = 0) {
        m_body.push_back(unit);
    }
    std::string compile(unsigned int level = 0) const {
        std::string result;
        if (m_flags & STATIC) {
            result += "static ";
        }
        if (m_flags & ABSTRACT) {
            result += "abstract ";
        }
        if (m_flags & FINAL) {
            result += "final ";
        }
        result += m_returnType + " ";
        result += m_name + "()";
        result += " {\n";
        for (const auto& b : m_body) {
            result += b->compile(level + 1);
        }
        result += generateShift(level) + "}\n";
        return result;
    }

 };
