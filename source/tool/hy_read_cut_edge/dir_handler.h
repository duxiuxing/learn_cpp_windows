#pragma once

#include <gdiplus.h>

class DirectoryHandler
{
public:
    DirectoryHandler(const WCHAR* dirPath, Gdiplus::Image* newLogo);
};
