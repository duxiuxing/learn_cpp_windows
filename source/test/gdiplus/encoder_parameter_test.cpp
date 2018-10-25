#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"
#include "helper.h"

class EncoderParameterTest : public testing::Test {
protected:
    Bitmap* m_bitmap;
    EncoderParameters* m_encoderParameters;

public:
    EncoderParameterTest()
        : m_bitmap(NULL)
        , m_encoderParameters(NULL) {}

    virtual void SetUp() override {
        m_bitmap = new Bitmap(1, 1);
    }

    virtual void TearDown() override {
        if (m_encoderParameters) {
            free(m_encoderParameters);
            m_encoderParameters = NULL;
        }

        if (m_bitmap) {
            delete m_bitmap;
            m_bitmap = NULL;
        }
    }

    EncoderParameters* GetEncoderParameterList(const WCHAR* mimeType) {
        if (m_encoderParameters) {
            return m_encoderParameters;
        }

        // Get the Encoder CLSID.
        CLSID clsidEncoder = {0};
        Helper::GetEncoderClsid(mimeType, &clsidEncoder);

        // How big (in bytes) is the Encoder's parameter list?
        UINT bytes = m_bitmap->GetEncoderParameterListSize(&clsidEncoder);
        if (bytes)
        {
            // Allocate a buffer large enough to hold the parameter list.
            m_encoderParameters = (EncoderParameters*)malloc(bytes);

            // Get the parameter list for the Encoder.
            m_bitmap->GetEncoderParameterList(&clsidEncoder, bytes, m_encoderParameters);
        }

        return m_encoderParameters;
    }
};

TEST_F(EncoderParameterTest, BmpEncoderParameters) {
    EncoderParameters* bmpEncoderParameters = GetEncoderParameterList(L"image/bmp");
    ASSERT_TRUE(NULL == bmpEncoderParameters);
}

TEST_F(EncoderParameterTest, JpegCodecInfo) {
    EncoderParameters* jpegEncoderParameters = GetEncoderParameterList(L"image/jpeg");
    ASSERT_TRUE(NULL != jpegEncoderParameters);

    EXPECT_EQ(5, jpegEncoderParameters->Count);
}

TEST_F(EncoderParameterTest, GifCodecInfo) {
    EncoderParameters* gifEncoderParameters = GetEncoderParameterList(L"image/gif");
    ASSERT_TRUE(NULL != gifEncoderParameters);
}

TEST_F(EncoderParameterTest, TiffCodecInfo) {
    EncoderParameters* tiffEncoderParameters = GetEncoderParameterList(L"image/tiff");
    ASSERT_TRUE(NULL != tiffEncoderParameters);
}

TEST_F(EncoderParameterTest, PngCodecInfo) {
    EncoderParameters* pngEncoderParameters = GetEncoderParameterList(L"image/png");
    ASSERT_TRUE(NULL != pngEncoderParameters);
}

TEST(ImageCoders, EncoderParameters) {
    // Create Bitmap (inherited from Image) object so that we can call
    // GetParameterListSize and GetParameterList.
    Bitmap* bitmap = new Bitmap(1, 1);
	
    // Get the JPEG encoder CLSID.
    CLSID encoderClsid = {0};
    Helper::GetEncoderClsid(L"image/jpeg", &encoderClsid);

    // How big (in bytes) is the JPEG encoder's parameter list?
    UINT listSize = bitmap->GetEncoderParameterListSize(&encoderClsid);
    EXPECT_EQ(200, listSize) << "The parameter list requires " << listSize << " bytes.";

    // Allocate a buffer large enough to hold the parameter list.
    EncoderParameters* pEncoderParameters = (EncoderParameters*)malloc(listSize);

    // Get the parameter list for the JPEG encoder.
    bitmap->GetEncoderParameterList(
        &encoderClsid, listSize, pEncoderParameters);

    // pEncoderParameters points to an EncoderParameters object, which
    // has a Count member and an array of EncoderParameter objects.
    // How many EncoderParameter objects are in the array?
    EXPECT_EQ(5, pEncoderParameters->Count) << "There are " << pEncoderParameters->Count
                                            << " EncoderParameter objects in the array.";

    free(pEncoderParameters);
    delete (bitmap);
}
