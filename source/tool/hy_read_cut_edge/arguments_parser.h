#pragma once

#include "argument.h"

template<class StringType>
class ArgumentsParserT
{
public:
    typedef typename StringType::value_type CharType;
    typedef ArgumentT<StringType> ArgumentType;

    ArgumentsParserT(int argc, CharType** argv)
    {
        if (argc > 0)
        {
            m_argList.reserve(argc);
            for (int i = 0; i < argc; ++i)
            {
                m_argList.emplace_back(ArgumentType(m_argList, i, argv[i]));
            }
        }
    }

    bool Has(const CharType* text) const
    {
        return (Get(text) != nullptr);
    }

    const ArgumentType* Get(const CharType* text) const
    {
        for (auto& arg : m_argList)
        {
            if (arg.IsEqualTo(text))
            {
                return &arg;
            }
        }

        return nullptr;
    }

    int Count() const
    {
        return static_cast<int>(m_argList.size());
    }

    const ArgumentType* At(int index) const
    {
        return m_argList.at(index);
    }

protected:
    typename ArgumentType::List m_argList;
};

typedef ArgumentsParserT<std::string> ArgumentsParser;
typedef ArgumentsParserT<std::wstring> ArgumentsParserW;
