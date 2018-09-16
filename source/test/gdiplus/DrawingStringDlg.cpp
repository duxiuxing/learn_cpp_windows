#include "stdafx.h"
#include "DrawingStringDlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

IMPLEMENT_DYNAMIC(CDrawingStringDlg, CDialog)

CDrawingStringDlg::CDrawingStringDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawingStringDlg::IDD, pParent)
{}

CDrawingStringDlg::~CDrawingStringDlg()
{}

BEGIN_MESSAGE_MAP(CDrawingStringDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CDrawingStringDlg::OnPaint()
{
	CPaintDC   dc(this);
	Graphics   graphics(dc.GetSafeHdc());
	SolidBrush brush(Color(255, 0, 0, 255));
	FontFamily fontFamily(L"Times New Roman");
	Font       font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF     pointF(10.0f, 20.0f);

	graphics.DrawString(L"Hello World!", -1, &font, pointF, &brush);
}
