#include "stdafx.h"
#include "draw_rectangle_dlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"

DrawRectangleDlg::DrawRectangleDlg(CWnd* pParent /*=NULL*/)
    : CDialog(DrawRectangleDlg::IDD, pParent)
{}

BEGIN_MESSAGE_MAP(DrawRectangleDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void DrawRectangleDlg::OnPaint()
{
    CPaintDC dc(this);
    Graphics graphics(dc.GetSafeHdc());
    Pen      blackPen(Color(255, 0, 0, 0), 5);

    EXPECT_EQ(Gdiplus::Ok, graphics.DrawRectangle(&blackPen, 10, 10, 100, 50));
}
