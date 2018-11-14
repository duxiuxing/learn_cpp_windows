#include "stdafx.h"
#include "gtest/gtest.h"

#include <atlpath.h>
using namespace ATL;

/*
    TestedMethod: ATLPath::RemoveFileSpec()
    Description: 利用ATLPath::RemoveFileSpec()来获得父亲文件夹路径
    Steps:
        1. 通过GetModuleFileName()获得当前exe的路径
        2. 通过字符串截取来获得exe所在的文件夹路径
        3. 调用ATLPath::RemoveFileSpec()获得当前exe所在的文件夹路径
        4. 2和3的文件夹路径应当一致
*/
TEST(ATLPathTest, GetParentDirectory)
{
    // 1
    CString exePath;
    ASSERT_NE(::GetModuleFileName(NULL, exePath.GetBuffer(MAX_PATH), MAX_PATH), 0);
    exePath.ReleaseBuffer();

    // 2
    CString dirPath1;
    {
        CPath path(exePath);
        dirPath1 = exePath.Left(path.FindFileName() - 1);
    }

    // 3
    CPath dirPath2(exePath);
    ASSERT_NE(dirPath2.RemoveFileSpec(), FALSE);

    // 4
    EXPECT_EQ(0, dirPath2.m_strPath.Compare(dirPath1));
}
