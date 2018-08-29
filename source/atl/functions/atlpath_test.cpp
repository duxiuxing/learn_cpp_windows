#include "stdafx.h"
#include "gtest/gtest.h"

#include <atlpath.h>
using namespace ATL;

/*
    Functions
    ATLPath::AddBackslash   This function is an overloaded wrapper for PathAddBackslash.
    ATLPath::AddExtension   This function is an overloaded wrapper for PathAddExtension.
    ATLPath::Append This function is an overloaded wrapper for PathAppend.
    ATLPath::BuildRoot  This function is an overloaded wrapper for PathBuildRoot.
    ATLPath::Canonicalize   This function is an overloaded wrapper for PathCanonicalize.
    ATLPath::Combine    This function is an overloaded wrapper for PathCombine.
    ATLPath::CommonPrefix   This function is an overloaded wrapper for PathCommonPrefix.
    ATLPath::CompactPath    This function is an overloaded wrapper for PathCompactPath.
    ATLPath::CompactPathEx  This function is an overloaded wrapper for PathCompactPathEx.
    ATLPath::FileExists This function is an overloaded wrapper for PathFileExists.
    ATLPath::FindExtension  This function is an overloaded wrapper for PathFindExtension.
    ATLPath::FindFileName   This function is an overloaded wrapper for PathFindFileName.
    ATLPath::GetDriveNumber This function is an overloaded wrapper for PathGetDriveNumber.
    ATLPath::IsDirectory    This function is an overloaded wrapper for PathIsDirectory.
    ATLPath::IsFileSpec This function is an overloaded wrapper for PathIsFileSpec.
    ATLPath::IsPrefix   This function is an overloaded wrapper for PathIsPrefix.
    ATLPath::IsRelative This function is an overloaded wrapper for PathIsRelative.
    ATLPath::IsRoot This function is an overloaded wrapper for PathIsRoot.
    ATLPath::IsSameRoot This function is an overloaded wrapper for PathIsSameRoot.
    ATLPath::IsUNC  This function is an overloaded wrapper for PathIsUNC.
    ATLPath::IsUNCServer    This function is an overloaded wrapper for PathIsUNCServer.
    ATLPath::IsUNCServerShare   This function is an overloaded wrapper for PathIsUNCServerShare.
    ATLPath::MakePretty This function is an overloaded wrapper for PathMakePretty.
    ATLPath::MatchSpec  This function is an overloaded wrapper for PathMatchSpec.
    ATLPath::QuoteSpaces    This function is an overloaded wrapper for PathQuoteSpaces.
    ATLPath::RelativePathTo This function is an overloaded wrapper for PathRelativePathTo.
    ATLPath::RemoveArgs This function is an overloaded wrapper for PathRemoveArgs.
    ATLPath::RemoveBackslash    This function is an overloaded wrapper for PathRemoveBackslash.
    ATLPath::RemoveBlanks   This function is an overloaded wrapper for PathRemoveBlanks.
    ATLPath::RemoveExtension    This function is an overloaded wrapper for PathRemoveExtension.

    ATLPath::RenameExtension    This function is an overloaded wrapper for PathRenameExtension.
    ATLPath::SkipRoot   This function is an overloaded wrapper for PathSkipRoot.
    ATLPath::StripPath  This function is an overloaded wrapper for PathStripPath.
    ATLPath::StripToRoot    This function is an overloaded wrapper for PathStripToRoot.
    ATLPath::UnquoteSpaces  This function is an overloaded wrapper for PathUnquoteSpaces.
*/

/*
    TestedMethod: ATLPath::RemoveFileSpec()
    Description: Removes the trailing file name and backslash from a path, if they are present.
    Steps:
        1. 通过GetModuleFileName()获得当前exe的路径
        2. 通过字符串截取来获得exe所在的文件夹路径
        3. 调用ATLPath::RemoveFileSpec()获得当前exe所在的文件夹路径
        4. 2和3的文件夹路径应当一致
*/
TEST(ATLPathTest, RemoveFileSpec) {
    // 1
    CString exePath;
    ASSERT_NE(::GetModuleFileName(NULL, exePath.GetBuffer(MAX_PATH), MAX_PATH), 0);
    exePath.ReleaseBuffer();

    // 2
    CString dirPath1;
    {
        ATL::CPath path(exePath);
        dirPath1 = exePath.Left(path.FindFileName() - 1);
    }

    // 3
    CPath dirPath2(exePath);
    ASSERT_NE(dirPath2.RemoveFileSpec(), FALSE);

    // 4
    EXPECT_EQ(0, dirPath2.m_strPath.Compare(dirPath1));
}
