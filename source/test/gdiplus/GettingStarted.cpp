#include "stdafx.h"

#include <cppunit/cppunit.h>
#include "DrawingLineDlg.h"

class GettingStarted
	: public CPPUNIT_NS::MfcDialogTestFixture
{
	CPPUNIT_TEST_SUITE(GettingStarted);
	{
		CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawingLine, CDrawingLineDlg, 2000);
	}
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GettingStarted);
