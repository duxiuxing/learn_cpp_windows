#include "stdafx.h"
#include "file_handler.h"
#include "png_image.h"

FileHandler::FileHandler(const WCHAR* filePath, Gdiplus::Image* newLogo)
{
    CPath path(filePath);
    if (!path.IsDirectory() && path.FileExists())
    {
        HyRead::PngImage pngImage(filePath);
        pngImage.EraseLogo(newLogo);

        CRect margin(0, 0, 0, 0);
        pngImage.CalculateMargin(margin);
        
        pngImage.CutEdge(margin);
        pngImage.Save();
    }
}
