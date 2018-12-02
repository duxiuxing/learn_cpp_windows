#pragma once

#include <gdiplus.h>

class FileHandler
{
public:
    FileHandler(const WCHAR* filePath, Gdiplus::Image* newLogo);    
};
