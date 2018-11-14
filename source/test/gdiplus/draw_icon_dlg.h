#pragma once

#include "resource.h"

namespace Gdiplus {
class Bitmap;
}

class DrawIconDlg : public CDialog
{
public:
    enum { IDD = IDD_DRAW_ICON };
    DrawIconDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~DrawIconDlg();      

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();

    Gdiplus::Bitmap* m_bitmap;
};
