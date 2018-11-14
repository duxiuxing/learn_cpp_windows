#include "stdafx.h"
#include "draw_jpeg_dlg.h"
#include "helper.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"

IMPLEMENT_DYNAMIC(CDrawJpegDlg, CDialog)

CDrawJpegDlg::CDrawJpegDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CDrawJpegDlg::IDD, pParent)
    , m_image(NULL)
{
    ATL::CPath jpegFilePath;
    BOOL jpegFileExist = Helper::GetResourceFileFullPath(_T("gdiplus\\Grapes.jpg"), jpegFilePath);
    EXPECT_EQ(TRUE, jpegFileExist);

    if (jpegFileExist)
    {
        m_image = new Image(jpegFilePath);
    }
}

CDrawJpegDlg::~CDrawJpegDlg()
{
    if (m_image)
    {
        delete m_image;
        m_image = NULL;
    }
}

BEGIN_MESSAGE_MAP(CDrawJpegDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void CDrawJpegDlg::OnPaint()
{
    CPaintDC   dc(this);
    Graphics   graphics(dc.GetSafeHdc());

    if (m_image)
    {
        graphics.DrawImage(m_image, 60, 10);
    }
}
