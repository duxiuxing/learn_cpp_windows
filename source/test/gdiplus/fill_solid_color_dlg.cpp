#include "stdafx.h"
#include "fill_solid_color_dlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"

FillSolidColorDlg::FillSolidColorDlg(CWnd* pParent /*=NULL*/)
    : CDialog(FillSolidColorDlg::IDD, pParent)
{}

BEGIN_MESSAGE_MAP(FillSolidColorDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void FillSolidColorDlg::OnPaint()
{
    CPaintDC   dc(this);
    Graphics   graphics(dc.GetSafeHdc());
    SolidBrush solidBrush(Color(255, 255, 0, 0));

    EXPECT_EQ(Gdiplus::Ok, graphics.FillEllipse(&solidBrush, 0, 0, 100, 60));
}
