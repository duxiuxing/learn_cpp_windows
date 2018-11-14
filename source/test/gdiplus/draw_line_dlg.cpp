#include "stdafx.h"
#include "draw_line_dlg.h"

#include <gdiplus.h>
using namespace Gdiplus;

IMPLEMENT_DYNAMIC(CDrawLineDlg, CDialog)

CDrawLineDlg::CDrawLineDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CDrawLineDlg::IDD, pParent)
{}

CDrawLineDlg::~CDrawLineDlg()
{}

BEGIN_MESSAGE_MAP(CDrawLineDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void CDrawLineDlg::OnPaint()
{
    CPaintDC dc(this);
    Graphics graphics(dc.GetSafeHdc());

    // draw a line from (0, 0) to (200, 100)
    {
        Pen pen(Color(255, 0, 0, 255)); // solid blue
        graphics.DrawLine(&pen, 0, 0, 200, 100);
    }

    // draw a line from (20, 10) to (300, 100)
    {
        Pen pen(Color(255, 0, 0, 0)); // solid black
        graphics.DrawLine(&pen, 20, 10, 300, 100);
    }
}
