#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"
#include "helper.h"

class ImageCodecInfoTest : public testing::Test {
protected:
    ImageCodecInfo* m_imageCodecInfoList;
    UINT m_imageCodecInfoCount;

public:
    ImageCodecInfoTest()
        : m_imageCodecInfoList(NULL)
        , m_imageCodecInfoCount(0) {}

    virtual void SetUp() override {
        UINT bytes = 0;
        GetImageEncodersSize(&m_imageCodecInfoCount, &bytes);
        if (bytes != 0) {
            m_imageCodecInfoList = (ImageCodecInfo*)(malloc(bytes));
            GetImageEncoders(m_imageCodecInfoCount, bytes, m_imageCodecInfoList);
        }
    }

    virtual void TearDown() override {
        if (m_imageCodecInfoList) {
            free(m_imageCodecInfoList);
            m_imageCodecInfoList = NULL;
            m_imageCodecInfoCount = 0;
        }
    }

    ImageCodecInfo* FindImageCodecInfo(const WCHAR* mimeType) {
        for (UINT i = 0; i < m_imageCodecInfoCount; ++i) {
            if (wcscmp(m_imageCodecInfoList[i].MimeType, mimeType) == 0) {
                return (m_imageCodecInfoList + i);
            }
        }
        return NULL;
    }

    void CheckImageCodecInfo(ImageCodecInfo& expectInfo) {
        ImageCodecInfo* actualInfo = FindImageCodecInfo(expectInfo.MimeType);
        ASSERT_TRUE(actualInfo != NULL);

        WCHAR clsid[39] = {0};
        StringFromGUID2(actualInfo->Clsid, clsid, 39);
        EXPECT_TRUE(::IsEqualCLSID(expectInfo.Clsid, actualInfo->Clsid)) << "Actual Clsid is " << clsid;

        WCHAR formatID[39] = {0};
        StringFromGUID2(actualInfo->FormatID, formatID, 39);
        EXPECT_TRUE(::IsEqualGUID(expectInfo.FormatID, actualInfo->FormatID)) << "Actual FormatID is " << formatID;

        EXPECT_STREQ(expectInfo.CodecName, actualInfo->CodecName);
        EXPECT_STREQ(expectInfo.DllName, actualInfo->DllName);
        EXPECT_STREQ(expectInfo.FormatDescription, actualInfo->FormatDescription);
        EXPECT_STREQ(expectInfo.FilenameExtension, actualInfo->FilenameExtension);
        EXPECT_STREQ(expectInfo.MimeType, actualInfo->MimeType);
        EXPECT_EQ(expectInfo.Flags, actualInfo->Flags);
        EXPECT_EQ(expectInfo.Version, actualInfo->Version);
        EXPECT_EQ(expectInfo.SigCount, actualInfo->SigCount);
        EXPECT_EQ(expectInfo.SigSize, actualInfo->SigSize);
    }
};

TEST_F(ImageCodecInfoTest, BmpCodecInfo) {
    ImageCodecInfo bmpCodecInfo;

    CLSIDFromString(L"{557CF400-1A04-11D3-9A73-0000F81EF32E}", &bmpCodecInfo.Clsid);
    CLSIDFromString(L"{B96B3CAB-0728-11D3-9D7B-0000F81EF32E}", &bmpCodecInfo.FormatID);
    bmpCodecInfo.CodecName          = L"Built-in BMP Codec";
    bmpCodecInfo.DllName            = NULL;
    bmpCodecInfo.FormatDescription  = L"BMP";
    bmpCodecInfo.FilenameExtension  = L"*.BMP;*.DIB;*.RLE";
    bmpCodecInfo.MimeType           = L"image/bmp";
    bmpCodecInfo.Flags              = ImageCodecFlagsEncoder
                                      | ImageCodecFlagsDecoder
                                      | ImageCodecFlagsSupportBitmap
                                      | ImageCodecFlagsBuiltin;
    bmpCodecInfo.Version            = 1;
    bmpCodecInfo.SigCount           = 1;
    bmpCodecInfo.SigSize            = 2;

    CheckImageCodecInfo(bmpCodecInfo);
}

