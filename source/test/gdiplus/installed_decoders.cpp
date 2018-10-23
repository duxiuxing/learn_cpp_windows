#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"
#include <vector>

TEST(ImageCoders, InstalledDecoders) {
    UINT num = 0;   // number of image decoders
    UINT size = 0;  // size, in bytes, of the image decoder array

    // How many decoders are there?
    // How big (in bytes) is the array of all ImageCodecInfo objects?
    GetImageDecodersSize(&num, &size);

    // Create a buffer large enough to hold the array of ImageCodecInfo
    // objects that will be returned by GetImageDecoders.
    ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*)(malloc(size));

    // GetImageDecoders creates an array of ImageCodecInfo objects
    // and copies that array into a previously allocated buffer.
    // The third argument, imageCodecInfo, is a pointer to that buffer.
    GetImageDecoders(num, size, pImageCodecInfo);

    // Save the graphics file format (MimeType)
    // for each ImageCodecInfo object.
    std::vector<std::wstring> actualDecoders;
    for (UINT j = 0; j < num; ++j) {
        actualDecoders.push_back(pImageCodecInfo[j].MimeType);
    }
    sort(actualDecoders.begin(), actualDecoders.end());

    std::wstring decoders[] = {
        L"image/bmp",
        L"image/jpeg",
        L"image/gif",
        L"image/x-emf",
        L"image/x-wmf",
        L"image/tiff",
        L"image/png",
        L"image/x-icon"
    };
    size_t decoderCount = sizeof(decoders) / sizeof(decoders[0]);
    std::vector<std::wstring> expectDecoders(decoders, decoders + decoderCount);
    sort(expectDecoders.begin(), expectDecoders.end());

    EXPECT_TRUE(expectDecoders == actualDecoders);

    free(pImageCodecInfo);
}
