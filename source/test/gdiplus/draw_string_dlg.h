#pragma once

#include "resource.h"

class CDrawStringDlg : public CDialog
{
    DECLARE_DYNAMIC(CDrawStringDlg)

public:
    CDrawStringDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDrawStringDlg();

    // Dialog Data
    enum {IDD = IDD_DRAW_STRING};
protected:
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnPaint();
};
