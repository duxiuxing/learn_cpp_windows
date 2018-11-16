#pragma once

#include "resource.h"

namespace Gdiplus {
class Image;
}

class DrawJpegDlg : public CDialog
{
public:
    DrawJpegDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~DrawJpegDlg();

    // Dialog Data
    enum { IDD = IDD_DRAW_JPEG };
protected:
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnPaint();
    Gdiplus::Image* m_image;
};
