#include "stdafx.h"

#include <cppunit/cppunit.h>
#include "fill_solid_color_dlg.h"
#include "fill_hatch_pattern_dlg.h"

class UsingBrush
	: public CPPUNIT_NS::MfcDialogTestFixture
{
	CPPUNIT_TEST_SUITE(UsingBrush);
	{
		CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(FillSolidColor, FillSolidColorDlg, MS_TIMEOUT);
        CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(FillHatchPattern, FillHatchPatternDlg, MS_TIMEOUT);
	}
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UsingBrush);
