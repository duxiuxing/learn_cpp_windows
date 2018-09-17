#pragma once

#include "resource.h"

class CDrawLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CDrawLineDlg)

public:
	CDrawLineDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDrawLineDlg();

	// Dialog Data
	enum {IDD = IDD_DRAW_LINE};

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
};
