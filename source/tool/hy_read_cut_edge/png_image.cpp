#include "stdafx.h"
#include "png_image.h"
#include "helper.h"

namespace HyRead {

PngImage::PngImage(const WCHAR* filePath)
    : m_filePath(filePath)
    , m_image(NULL)
{
    if (m_filePath.FileExists())
    {
        m_image = new Gdiplus::Image(filePath);
    }

    wprintf(L"%s\n", (const WCHAR*)m_filePath);
}

PngImage::~PngImage()
{
    if (m_image)
    {
        delete m_image;
        m_image = NULL;
    }
}

BOOL PngImage::EraseLogoWithHorizontalLine(CDC* dc, const CRect& logoRect)
{
    // ��logoRect�Ϸ�2�����ش�ȡ�߶�A��׼����������������logoRect����
    COLORREF* horizontalLine = new COLORREF[logoRect.Width()];
    int y = logoRect.top - 2;
    for (int xOffset = 0; xOffset < logoRect.Width(); ++xOffset)
    {
        horizontalLine[xOffset] = dc->GetPixel(logoRect.left + xOffset, y);
    }

    // ��logoRect�Ϸ�1�����ش�ȡ�߶�B�����B�ĸ��������Ƿ���Aһ��
    y = logoRect.top - 1;
    for (int xOffset = 0; xOffset < logoRect.Width(); ++xOffset)
    {
        if (horizontalLine[xOffset] != dc->GetPixel(logoRect.left + xOffset, y))
        {
            delete horizontalLine;
            return FALSE;
        }
    }

    // ��logoRect�·�1�����ش�ȡ�߶�C�����C�ĸ��������Ƿ���Aһ��
    y = logoRect.bottom;
    for (int xOffset = 0; xOffset < logoRect.Width(); ++xOffset)
    {
        if (horizontalLine[xOffset] != dc->GetPixel(logoRect.left + xOffset, y))
        {
            delete horizontalLine;
            return FALSE;
        }
    }

    // ����Logo
    for (int yOffset = 0; yOffset < logoRect.Height(); ++yOffset)
    {
        for (int xOffset = 0; xOffset < logoRect.Width(); ++xOffset)
        {
            dc->SetPixel(logoRect.left + xOffset, logoRect.top + yOffset, horizontalLine[xOffset]);
        }
    }

    delete horizontalLine;
    return TRUE;
}

BOOL PngImage::EraseLogoWithVerticalLine(CDC* dc, const CRect& logoRect)
{
    // ��logoRect���2�����ش�ȡ�߶�A��׼����������������logoRect����
    COLORREF* verticalLine = new COLORREF[logoRect.Height()];
    int x = logoRect.left - 2;
    for (int yOffset = 0; yOffset < logoRect.Height(); ++yOffset)
    {
        verticalLine[yOffset] = dc->GetPixel(x, logoRect.top + yOffset);
    }

    // ��logoRect���1�����ش�ȡ�߶�B�����B�ĸ��������Ƿ���Aһ��
    x = logoRect.left - 1;
    for (int yOffset = 0; yOffset < logoRect.Height(); ++yOffset)
    {
        if (verticalLine[yOffset] != dc->GetPixel(x, logoRect.top + yOffset))
        {
            return FALSE;
        }
    }

    // ��logoRect�Ҳ�1�����ش�ȡ�߶�C�����C�ĸ��������Ƿ���Aһ��
    x = logoRect.right;
    for (int yOffset = 0; yOffset < logoRect.Height(); ++yOffset)
    {
        if (verticalLine[yOffset] != dc->GetPixel(x, logoRect.top + yOffset))
        {
            return FALSE;
        }
    }

    for (int xOffset = 0; xOffset < logoRect.Width(); ++xOffset)
    {
        for (int yOffset = 0; yOffset < logoRect.Height(); ++yOffset)
        {
            dc->SetPixel(logoRect.left + xOffset, logoRect.top + yOffset, verticalLine[yOffset]);
        }
    }

    return TRUE;
}

BOOL PngImage::EraseLogoWithNewLogo(CDC* dc, const CRect& logoRect, Gdiplus::Image* newLogo)
{
    if (newLogo)
    {
        CRect newRect(0, 0, newLogo->GetWidth(), newLogo->GetHeight());
        newRect.OffsetRect(logoRect.CenterPoint() - newRect.CenterPoint());

        Gdiplus::Graphics graphics(dc->GetSafeHdc());
        graphics.DrawImage(newLogo, newRect.left, newRect.top, newRect.Width(), newRect.Height());
    }

    return TRUE;
}

BOOL PngImage::EraseLogo(Gdiplus::Image* newLogo)
{
    const CRect logoRect(1456, 1874, 1456 + 32, 1874 + 42);

    if (!m_image
        || logoRect.right >= (LONG)m_image->GetWidth()
        || logoRect.bottom >= (LONG)m_image->GetHeight())
    {
        return FALSE;
    }    

    CDC dc;
    dc.Attach(::GetWindowDC(NULL));
    
    CDC memdc;
    memdc.CreateCompatibleDC(&dc);

    CBitmap bitmap;
    bitmap.CreateCompatibleBitmap(&dc, m_image->GetWidth(), m_image->GetHeight());
    CBitmap* oldBitmap = memdc.SelectObject(&bitmap);

    BOOL ret = FALSE;
    {
        Gdiplus::Graphics graphics(memdc.GetSafeHdc());
        graphics.DrawImage(m_image, 0, 0);

        if (EraseLogoWithHorizontalLine(&memdc, logoRect)
            || EraseLogoWithVerticalLine(&memdc, logoRect))
        {
            ret = TRUE;
        }
        else if (newLogo)
        {
            EraseLogoWithNewLogo(&memdc, logoRect, newLogo);
            wprintf(L"EraseLogoWithNewLogo\n");
            ret = TRUE;
        }

        if (ret)
        {
            delete m_image;
            m_image = new Gdiplus::Bitmap((HBITMAP)bitmap.GetSafeHandle(), NULL);
        }
    }

    memdc.SelectObject(oldBitmap);
    bitmap.DeleteObject();
    memdc.DeleteDC();
    ::ReleaseDC(NULL, dc.Detach());

    return ret;
}

INT PngImage::CalculateMarginLeft(CDC* dc)
{
    COLORREF leftTop = dc->GetPixel(0, 0);    
    for (UINT left = 0; left < m_image->GetWidth(); ++left)
    {
        for (UINT y = 0; y < m_image->GetHeight(); ++y)
        {
            if (leftTop != dc->GetPixel(left, y))
            {
                return left;
            }
        }
    }

    return 0;
}

INT PngImage::CalculateMarginTop(CDC* dc)
{
    COLORREF leftTop = dc->GetPixel(0, 0);
    for (UINT top = 0; top < m_image->GetHeight(); ++top)    
    {
        for (UINT x = 0; x < m_image->GetWidth(); ++x)
        {
            if (leftTop != dc->GetPixel(x, top))
            {
                return top;
            }
        }
    }

    return 0;
}

INT PngImage::CalculateMarginRight(CDC* dc)
{
    COLORREF rightTop = dc->GetPixel(m_image->GetWidth() - 1, 0);
    for (UINT right = 0; right < m_image->GetWidth(); ++right)
    {
        for (UINT y = 0; y < m_image->GetHeight(); ++y)
        {
            if (rightTop != dc->GetPixel(m_image->GetWidth() - right - 1, y))
            {
                return right;
            }
        }
    }

    return 0;
}

INT PngImage::CalculateMarginBottom(CDC* dc)
{
    COLORREF rightBottom = dc->GetPixel(m_image->GetWidth() - 1, m_image->GetHeight() - 1);
    for (UINT bottom = 0; bottom < m_image->GetHeight(); ++bottom) 
    {
        for (UINT x = 0; x < m_image->GetWidth(); ++x)
        {
            if (rightBottom != dc->GetPixel(x, m_image->GetHeight() - bottom - 1))
            {
                return bottom;
            }
        }
    }

    return 0;
}

BOOL PngImage::CalculateMargin(CRect& margin)
{
    if (!m_image)
    {
        return FALSE;
    }

    CDC dc;
    dc.Attach(::GetWindowDC(NULL));

    CDC memdc;
    memdc.CreateCompatibleDC(&dc);

    CBitmap bitmap;
    bitmap.CreateCompatibleBitmap(&dc, m_image->GetWidth(), m_image->GetHeight());
    CBitmap* oldBitmap = memdc.SelectObject(&bitmap);

    {
        Gdiplus::Graphics graphics(memdc.GetSafeHdc());
        graphics.DrawImage(m_image, 0, 0);

        margin.left   = CalculateMarginLeft(&memdc);
        margin.top    = CalculateMarginTop(&memdc);
        margin.right  = CalculateMarginRight(&memdc);
        margin.bottom = CalculateMarginBottom(&memdc);
    }

    memdc.SelectObject(oldBitmap);
    bitmap.DeleteObject();
    memdc.DeleteDC();
    ::ReleaseDC(NULL, dc.Detach());

    return TRUE;
}

BOOL PngImage::CutEdge(const CRect& margin)
{    
    if (!m_image)
    {
        return FALSE;
    }
        
    CRect cropRect;
    cropRect.left   = margin.left; 
    cropRect.top    = margin.top; 
    cropRect.right  = m_image->GetWidth() - margin.right;
    cropRect.bottom = m_image->GetHeight() - margin.bottom;

    CDC dc;
    dc.Attach(::GetWindowDC(NULL));

    CDC memdc;
    memdc.CreateCompatibleDC(&dc);

    CBitmap bitmap;
    bitmap.CreateCompatibleBitmap(&dc, cropRect.Width(), cropRect.Height());
    CBitmap* oldBitmap = memdc.SelectObject(&bitmap);

    {
        Gdiplus::Graphics graphics(memdc.GetSafeHdc());
        graphics.DrawImage(m_image, 0, 0, cropRect.left, cropRect.top, cropRect.Width(), cropRect.Height(), Gdiplus::UnitPixel);

        delete m_image;
        m_image = new Gdiplus::Bitmap((HBITMAP)bitmap.GetSafeHandle(), NULL);
    }

    memdc.SelectObject(oldBitmap);
    bitmap.DeleteObject();
    memdc.DeleteDC();
    ::ReleaseDC(NULL, dc.Detach());

    return TRUE;
}

BOOL PngImage::Save(const WCHAR* filePath)
{
    CLSID encoderClsid;
    Gdiplus::Helper::GetEncoderClsid(L"image/png", &encoderClsid);

    if (filePath)
    {
        return (m_image->Save(filePath, &encoderClsid, NULL) == Gdiplus::Ok);
    }
    else
    {
        return (m_image->Save(m_filePath, &encoderClsid, NULL) == Gdiplus::Ok);
    }
}

} // namespace HyRead {
