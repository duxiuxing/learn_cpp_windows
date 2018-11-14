#pragma once

#include "resource.h"

class DrawLineDlg : public CDialog
{
public:
    enum { IDD = IDD_DRAW_LINE };
    DrawLineDlg(CWnd* pParent = NULL);

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
};
