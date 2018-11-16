#include "stdafx.h"
#include "mfc_dll_app.h"

#include <gdiplus.h>
using namespace Gdiplus;

#pragma comment (lib, "Gdiplus.lib")

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMfcDllApp, CWinApp)
END_MESSAGE_MAP()

CMfcDllApp::CMfcDllApp() : m_gdiplusToken(NULL)
{}

CMfcDllApp theApp;

BOOL CMfcDllApp::InitInstance()
{
    CWinApp::InitInstance();

    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

    return TRUE;
}

int CMfcDllApp::ExitInstance()
{
    ::GdiplusShutdown(m_gdiplusToken);

    return CWinApp::ExitInstance();
}
