#pragma once

#include <atlpath.h>

class ArgumentsHandler
{
public:
    ArgumentsHandler(int argc, char** argv);
    virtual ~ArgumentsHandler();

protected:
    CPath* m_dirPath;
    CPath* m_filePath;
    CPath* m_logoPath;
};
