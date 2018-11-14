#include "stdafx.h"
#include "fill_hatch_pattern_dlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"

FillHatchPatternDlg::FillHatchPatternDlg(CWnd* pParent /*=NULL*/)
    : CDialog(FillHatchPatternDlg::IDD, pParent)
{}

BEGIN_MESSAGE_MAP(FillHatchPatternDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void FillHatchPatternDlg::OnPaint()
{
    CPaintDC   dc(this);
    Graphics   graphics(dc.GetSafeHdc());
    HatchBrush hBrush(HatchStyleHorizontal, Color(255, 255, 0, 0),
                      Color(255, 128, 255, 255));

    EXPECT_EQ(Gdiplus::Ok, graphics.FillEllipse(&hBrush, 0, 0, 100, 60));
}
