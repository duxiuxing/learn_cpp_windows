#include "stdafx.h"

#include <cppunit/cppunit.h>
#include "draw_rectangle_dlg.h"

class UsingPen
	: public CPPUNIT_NS::MfcDialogTestFixture
{
	CPPUNIT_TEST_SUITE(UsingPen);
	{
		CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawRectangle, CDrawRectangleDlg, MS_TIMEOUT);
	}
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UsingPen);
