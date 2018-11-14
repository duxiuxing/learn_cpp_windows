#pragma once

#include "resource.h"

class FillSolidColorDlg : public CDialog
{
public:
    enum { IDD = IDD_FILL_SOLID_COLOR };
    FillSolidColorDlg(CWnd* pParent = NULL);

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
};