TEST_F(ImageCodecInfoTest, JpegCodecInfo) {
    ImageCodecInfo jpegCodecInfo;

    CLSIDFromString(L"{557CF401-1A04-11D3-9A73-0000F81EF32E}", &jpegCodecInfo.Clsid);
    CLSIDFromString(L"{B96B3CAE-0728-11D3-9D7B-0000F81EF32E}", &jpegCodecInfo.FormatID);
    jpegCodecInfo.CodecName         = L"Built-in JPEG Codec";
    jpegCodecInfo.DllName           = NULL;
    jpegCodecInfo.FormatDescription = L"JPEG";
    jpegCodecInfo.FilenameExtension = L"*.JPG;*.JPEG;*.JPE;*.JFIF";
    jpegCodecInfo.MimeType          = L"image/jpeg";
    jpegCodecInfo.Flags             = ImageCodecFlagsEncoder
                                      | ImageCodecFlagsDecoder
                                      | ImageCodecFlagsSupportBitmap
                                      | ImageCodecFlagsBuiltin;
    jpegCodecInfo.Version           = 1;
    jpegCodecInfo.SigCount          = 1;
    jpegCodecInfo.SigSize           = 2;

    CheckImageCodecInfo(jpegCodecInfo);
}

TEST_F(ImageCodecInfoTest, GifCodecInfo) {
    ImageCodecInfo gifCodecInfo;

    CLSIDFromString(L"{557CF402-1A04-11D3-9A73-0000F81EF32E}", &gifCodecInfo.Clsid);
    CLSIDFromString(L"{B96B3CB0-0728-11D3-9D7B-0000F81EF32E}", &gifCodecInfo.FormatID);
    gifCodecInfo.CodecName          = L"Built-in GIF Codec";
    gifCodecInfo.DllName            = NULL;
    gifCodecInfo.FormatDescription  = L"GIF";
    gifCodecInfo.FilenameExtension  = L"*.GIF";
    gifCodecInfo.MimeType           = L"image/gif";
    gifCodecInfo.Flags              = ImageCodecFlagsEncoder
                                      | ImageCodecFlagsDecoder
                                      | ImageCodecFlagsSupportBitmap
                                      | ImageCodecFlagsBuiltin;
    gifCodecInfo.Version            = 1;
    gifCodecInfo.SigCount           = 2;
    gifCodecInfo.SigSize            = 6;

    CheckImageCodecInfo(gifCodecInfo);
}

TEST_F(ImageCodecInfoTest, TiffCodecInfo) {
    ImageCodecInfo tiffCodecInfo;

    CLSIDFromString(L"{557CF405-1A04-11D3-9A73-0000F81EF32E}", &tiffCodecInfo.Clsid);
    CLSIDFromString(L"{B96B3CB1-0728-11D3-9D7B-0000F81EF32E}", &tiffCodecInfo.FormatID);
    tiffCodecInfo.CodecName         = L"Built-in TIFF Codec";
    tiffCodecInfo.DllName           = NULL;
    tiffCodecInfo.FormatDescription = L"TIFF";
    tiffCodecInfo.FilenameExtension = L"*.TIF;*.TIFF";
    tiffCodecInfo.MimeType          = L"image/tiff";
    tiffCodecInfo.Flags             = ImageCodecFlagsEncoder
                                      | ImageCodecFlagsDecoder
                                      | ImageCodecFlagsSupportBitmap
                                      | ImageCodecFlagsBuiltin;
    tiffCodecInfo.Version           = 1;
    tiffCodecInfo.SigCount          = 2;
    tiffCodecInfo.SigSize           = 2;

    CheckImageCodecInfo(tiffCodecInfo);
}

TEST_F(ImageCodecInfoTest, PngCodecInfo) {
    ImageCodecInfo pngCodecInfo;

    CLSIDFromString(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", &pngCodecInfo.Clsid);
    CLSIDFromString(L"{B96B3CAF-0728-11D3-9D7B-0000F81EF32E}", &pngCodecInfo.FormatID);
    pngCodecInfo.CodecName          = L"Built-in PNG Codec";
    pngCodecInfo.DllName            = NULL;
    pngCodecInfo.FormatDescription  = L"PNG";
    pngCodecInfo.FilenameExtension  = L"*.PNG";
    pngCodecInfo.MimeType           = L"image/png";
    pngCodecInfo.Flags              = ImageCodecFlagsEncoder
                                      | ImageCodecFlagsDecoder
                                      | ImageCodecFlagsSupportBitmap
                                      | ImageCodecFlagsBuiltin;
    pngCodecInfo.Version            = 1;
    pngCodecInfo.SigCount           = 1;
    pngCodecInfo.SigSize            = 8;

    CheckImageCodecInfo(pngCodecInfo);
}
