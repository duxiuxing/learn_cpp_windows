#pragma once

#ifndef __AFXWIN_H__
    #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"

class CMfcDllApp : public CWinApp
{
    DECLARE_MESSAGE_MAP()

public:
    CMfcDllApp();
    virtual BOOL InitInstance();
};
