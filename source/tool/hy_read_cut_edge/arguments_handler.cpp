#include "stdafx.h"
#include "arguments_handler.h"
#include "arguments_parser.h"
#include "png_image.h"

ArgumentsHandler::ArgumentsHandler(int argc, char** argv)
    : m_dirPath(nullptr)
    , m_filePath(nullptr)
    , m_logo(nullptr)
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
                m_logo = new Gdiplus::Image(logoPath);
            }
        }
    }

    if (m_filePath)
    {
        HyRead::PngImage pngImage(*m_filePath);
        pngImage.EraseLogo(m_logo);

        CRect margin(0, 0, 0, 0);
        pngImage.CalculateMargin(margin);

        pngImage.CutEdge(margin);
        pngImage.Save();
        return;
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

    if (m_logo)
    {
        delete m_logo;
        m_logo = nullptr;
    }
}
