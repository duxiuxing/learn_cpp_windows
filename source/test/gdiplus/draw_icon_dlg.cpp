#include "stdafx.h"
#include "draw_icon_dlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"

IMPLEMENT_DYNAMIC(CDrawIconDlg, CDialog)

CDrawIconDlg::CDrawIconDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CDrawIconDlg::IDD, pParent)
    , m_bitmap(NULL)
{
    HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_GDIPLUS_TEST));
    EXPECT_TRUE(hIcon != NULL);

    m_bitmap = new Bitmap(hIcon);
}

CDrawIconDlg::~CDrawIconDlg()
{
    if (m_bitmap)
    {
        delete m_bitmap;
        m_bitmap = NULL;
    }
}

BEGIN_MESSAGE_MAP(CDrawIconDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void CDrawIconDlg::OnPaint()
{
    CPaintDC dc(this);
    Graphics graphics(dc.GetSafeHdc());

    if (m_bitmap)
    {
        graphics.DrawImage(m_bitmap, 10, 10);
    }
}
