#include "stdafx.h"
#include "draw_string_dlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

IMPLEMENT_DYNAMIC(CDrawStringDlg, CDialog)

CDrawStringDlg::CDrawStringDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawStringDlg::IDD, pParent)
{}

CDrawStringDlg::~CDrawStringDlg()
{}

BEGIN_MESSAGE_MAP(CDrawStringDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CDrawStringDlg::OnPaint()
{
	CPaintDC   dc(this);
	Graphics   graphics(dc.GetSafeHdc());
	SolidBrush brush(Color(255, 0, 0, 255));
	FontFamily fontFamily(L"Times New Roman");
	Font       font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF     pointF(10.0f, 20.0f);

	graphics.DrawString(L"Hello World!", -1, &font, pointF, &brush);
}
