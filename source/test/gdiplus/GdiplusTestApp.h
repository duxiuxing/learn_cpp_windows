#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

class CGdiplusTestApp : public CWinApp
{
public:
	CGdiplusTestApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

protected:
	ULONG_PTR m_gdiplusToken;
};
