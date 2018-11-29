#include "stdafx.h"
#include "arguments_handler.h"
#include "arguments_parser.h"

ArgumentsHandler::ArgumentsHandler(int argc, char** argv)
    : m_dirPath(nullptr)
    , m_filePath(nullptr)
    , m_logoPath(nullptr)
{
    ArgumentsParser parser(argc, argv);
        
    if (parser.Has("-dir"))
    {
        const Argument* arg = parser.Get("-dir")->Next();
        if (arg)
        {
            CPath dirPath(CString(arg->Text()));
            if (dirPath.IsDirectory())
            {
                m_dirPath = new CPath(dirPath);
            }
        }
    }

    if (parser.Has("-file"))
    {
        const Argument* arg = parser.Get("-file")->Next();
        if (arg)
        {
            CPath filePath(CString(arg->Text()));
            if (!filePath.IsDirectory() && filePath.FileExists())
            {
                m_filePath = new CPath(filePath);
            }
        }
    }

    if (parser.Has("-logo"))
    {
        const Argument* arg = parser.Get("-logo")->Next();
        if (arg)
        {
            CPath logoPath(CString(arg->Text()));
            if (!logoPath.IsDirectory() && logoPath.FileExists())
            {
                m_logoPath = new CPath(logoPath);
            }
        }
    }


}

ArgumentsHandler::~ArgumentsHandler()
{
    if (m_dirPath)
    {
        delete m_dirPath;
        m_dirPath = nullptr;
    }

    if (m_filePath)
    {
        delete m_filePath;
        m_filePath = nullptr;
    }

    if (m_logoPath)
    {
        delete m_logoPath;
        m_logoPath = nullptr;
    }
}
