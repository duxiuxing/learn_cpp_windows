#pragma once

#include <atlpath.h>

namespace GdiplusTest
{	
	// return fileFullPath.FileExists()
	BOOL GetResourceFileFullPath(PTSTR fileRelativePath, ATL::CPath& fileFullPath);
}
