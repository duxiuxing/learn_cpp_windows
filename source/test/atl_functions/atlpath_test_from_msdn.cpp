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
    Output:
        1. 若当前路径不是顶级路径，RemoveFileSpec()返回非0，调用RemoveFileSpec()之后，得到父亲文件夹路径；
        2. 若当前路径是顶级路径，RemoveFileSpec()返回FALSE；
*/
TEST(ATLPathTest, RemoveFileSpec)
{
	// 本地路径
	{
		CPath path(_T("C:\\Windows\\notepad.exe"));

		EXPECT_NE(path.RemoveFileSpec(), FALSE);
		EXPECT_STREQ(_T("C:\\Windows"), path.m_strPath);

		EXPECT_NE(path.RemoveFileSpec(), FALSE);
		EXPECT_STREQ(_T("C:\\"), path.m_strPath);

		EXPECT_EQ(FALSE, path.RemoveFileSpec());
	}

	// 共享路径
	{
		CPath path(_T("\\\\localhost\\share\\Wallpaper.jpg"));

		EXPECT_NE(path.RemoveFileSpec(), FALSE);
		EXPECT_STREQ(_T("\\\\localhost\\share"), path.m_strPath);

		EXPECT_NE(path.RemoveFileSpec(), FALSE);
		EXPECT_STREQ(_T("\\\\localhost"), path.m_strPath);

		EXPECT_NE(path.RemoveFileSpec(), FALSE);
		EXPECT_STREQ(_T("\\\\"), path.m_strPath);

		EXPECT_EQ(FALSE, path.RemoveFileSpec());
	}
}
