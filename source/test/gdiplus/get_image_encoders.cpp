#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"
#include <vector>

TEST(UsingImageEncoders, GetImageEncoders)
{
    UINT numEncoders = 0;   // number of image encoders
    UINT size = 0;          // size, in bytes, of the image encoder array

    // How many encoders are there?
    // How big (in bytes) is the array of all ImageCodecInfo objects?
    GetImageEncodersSize(&numEncoders, &size);

    // Create a buffer large enough to hold the array of ImageCodecInfo
    // objects that will be returned by GetImageEncoders.
    ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*)(malloc(size));

    // GetImageEncoders creates an array of ImageCodecInfo objects
    // and copies that array into a previously allocated buffer.
    // The third argument, imageCodecInfo, is a pointer to that buffer.
    GetImageEncoders(numEncoders, size, pImageCodecInfo);

    // Check the graphics file format (MimeType)
    // for each ImageCodecInfo object.
    WCHAR* allMimeTypes[] =
    {
        L"image/bmp",
        L"image/jpeg",
        L"image/gif",
        L"image/tiff",
        L"image/png"
    };
    for (UINT j = 0; j < numEncoders; ++j)
    {
        EXPECT_STREQ(allMimeTypes[j], pImageCodecInfo[j].MimeType);
    }

    free(pImageCodecInfo);
}
