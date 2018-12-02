// hy_read_cut_edge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arguments_handler.h"

CWinApp theApp;

int main(int argc, char** argv)
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: change error code to suit your needs
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
            ULONG_PTR gdiplusToken = 0;
            Gdiplus::GdiplusStartupInput gdiplusInput;
            Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusInput, NULL);

            ArgumentsHandler(argc, argv);

            Gdiplus::GdiplusShutdown(gdiplusToken);
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
