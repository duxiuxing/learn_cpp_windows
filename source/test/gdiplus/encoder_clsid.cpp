#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "gtest/gtest.h"
#include "helper.h"

TEST(UsingImageEncoders, GetEncoderClsid) {
    CLSID encoderClsid = GUID_NULL;
    INT result = Helper::GetEncoderClsid(L"image/png", &encoderClsid);

    ASSERT_TRUE(result != -1) << "The PNG encoder is not installed.";

	WCHAR guid[39] = {0};
    StringFromGUID2(encoderClsid, guid, 39);
    EXPECT_STREQ(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", guid);
}
