#include "stdafx.h"
#include "draw_jpeg_dlg.h"
#include "helper.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"

DrawJpegDlg::DrawJpegDlg(CWnd* pParent /*=NULL*/)
    : CDialog(DrawJpegDlg::IDD, pParent)
    , m_image(NULL)
{
    ATL::CPath jpegFilePath;
    BOOL jpegFileExist = Helper::QueryResourceFile(_T("gdiplus\\Grapes.jpg"), jpegFilePath);
    EXPECT_EQ(TRUE, jpegFileExist);

    if (jpegFileExist)
    {
        m_image = new Image(jpegFilePath);
    }
}

DrawJpegDlg::~DrawJpegDlg()
{
    if (m_image)
    {
        delete m_image;
        m_image = NULL;
    }
}

BEGIN_MESSAGE_MAP(DrawJpegDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void DrawJpegDlg::OnPaint()
{
    CPaintDC dc(this);
    Graphics graphics(dc.GetSafeHdc());

    if (m_image)
    {
        EXPECT_EQ(Gdiplus::Ok, graphics.DrawImage(m_image, 60, 10));
    }
}
