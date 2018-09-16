#pragma once

#include "resource.h"

class CDrawingStringDlg : public CDialog
{
	DECLARE_DYNAMIC(CDrawingStringDlg)

public:
	CDrawingStringDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDrawingStringDlg();

	// Dialog Data
	enum {IDD = IDD_DRAWING_STRING};
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
};
