#include "stdafx.h"
#include "helper.h"

#include <gdiplus.h>
using namespace Gdiplus;

BOOL Helper::GetResourceFileFullPath(PTSTR fileRelativePath, ATL::CPath& fileFullPath) {
    ATL::CPath relativePath;
    relativePath.Combine(_T("resource"), fileRelativePath);

    ATL::CPath resDirPath;
    ::GetModuleFileName(NULL, resDirPath.m_strPath.GetBuffer(MAX_PATH), MAX_PATH);
    resDirPath.m_strPath.ReleaseBuffer();
    resDirPath.RemoveFileSpec();

    fileFullPath.Combine(resDirPath, relativePath);

    BOOL fileExists = fileFullPath.FileExists();
    while (!fileExists) {
        if (resDirPath.RemoveFileSpec()) {
            fileFullPath.Combine(resDirPath, relativePath);
            fileExists = fileFullPath.FileExists();
        } else {
            return FALSE;
        }
    }

    return fileExists;
}

INT Helper::GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    UINT num = 0;   // number of image encoders
    UINT size = 0;  // size of the image encoder array in bytes
    GetImageEncodersSize(&num, &size);
    if (size == 0) {
        return -1; // Failure
    }

    ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL) {
        return -1; // Failure
    }

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;  // Success
        }
    }

    free(pImageCodecInfo);
    return -1;  // Failure
}
