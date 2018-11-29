#pragma once

#include <atlpath.h>
#include <gdiplus.h>

namespace HyRead {

class PngImage
{
public:
    PngImage(const WCHAR* filePath);
    virtual ~PngImage();

    BOOL EraseLogo(Gdiplus::Image* newLogo, const CSize& newLogoSize);

    BOOL CalculateMargin(CRect& rc);

    BOOL CutEdge(const CRect* margin = NULL);
    BOOL Save(const WCHAR* filePath = NULL);

protected:
    BOOL EraseLogoWithHorizontalLine(CDC* dc, const CRect& logoRect);
    BOOL EraseLogoWithVerticalLine(CDC* dc, const CRect& logoRect);
    BOOL EraseLogoWithNewLogo(CDC* dc, const CRect& logoRect, Gdiplus::Image* newLogo, const CSize& newLogoSize);

    INT CalculateMarginLeft(CDC* dc);
    INT CalculateMarginTop(CDC* dc);
    INT CalculateMarginRight(CDC* dc);
    INT CalculateMarginBottom(CDC* dc);

    CPath m_filePath;
    Gdiplus::Image* m_image;
    CRect m_rcMargin;
};

} // namespace HyRead {
