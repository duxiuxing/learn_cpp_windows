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
        if (bytes) {
            // Allocate a buffer large enough to hold the parameter list.
            m_encoderParameters = (EncoderParameters*)malloc(bytes);

            // Get the parameter list for the Encoder.
            m_bitmap->GetEncoderParameterList(&clsidEncoder, bytes, m_encoderParameters);
        }

        return m_encoderParameters;
    }

    void CheckEncoderParameter(EncoderParameter& expectParam, EncoderParameter& actualParam) {
        WCHAR guid[39] = {0};
        StringFromGUID2(actualParam.Guid, guid, 39);
        EXPECT_TRUE(::IsEqualGUID(expectParam.Guid, actualParam.Guid)) << "Actual Guid is " << guid;

        EXPECT_EQ(expectParam.NumberOfValues, actualParam.NumberOfValues);
        EXPECT_EQ(expectParam.Type, actualParam.Type);

        if (expectParam.Value) {
            switch (expectParam.Type) {
            case EncoderParameterValueTypeLong:
                EXPECT_TRUE(0 == memcmp(expectParam.Value, actualParam.Value, expectParam.NumberOfValues * sizeof(LONG)));
                break;
            case EncoderParameterValueTypeLongRange:
                EXPECT_TRUE(0 == memcmp(expectParam.Value, actualParam.Value, 2 * sizeof(LONG)));
                break;
            default:
                break;
            }
        }
    }
};

TEST_F(EncoderParameterTest, BmpEncoderParameters) {
    EncoderParameters* bmpEncoderParameters = GetEncoderParameterList(L"image/bmp");
    ASSERT_TRUE(NULL == bmpEncoderParameters);
}

TEST_F(EncoderParameterTest, JpegEncoderParameters) {
    EncoderParameters* jpegEncoderParameters = GetEncoderParameterList(L"image/jpeg");
    ASSERT_TRUE(NULL != jpegEncoderParameters);

    EXPECT_EQ(5, jpegEncoderParameters->Count);

    const LONG transformation[] = {
        EncoderValueTransformRotate90,        // 13
        EncoderValueTransformRotate180,       // 14
        EncoderValueTransformRotate270,       // 15
        EncoderValueTransformFlipHorizontal,  // 16
        EncoderValueTransformFlipVertical,    // 17
    };
    EncoderParameter param0;
    param0.Guid             = EncoderTransformation;
    param0.NumberOfValues   = 5;
    param0.Type             = EncoderParameterValueTypeLong;
    param0.Value = (VOID*)transformation;
    CheckEncoderParameter(param0, jpegEncoderParameters->Parameter[0]);

    const LONG quality[] = {0, 100};
    EncoderParameter param1;
    param1.Guid             = EncoderQuality;
    param1.NumberOfValues   = 1;
    param1.Type             = EncoderParameterValueTypeLongRange;
    param1.Value            = (VOID*)quality;
    CheckEncoderParameter(param1, jpegEncoderParameters->Parameter[1]);

    EncoderParameter param2;
    param2.Guid             = EncoderLuminanceTable;
    param2.NumberOfValues   = 0;
    param2.Type             = EncoderParameterValueTypeShort;
    param2.Value            = NULL;
    CheckEncoderParameter(param2, jpegEncoderParameters->Parameter[2]);

    EncoderParameter param3;
    param3.Guid             = EncoderChrominanceTable;
    param3.NumberOfValues   = 0;
    param3.Type             = EncoderParameterValueTypeShort;
    param3.Value            = NULL;
    CheckEncoderParameter(param3, jpegEncoderParameters->Parameter[3]);

#if (GDIPVER >= 0x0110)
    EncoderParameter param4;
    param4.Guid             = EncoderImageItems;
    param4.NumberOfValues   = 0;
    param4.Type             = EncoderParameterValueTypePointer;
    param4.Value            = NULL;
    CheckEncoderParameter(param4, jpegEncoderParameters->Parameter[4]);
#endif //(GDIPVER >= 0x0110)
}

