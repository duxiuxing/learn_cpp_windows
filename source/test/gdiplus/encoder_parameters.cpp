#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"
#include "helper.h"

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
