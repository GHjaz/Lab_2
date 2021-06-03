#pragma once

#include "unit.h"
#include <vector>


class ClassUnit : public Unit{
  public:
    using Flags = unsigned int;
    virtual void add(const std::shared_ptr<Unit>& unit, Flags flags) = 0;
    virtual std::string compile(unsigned int level = 0) const = 0;
    virtual ~ClassUnit() = default;
};


class CClassUnit : public ClassUnit {
public:

    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };
    static const std::vector< std::string > ACCESS_MODIFIERS;

public:
    explicit CClassUnit(const std::string &name) : m_name(name) {
        m_fields.resize(ACCESS_MODIFIERS.size());
    }
    void add(const std::shared_ptr< Unit > &unit, Flags flags) {
        int accessModifier = PRIVATE;
        if (flags < ACCESS_MODIFIERS.size()) {
            accessModifier = flags;
        }
        m_fields[accessModifier].push_back(unit);
    }
    std::string compile(unsigned int level = 0) const {
        std::string result = generateShift(level) + "class " + m_name + " {\n";
        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (m_fields[i].empty()) {
                continue;
            }
            result += ACCESS_MODIFIERS[i] + ":\n";
            for (const auto &f : m_fields[i]) {
                result += f->compile(level + 1);
            }
            result += "\n";
        }
        result += generateShift(level) + "};\n";
        return result;
        }

private:
    std::string m_name;
    using Fields = std::vector< std::shared_ptr< Unit >>; //.. Вектор умных указателей на выделенный объект типа Unit
    std::vector< Fields > m_fields;

};


class SClassUnit : public ClassUnit
{
private:
    std::string m_name;
    using Fields = std::vector<std::shared_ptr<Unit> >;
    std::vector<Fields> m_fields;
    Flags access_flags;
    Flags m_flags;
    static const std::vector<std::string> ACCESS_MODIFIERS;
public:
    enum AccessModifier {
        DEFAULT,
        PUBLIC,
        PROTECTED,
        PRIVATE,
        INTERNAL
    };
    enum Modifier {
        STATIC   = 1,
        ABSTRACT = 1 << 1,
        SEALED    = 1 << 2
    };
public:
    explicit SClassUnit(const std::string name, ClassUnit::Flags modifier, ClassUnit::Flags access_modifier) : m_name(name)
    {
        m_fields.resize(ACCESS_MODIFIERS.size());
        access_flags = access_modifier;
        m_flags = modifier;
    }
    void add(const std::shared_ptr<Unit>& unit, Flags flags)
    {
        int accessModifier = DEFAULT;
        if (flags < ACCESS_MODIFIERS.size())
            accessModifier = flags;
        m_fields[accessModifier].push_back(unit);
    }
    std::string compile(unsigned int level = 0) const
    {
        std::string result = generateShift(level);
        switch (access_flags)
        {
            case PUBLIC:
                result += "public ";
                break;
            case PRIVATE:
                result += "private  ";
                break;
            case PROTECTED:
                result += "protected  ";
                break;
            case INTERNAL:
                result += "internal  ";
                break;
        }
        if (m_flags & STATIC)
            result += "static ";
        if (m_flags & ABSTRACT)
            result += "abstract ";
        if (m_flags & SEALED)
            result += "sealed ";
        result += "class " + m_name + " {\n";
        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); i++) {
            if (m_fields[i].empty())
                continue;
            for (const auto& f : m_fields[i]) {
                result += generateShift(level + 1) + ACCESS_MODIFIERS[i] + " " + f->compile(level + 1);
            }
        }
        result += generateShift(level) + "}\n";
        return result;
    }
};

class JClassUnit : public ClassUnit
{
private:
    std::string m_name;
    using Fields = std::vector<std::shared_ptr<Unit> >;
    std::vector<Fields> m_fields;
    Flags access_flags;
    Flags m_flags;
    static const std::vector<std::string> ACCESS_MODIFIERS;
public:
    enum AccessModifier {
        DEFAULT,
        PUBLIC,
        PROTECTED,
        PRIVATE
    };
    enum Modifier {
        STATIC   = 1,
        ABSTRACT = 1 << 1,
        FINAL    = 1 << 3
    };
public:
    explicit JClassUnit(const std::string name, ClassUnit::Flags modifier, ClassUnit::Flags access_modifier) : m_name(name)
    {
        m_fields.resize(ACCESS_MODIFIERS.size());
        access_flags = access_modifier;
        m_flags = modifier;
    }
    void add(const std::shared_ptr<Unit>& unit, Flags flags)
    {
        int accessModifier = DEFAULT;
        if (flags < ACCESS_MODIFIERS.size())
            accessModifier = flags;
        m_fields[accessModifier].push_back(unit);
    }
    std::string compile(unsigned int level = 0) const
    {
        std::string result = generateShift(level);
        switch (access_flags)
        {
            case PUBLIC:
                result += "public ";
                break;
            case PRIVATE:
                result += "private ";
                break;
            case PROTECTED:
                result += "protected ";
                break;
        }
        if (m_flags & STATIC)
            result += "static ";
        if (m_flags & ABSTRACT)
            result += "abstract ";
        if (m_flags & FINAL)
            result += "final ";
        result += "class " + m_name + " {\n";
        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); i++) {
            if (m_fields[i].empty())
                continue;
            for (const auto& f : m_fields[i]) {
                result += generateShift(level + 1) + ACCESS_MODIFIERS[i] + " " + f->compile(level + 1);
            }
        }
        result += generateShift(level) + "}\n";
        return result;
    }

};
