#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"
#include <vector>

TEST(ImageCoders, InstalledEncoders) {
    UINT num = 0;   // number of image encoders
    UINT size = 0;  // size, in bytes, of the image encoder array

    // How many encoders are there?
    // How big (in bytes) is the array of all ImageCodecInfo objects?
    GetImageEncodersSize(&num, &size);

    // Create a buffer large enough to hold the array of ImageCodecInfo
    // objects that will be returned by GetImageEncoders.
    ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*)(malloc(size));

    // GetImageEncoders creates an array of ImageCodecInfo objects
    // and copies that array into a previously allocated buffer.
    // The third argument, imageCodecInfo, is a pointer to that buffer.
    GetImageEncoders(num, size, pImageCodecInfo);

    // Save the graphics file format (MimeType)
    // for each ImageCodecInfo object.
    std::vector<std::wstring> actualEncoders;
    for (UINT j = 0; j < num; ++j) {
        actualEncoders.push_back(pImageCodecInfo[j].MimeType);
    }
    sort(actualEncoders.begin(), actualEncoders.end());

    std::wstring encoders[] = {
        L"image/bmp",
        L"image/jpeg",
        L"image/gif",
        L"image/tiff",
        L"image/png"
    };
    size_t encoderCount = sizeof(encoders) / sizeof(encoders[0]);
    std::vector<std::wstring> expectEncoders(encoders, encoders + encoderCount);
    sort(expectEncoders.begin(), expectEncoders.end());

    EXPECT_TRUE(expectEncoders == actualEncoders);

    free(pImageCodecInfo);
}
