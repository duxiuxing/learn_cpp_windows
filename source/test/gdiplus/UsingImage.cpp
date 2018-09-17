﻿#include "stdafx.h"

#include <cppunit/cppunit.h>
#include "DrawJpegDlg.h"
#include "DrawIconDlg.h"

class UsingImage
	: public CPPUNIT_NS::MfcDialogTestFixture
{
	CPPUNIT_TEST_SUITE(UsingImage);
	{
		CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawJpeg, CDrawJpegDlg, TIMEOUT_MS);
		CPPUNIT_MFC_DIALOG_TEST_WITH_TIMEOUT(DrawIcon, CDrawIconDlg, TIMEOUT_MS);
	}
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UsingImage);
