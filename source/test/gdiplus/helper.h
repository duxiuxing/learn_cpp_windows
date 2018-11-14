#pragma once

#include <atlpath.h>

namespace Helper {

// return fileFullPath.FileExists()
BOOL QueryResourceFile(PTSTR fileRelativePath, ATL::CPath& fileFullPath);

/*
    Retrieving the Class Identifier for an Encoder.
    If the function fails, it returns �C1.
    Or the function returns the index of the ImageCodecInfo object and
    copies the CLSID into the variable pointed to by pClsid.
*/
INT GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

}
