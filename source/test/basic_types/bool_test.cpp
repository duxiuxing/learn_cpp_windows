#include "stdafx.h"
#include "gtest/gtest.h"

/*
    Description: 布尔值转字符串
    Output: TRUE显示为1，FALSE显示为0
*/
TEST(BasicTypesTest, BoolToString)
{
    CONST TCHAR expectString[] = _T("TRUE=1, FALSE=0");

    CString actualString;
    actualString.Format(_T("TRUE=%u, FALSE=%u"), TRUE, FALSE);

    EXPECT_STREQ(expectString, actualString);
}