TEST_F(EncoderParameterTest, GifEncoderParameters) {
    EncoderParameters* gifEncoderParameters = GetEncoderParameterList(L"image/gif");
    ASSERT_TRUE(NULL != gifEncoderParameters);

    EXPECT_EQ(2, gifEncoderParameters->Count);

#if (GDIPVER >= 0x0110)
    EncoderParameter param0;
    param0.Guid             = EncoderImageItems;
    param0.NumberOfValues   = 0;
    param0.Type             = EncoderParameterValueTypePointer;
    param0.Value            = NULL;
    CheckEncoderParameter(param0, gifEncoderParameters->Parameter[0]);
#endif //(GDIPVER >= 0x0110)

    LONG saveFlag = EncoderValueMultiFrame;
    EncoderParameter param1;
    param1.Guid             = EncoderSaveFlag;
    param1.NumberOfValues   = 1;
    param1.Type             = EncoderParameterValueTypeLong;
    param1.Value            = &saveFlag;
    CheckEncoderParameter(param1, gifEncoderParameters->Parameter[1]);
}

TEST_F(EncoderParameterTest, TiffEncoderParameters) {
    EncoderParameters* tiffEncoderParameters = GetEncoderParameterList(L"image/tiff");
    ASSERT_TRUE(NULL != tiffEncoderParameters);

    EXPECT_EQ(4, tiffEncoderParameters->Count);

    const LONG compression[] = {
        EncoderValueCompressionLZW,     // 2
        EncoderValueCompressionCCITT3,  // 3
        EncoderValueCompressionRle,     // 5
        EncoderValueCompressionCCITT4,  // 4
        EncoderValueCompressionNone,    // 6
    };
    EncoderParameter param0;
    param0.Guid             = EncoderCompression;
    param0.NumberOfValues   = 5;
    param0.Type             = EncoderParameterValueTypeLong;
    param0.Value            = (VOID*)compression;
    CheckEncoderParameter(param0, tiffEncoderParameters->Parameter[0]);

    const LONG colorDepth[] = {1, 4, 8, 24, 32};
    EncoderParameter param1;
    param1.Guid             = EncoderColorDepth;
    param1.NumberOfValues   = 5;
    param1.Type             = EncoderParameterValueTypeLong;
    param1.Value            = (VOID*)colorDepth;
    CheckEncoderParameter(param1, tiffEncoderParameters->Parameter[1]);

    LONG saveFlag = EncoderValueMultiFrame;
    EncoderParameter param2;
    param2.Guid             = EncoderSaveFlag;
    param2.NumberOfValues   = 1;
    param2.Type             = EncoderParameterValueTypeLong;
    param2.Value            = (VOID*)&saveFlag;
    CheckEncoderParameter(param2, tiffEncoderParameters->Parameter[2]);

#if (GDIPVER >= 0x0110)
    EncoderParameter param3;
    param3.Guid             = EncoderSaveAsCMYK;
    param3.NumberOfValues   = 1;
    param3.Type             = EncoderParameterValueTypeLong;
    param3.Value            = tiffEncoderParameters->Parameter[3].Value;
    CheckEncoderParameter(param3, tiffEncoderParameters->Parameter[3]);
#endif //(GDIPVER >= 0x0110)
}

TEST_F(EncoderParameterTest, PngEncoderParameters) {
    EncoderParameters* pngEncoderParameters = GetEncoderParameterList(L"image/png");
    ASSERT_TRUE(NULL != pngEncoderParameters);

    EXPECT_EQ(1, pngEncoderParameters->Count);

#if (GDIPVER >= 0x0110)
    EncoderParameter param0 = pngEncoderParameters->Parameter[0];
    param0.Guid             = EncoderImageItems;
    param0.NumberOfValues   = 0;
    param0.Type             = EncoderParameterValueTypePointer;
    param0.Value            = NULL;
    CheckEncoderParameter(param0, pngEncoderParameters->Parameter[0]);
#endif //(GDIPVER >= 0x0110)
}
