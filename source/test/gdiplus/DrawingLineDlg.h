#pragma once

#include "resource.h"

class CDrawingLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CDrawingLineDlg)

public:
	CDrawingLineDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDrawingLineDlg();

// Dialog Data
	enum { IDD = IDD_DRAWING_LINE };

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
};
