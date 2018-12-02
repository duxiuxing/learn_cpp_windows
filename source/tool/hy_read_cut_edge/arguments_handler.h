#pragma once

#include <atlpath.h>
#include <gdiplus.h>

class ArgumentsHandler
{
public:
    ArgumentsHandler(int argc, char** argv);
    virtual ~ArgumentsHandler();

protected:
    Gdiplus::Image* m_logo;
};
