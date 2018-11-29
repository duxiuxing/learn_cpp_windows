// hy_read_cut_edge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arguments_handler.h"

#include "png_image.h"

CWinApp theApp;

using namespace std;

void Test()
{

}

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
            /*
            {                
                int pageCount = 548;
                bool saveFile = true;
                CRect margin(11, 0, 11, 0);

                CString pngPathFormat;
                if (pageCount > 100)
                    pngPathFormat = L"J:\\mipad\\ing\\1\\%0.3d.png";
                else
                    pngPathFormat = L"J:\\mipad\\ing\\1\\%0.2d.png";

                Gdiplus::Image logoImage(L"J:\\weixin.png");
                CSize logoSize(48, 48);
                
                if (saveFile)
                {
                    for (int index = 1; index <= pageCount; ++index)
                    {
                        CString path;
                        path.Format(pngPathFormat, index);

                        HyRead::PngImage pngImage(path);
                        pngImage.EraseLogo(&logoImage, logoSize);                        
                       
                        pngImage.CutEdge(&margin);
                        pngImage.Save();
                    }
                }
                else
                {
                    CRect lastMarginCalc(0, 0, 0, 0);
                    for (int index = 1; index <= 30; ++index)
                    {
                        CString path;
                        path.Format(pngPathFormat, index);

                        HyRead::PngImage pngImage(path);
                        pngImage.EraseLogo(&logoImage, logoSize);

                        CRect marginCalc(0, 0, 0, 0);
                        pngImage.CalculateMargin(marginCalc);
                        if (lastMarginCalc != marginCalc)
                        {
                            lastMarginCalc = marginCalc;
                            wprintf(L"margin = rect(%d, %d, %d, %d)\n", marginCalc.left, marginCalc.top, marginCalc.right, marginCalc.bottom);
                        }
                    }
                }

                for (int index = 1; index <= pageCount; ++index)
                {
                    CString path;
                    path.Format(pngPathFormat, index);

                    HyRead::PngImage pngImage(path);                    
                    CRect margin(89, 0, 89, 0);
                    pngImage.CutEdge(&margin);
                    pngImage.Save();
                }
                
            }
            */
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
