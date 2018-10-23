#include "stdafx.h"
#include "draw_rectangle_dlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"

IMPLEMENT_DYNAMIC(CDrawRectangleDlg, CDialog)

CDrawRectangleDlg::CDrawRectangleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawRectangleDlg::IDD, pParent)
{}

CDrawRectangleDlg::~CDrawRectangleDlg()
{}

BEGIN_MESSAGE_MAP(CDrawRectangleDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CDrawRectangleDlg::OnPaint()
{
	CPaintDC dc(this);
	Graphics graphics(dc.GetSafeHdc());
	Pen blackPen(Color(255, 0, 0, 0), 5);
	Status status = graphics.DrawRectangle(&blackPen, 10, 10, 100, 50);
	EXPECT_EQ(Gdiplus::Ok, status);
}
