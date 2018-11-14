#pragma once

#include "resource.h"

class FillHatchPatternDlg : public CDialog
{
public:
    enum { IDD = IDD_FILL_HATCH_PATTERN };
    FillHatchPatternDlg(CWnd* pParent = NULL);

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
};
