#include "stdafx.h"
#include "GdiplusTestApp.h"

#include <gdiplus.h>
using namespace Gdiplus;

#pragma comment (lib, "Gdiplus.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CGdiplusTestApp, CWinApp)
END_MESSAGE_MAP()

CGdiplusTestApp::CGdiplusTestApp() : m_gdiplusToken(NULL)
{}

CGdiplusTestApp theApp;

BOOL CGdiplusTestApp::InitInstance()
{
	CWinApp::InitInstance();

	// Initialize GDI+
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	return TRUE;
}

int CGdiplusTestApp::ExitInstance()
{
	GdiplusShutdown(m_gdiplusToken);

	return CWinApp::ExitInstance();
}
