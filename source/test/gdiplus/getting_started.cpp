#include "stdafx.h"

#include <cppunit/cppunit.h>
#include "draw_line_dlg.h"
#include "draw_string_dlg.h"

class GettingStarted
    : public CPPUNIT_NS::MfcDialogTestFixture
{
    CPPUNIT_TEST_SUITE(GettingStarted);
    {
        CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawLine, CDrawLineDlg, MS_TIMEOUT);
        CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawString, CDrawStringDlg, MS_TIMEOUT);
    }
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GettingStarted);
