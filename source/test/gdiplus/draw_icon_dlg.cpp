#include "stdafx.h"
#include "draw_icon_dlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"

DrawIconDlg::DrawIconDlg(CWnd* pParent /*=NULL*/)
    : CDialog(DrawIconDlg::IDD, pParent)
    , m_bitmap(NULL)
{
    HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_GDIPLUS_TEST));
    EXPECT_TRUE(hIcon != NULL);

    m_bitmap = new Bitmap(hIcon);
}

DrawIconDlg::~DrawIconDlg()
{
    if (m_bitmap)
    {
        delete m_bitmap;
        m_bitmap = NULL;
    }
}

BEGIN_MESSAGE_MAP(DrawIconDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void DrawIconDlg::OnPaint()
{
    CPaintDC dc(this);
    Graphics graphics(dc.GetSafeHdc());

    if (m_bitmap)
    {
        EXPECT_EQ(Gdiplus::Ok, graphics.DrawImage(m_bitmap, 10, 10));
    }
}
