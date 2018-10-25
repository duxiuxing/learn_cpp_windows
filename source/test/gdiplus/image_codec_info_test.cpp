#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"
#include "helper.h"

class ImageCodecInfoTest : public testing::Test {
protected:
    ImageCodecInfo* m_imageCodecInfos;
    UINT m_imageCodecInfoCount;

public:
    ImageCodecInfoTest()
        : m_imageCodecInfos(NULL)
        , m_imageCodecInfoCount(0) {}

    virtual void SetUp() override {
        UINT bytes = 0;
        GetImageEncodersSize(&m_imageCodecInfoCount, &bytes);
        if (bytes != 0) {
            m_imageCodecInfos = (ImageCodecInfo*)(malloc(bytes));
            GetImageEncoders(m_imageCodecInfoCount, bytes, m_imageCodecInfos);
        }
    }

    virtual void TearDown() override {
        if (m_imageCodecInfos) {
            free(m_imageCodecInfos);
            m_imageCodecInfos = NULL;
            m_imageCodecInfoCount = 0;
        }
    }

    ImageCodecInfo* FindImageCodecInfo(const WCHAR* mimeType) {
        for (UINT i = 0; i < m_imageCodecInfoCount; ++i) {
            if (wcscmp(m_imageCodecInfos[i].MimeType, mimeType) == 0) {
                return (m_imageCodecInfos + i);
            }
        }
        return NULL;
    }

    void CheckCodecInfo(ImageCodecInfo& imageCodecInfo) {
        ImageCodecInfo* infoExpect = FindImageCodecInfo(imageCodecInfo.MimeType);
        ASSERT_TRUE(infoExpect != NULL);

        EXPECT_TRUE(::IsEqualCLSID(infoExpect->Clsid, imageCodecInfo.Clsid));
        EXPECT_TRUE(::IsEqualGUID(infoExpect->FormatID, imageCodecInfo.FormatID));
        EXPECT_STREQ(infoExpect->CodecName, imageCodecInfo.CodecName);
        EXPECT_STREQ(infoExpect->DllName, imageCodecInfo.DllName);
        EXPECT_STREQ(infoExpect->FormatDescription, imageCodecInfo.FormatDescription);
        EXPECT_STREQ(infoExpect->FilenameExtension, imageCodecInfo.FilenameExtension);
        EXPECT_STREQ(infoExpect->MimeType, imageCodecInfo.MimeType);
        EXPECT_EQ(infoExpect->Flags, imageCodecInfo.Flags);
        EXPECT_EQ(infoExpect->Version, imageCodecInfo.Version);
        EXPECT_EQ(infoExpect->SigCount, imageCodecInfo.SigCount);
        EXPECT_EQ(infoExpect->SigSize, imageCodecInfo.SigSize);
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

    CheckCodecInfo(bmpCodecInfo);
}

TEST_F(ImageCodecInfoTest, JpegCodecInfo) {
    ImageCodecInfo* codecInfo = FindImageCodecInfo(L"image/jpeg");
    ASSERT_TRUE(codecInfo != NULL);


}

TEST_F(ImageCodecInfoTest, GifCodecInfo) {
    ImageCodecInfo* codecInfo = FindImageCodecInfo(L"image/gif");
    ASSERT_TRUE(codecInfo != NULL);


}

TEST_F(ImageCodecInfoTest, TiffCodecInfo) {
    ImageCodecInfo* codecInfo = FindImageCodecInfo(L"image/tiff");
    ASSERT_TRUE(codecInfo != NULL);


}

TEST_F(ImageCodecInfoTest, PngCodecInfo) {
    ImageCodecInfo* codecInfo = FindImageCodecInfo(L"image/png");
    ASSERT_TRUE(codecInfo != NULL);


}
