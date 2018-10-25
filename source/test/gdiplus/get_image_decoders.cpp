#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"
#include <vector>

TEST(UsingImageDecoders, GetImageDecoders) {
    UINT numDecoders = 0;   // number of image decoders
    UINT size = 0;          // size, in bytes, of the image decoder array

    // How many decoders are there?
    // How big (in bytes) is the array of all ImageCodecInfo objects?
    GetImageDecodersSize(&numDecoders, &size);

    // Create a buffer large enough to hold the array of ImageCodecInfo
    // objects that will be returned by GetImageDecoders.
    ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*)(malloc(size));

    // GetImageDecoders creates an array of ImageCodecInfo objects
    // and copies that array into a previously allocated buffer.
    // The third argument, imageCodecInfo, is a pointer to that buffer.
    GetImageDecoders(numDecoders, size, pImageCodecInfo);

    // Check the graphics file format (MimeType)
    // for each ImageCodecInfo object.
    WCHAR* allMimeTypes[] = {
        L"image/bmp",
        L"image/jpeg",
        L"image/gif",
        L"image/x-emf",
        L"image/x-wmf",
        L"image/tiff",
        L"image/png",
        L"image/x-icon"
    };
    for (UINT j = 0; j < numDecoders; ++j) {
        EXPECT_STREQ(allMimeTypes[j], pImageCodecInfo[j].MimeType);
    }

    free(pImageCodecInfo);
}
