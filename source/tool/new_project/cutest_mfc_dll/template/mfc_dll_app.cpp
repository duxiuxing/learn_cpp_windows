#include "stdafx.h"
#include "mfc_dll_app.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMfcDllApp, CWinApp)
END_MESSAGE_MAP()

CMfcDllApp theApp;

CMfcDllApp::CMfcDllApp()
{}

BOOL CMfcDllApp::InitInstance()
{
    CWinApp::InitInstance();

    return TRUE;
}
