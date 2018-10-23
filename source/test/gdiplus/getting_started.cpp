#include "stdafx.h"

#include <cppunit/cppunit.h>
#include "draw_line_dlg.h"
#include "draw_string_dlg.h"

class GettingStarted
	: public CPPUNIT_NS::MfcDialogTestFixture
{
	CPPUNIT_TEST_SUITE(GettingStarted);
	{
		CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawLine, CDrawLineDlg, TIMEOUT_MS);
		CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawString, CDrawStringDlg, TIMEOUT_MS);
	}
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GettingStarted);
