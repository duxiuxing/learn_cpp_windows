#include "stdafx.h"
#include "DrawingLineDlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

IMPLEMENT_DYNAMIC(CDrawingLineDlg, CDialog)

CDrawingLineDlg::CDrawingLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawingLineDlg::IDD, pParent)
{}

CDrawingLineDlg::~CDrawingLineDlg()
{}

BEGIN_MESSAGE_MAP(CDrawingLineDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CDrawingLineDlg::OnPaint()
{
	CPaintDC dc(this);
	Graphics graphics(dc.GetSafeHdc());
	Pen      pen(Color(255, 0, 0, 255));
	graphics.DrawLine(&pen, 0, 0, 200, 100);
}
