#include "stdafx.h"
#include "DrawingLineDlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

IMPLEMENT_DYNAMIC(CDrawingLineDlg, CDialogEx)

CDrawingLineDlg::CDrawingLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrawingLineDlg::IDD, pParent)
{}

CDrawingLineDlg::~CDrawingLineDlg()
{}

BEGIN_MESSAGE_MAP(CDrawingLineDlg, CDialogEx) 
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CDrawingLineDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages

	Graphics graphics(dc.GetSafeHdc());
	Pen      pen(Color(255, 0, 0, 255));
	graphics.DrawLine(&pen, 0, 0, 200, 100);
}
