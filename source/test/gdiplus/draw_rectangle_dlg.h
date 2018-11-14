#pragma once

#include "resource.h"

class CDrawRectangleDlg : public CDialog
{
    DECLARE_DYNAMIC(CDrawRectangleDlg)

public:
    CDrawRectangleDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDrawRectangleDlg();

    // Dialog Data
    enum {IDD = IDD_DRAW_RECTANGLE};
protected:
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnPaint();
};
