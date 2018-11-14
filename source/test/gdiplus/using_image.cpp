#include "stdafx.h"

#include <cppunit/cppunit.h>
#include "draw_jpeg_dlg.h"
#include "draw_icon_dlg.h"

class UsingImage
    : public CPPUNIT_NS::MfcDialogTestFixture
{
    CPPUNIT_TEST_SUITE(UsingImage);
    {
        CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawJpeg, DrawJpegDlg, MS_TIMEOUT);
        CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawIcon, DrawIconDlg, MS_TIMEOUT);
    }
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UsingImage);
