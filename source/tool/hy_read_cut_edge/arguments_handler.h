#pragma once

#include <atlpath.h>
#include <gdiplus.h>

class ArgumentsHandler
{
public:
    ArgumentsHandler(int argc, char** argv);
    virtual ~ArgumentsHandler();

protected:
    CPath* m_dirPath;
    CPath* m_filePath;
    Gdiplus::Image* m_logo;
};
