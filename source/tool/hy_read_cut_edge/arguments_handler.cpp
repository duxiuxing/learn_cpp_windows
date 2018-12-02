#include "stdafx.h"
#include "arguments_handler.h"
#include "arguments_parser.h"
#include "dir_handler.h"
#include "file_handler.h"
#include "png_image.h"

ArgumentsHandler::ArgumentsHandler(int argc, char** argv)
    : m_logo(nullptr)
{
    ArgumentsParser parser(argc, argv);
    
    if (parser.Has("-logo"))
    {
        const Argument* arg = parser.Get("-logo")->Next();
        if (arg)
        {
            CPath logoPath(CString(arg->Text()));
            if (!logoPath.IsDirectory() && logoPath.FileExists())
            {
                m_logo = new Gdiplus::Image(logoPath);
            }
        }
    }

    if (parser.Has("-dir"))
    {
        const Argument* arg = parser.Get("-dir")->Next();
        if (arg)
        {
            DirectoryHandler(CString(arg->Text()), m_logo);
        }
    }

    if (parser.Has("-file"))
    {
        const Argument* arg = parser.Get("-file")->Next();
        if (arg)
        {
            FileHandler(CString(arg->Text()), m_logo);
        }
    }
}

ArgumentsHandler::~ArgumentsHandler()
{
    if (m_logo)
    {
        delete m_logo;
        m_logo = nullptr;
    }
}
