#include "stdafx.h"
#include "dll_app.h"

#include <gdiplus.h>
using namespace Gdiplus;

#pragma comment (lib, "Gdiplus.lib")

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CDllApp, CWinApp)
END_MESSAGE_MAP()

CDllApp::CDllApp() : m_gdiplusToken(NULL)
{}

CDllApp theApp;

BOOL CDllApp::InitInstance()
{
    CWinApp::InitInstance();

    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

    return TRUE;
}

int CDllApp::ExitInstance()
{
    ::GdiplusShutdown(m_gdiplusToken);

    return CWinApp::ExitInstance();
}
