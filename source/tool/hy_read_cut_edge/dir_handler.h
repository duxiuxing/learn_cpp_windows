#pragma once

#include <atlpath.h>
#include <gdiplus.h>
#include <string>
#include <vector>

#include "png_image.h"

class DirectoryHandler
{
public:
    DirectoryHandler(const WCHAR* dirPath, Gdiplus::Image* newLogo);
    virtual ~DirectoryHandler();

protected:
    BOOL CheckFileName();
    BOOL CalculateMargin(CRect& margin);
    void CutEdge(const CRect& margin);

    Gdiplus::Image* m_newLogo;

    CPath m_dirPath;
    std::vector<CString> m_fileNames;

    std::vector<HyRead::PngImage*> m_images;
};
