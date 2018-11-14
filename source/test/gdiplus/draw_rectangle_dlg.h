#pragma once

#include "resource.h"

class DrawRectangleDlg : public CDialog
{
public:
    enum { IDD = IDD_DRAW_RECTANGLE };
    DrawRectangleDlg(CWnd* pParent = NULL);    

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
};
