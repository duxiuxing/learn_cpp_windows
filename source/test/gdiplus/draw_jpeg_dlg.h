#pragma once

#include "resource.h"

namespace Gdiplus {
class Image;
}

class CDrawJpegDlg : public CDialog
{
    DECLARE_DYNAMIC(CDrawJpegDlg)

public:
    CDrawJpegDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDrawJpegDlg();

    // Dialog Data
    enum {IDD = IDD_DRAW_JPEG};
protected:
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnPaint();
    Gdiplus::Image* m_image;
};
