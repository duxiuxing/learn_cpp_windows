#include "stdafx.h"
#include "Helper.h"

BOOL GdiplusTest::GetResourceFileFullPath(PTSTR fileRelativePath, ATL::CPath& fileFullPath)
{
	ATL::CPath relativePath;
	relativePath.Combine(_T("resource"), fileRelativePath);

	ATL::CPath resDirPath;	
	::GetModuleFileName(NULL, resDirPath.m_strPath.GetBuffer(MAX_PATH), MAX_PATH);
	resDirPath.m_strPath.ReleaseBuffer();
	resDirPath.RemoveFileSpec();

	fileFullPath.Combine(resDirPath, relativePath);

	BOOL fileExists = fileFullPath.FileExists();
	while (!fileExists)
	{
		if (resDirPath.RemoveFileSpec())
		{
			fileFullPath.Combine(resDirPath, relativePath);
			fileExists = fileFullPath.FileExists();
		}
		else
		{
			return FALSE;
		}
	}

	return fileExists;
}
