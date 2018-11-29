#pragma once

#include <atlpath.h>
#include <gdiplus.h>

namespace HyRead {

class PngImage
{
public:
    PngImage(const WCHAR* filePath);
    virtual ~PngImage();

    // 擦除图片右下角的锁Logo，如果擦除失败，则使用newLogo来进行遮挡
    BOOL EraseLogo(Gdiplus::Image* newLogo);

    BOOL CalculateMargin(CRect& margin);

    BOOL CutEdge(const CRect& margin);
    BOOL Save(const WCHAR* filePath = NULL);

protected:
    BOOL EraseLogoWithHorizontalLine(CDC* dc, const CRect& logoRect);
    BOOL EraseLogoWithVerticalLine(CDC* dc, const CRect& logoRect);
    BOOL EraseLogoWithNewLogo(CDC* dc, const CRect& logoRect, Gdiplus::Image* newLogo);

    INT CalculateMarginLeft(CDC* dc);
    INT CalculateMarginTop(CDC* dc);
    INT CalculateMarginRight(CDC* dc);
    INT CalculateMarginBottom(CDC* dc);

    CPath m_filePath;
    Gdiplus::Image* m_image;
};

} // namespace HyRead {
