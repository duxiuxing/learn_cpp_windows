#pragma once

#include "resource.h"

namespace Gdiplus {
class Bitmap;
}

class CDrawIconDlg : public CDialog
{
    DECLARE_DYNAMIC(CDrawIconDlg)

public:
    CDrawIconDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDrawIconDlg();

    // Dialog Data
    enum {IDD = IDD_DRAW_ICON};
protected:
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnPaint();
    Gdiplus::Bitmap* m_bitmap;
};
