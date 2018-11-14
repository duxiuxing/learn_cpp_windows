#pragma once

#include "resource.h"

class DrawStringDlg : public CDialog
{
public:
    enum { IDD = IDD_DRAW_STRING };
    DrawStringDlg(CWnd* pParent = NULL);

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
};
