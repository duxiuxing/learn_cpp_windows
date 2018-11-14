#include "stdafx.h"
#include "draw_string_dlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"

DrawStringDlg::DrawStringDlg(CWnd* pParent /*=NULL*/)
    : CDialog(DrawStringDlg::IDD, pParent)
{}

BEGIN_MESSAGE_MAP(DrawStringDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void DrawStringDlg::OnPaint()
{
    CPaintDC   dc(this);
    Graphics   graphics(dc.GetSafeHdc());
    SolidBrush brush(Color(255, 0, 0, 255));
    FontFamily fontFamily(L"Times New Roman");
    Font       font(&fontFamily, 24, FontStyleRegular, UnitPixel);
    PointF     pointF(10.0f, 20.0f);

    EXPECT_EQ(Gdiplus::Ok, graphics.DrawString(L"Hello World!", -1, &font, pointF, &brush));
}
