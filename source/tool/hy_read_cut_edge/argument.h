#pragma once

#include <string>
#include <vector>

template<class StringType>
class ArgumentT
{
public:
    typedef typename StringType::value_type CharType;
    typedef ArgumentT<StringType> ArgumentType;
    typedef std::vector<ArgumentType> List;

    ArgumentT(List& argList, int index, const CharType* text)
        : m_argList(argList), m_index(index), m_text(text)
    {}

    const ArgumentType* Next() const
    {
        int nextIndex = m_index + 1;
        if (nextIndex > 0 && nextIndex < static_cast<int>(m_argList.size()))
        {
            return &m_argList[nextIndex];
        }
        else
        {
            return nullptr;
        }
    }

    const ArgumentType* Previous() const
    {
        int prevIndex = m_index - 1;
        if (prevIndex > 0 && prevIndex < static_cast<int>(m_argList.size()))
        {
            return &m_argList[prevIndex];
        }
        else
        {
            return nullptr;
        }
    }

    const CharType* Text() const
    {
        return m_text.c_str();
    }

    bool IsEqualTo(const CharType* text) const
    {
        return (0 == m_text.compare(text));
    }

protected:
    const List& m_argList;
    int m_index;
    StringType m_text;
};

typedef ArgumentT<std::string> Argument;
typedef ArgumentT<std::wstring> ArgumentW;
