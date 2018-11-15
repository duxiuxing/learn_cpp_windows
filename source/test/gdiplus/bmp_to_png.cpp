#include "stdafx.h"
#include "helper.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"

TEST(UsingImageEncoders, BmpToPng)
{
    ATL::CPath bmpFilePath;
    BOOL bmpFileExist = Helper::QueryResourceFile(_T("gdiplus\\Bird.bmp"), bmpFilePath);
    ASSERT_EQ(TRUE, bmpFileExist);

    // Get the CLSID of the PNG encoder.
    CLSID encoderClsid = GUID_NULL;
    INT result = Helper::GetEncoderClsid(L"image/png", &encoderClsid);
    ASSERT_TRUE(result != -1) << "The PNG encoder is not installed.";

    Image* image = new Image(bmpFilePath);

    // Construct .png path in the .exe folder.
    CString exePath;
    ASSERT_NE(0, ::GetModuleFileName(NULL, exePath.GetBuffer(MAX_PATH), MAX_PATH));
    exePath.ReleaseBuffer();

    CPath dirPath(exePath);
    ASSERT_EQ(TRUE, dirPath.RemoveFileSpec());
    ATL::CPath pngFilePath;
    pngFilePath.Combine(dirPath, L"Bird.png");

    if (pngFilePath.FileExists()) { ::DeleteFile(pngFilePath); }
    Status stat = image->Save(pngFilePath, &encoderClsid, NULL);

    EXPECT_EQ(Gdiplus::Ok, stat) << "Failure: stat = " << stat;

    delete image;
};
