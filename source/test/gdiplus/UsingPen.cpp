#include "stdafx.h"

#include <cppunit/cppunit.h>
#include "DrawRectangleDlg.h"

class UsingPen
	: public CPPUNIT_NS::MfcDialogTestFixture
{
	CPPUNIT_TEST_SUITE(UsingPen);
	{
		CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawRectangle, CDrawRectangleDlg, TIMEOUT_MS);
	}
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UsingPen);
