#include "stdafx.h"

#include <cppunit/cppunit.h>
#include "DrawingLineDlg.h"
#include "DrawingStringDlg.h"

class GettingStarted
	: public CPPUNIT_NS::MfcDialogTestFixture
{
	CPPUNIT_TEST_SUITE(GettingStarted);
	{
		CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawingLine, CDrawingLineDlg, TIMEOUT_MS);
		CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawingString, CDrawingStringDlg, TIMEOUT_MS);
	}
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GettingStarted);
