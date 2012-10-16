/*
 * QRTestController.cpp
 *
 *  Created on: Jul 15, 2011
 *      Author: root
 */

#include <config.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <algorithm>
#include <Printing/DocumentOptions.h>
#include "QRTestPrintDocument.h"
#include "QRTestController.h"
#include <Printing/PrinterStatusNotifier.h>
#include <Log/SMTTLogManager.h>
#include <config.h>
#include <qrencode.h>

using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::System;
using namespace Smartmatic::Log;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define BACKGROUND_IMAGE_PATH DATADIR"/"PACKAGE_NAME"/ui/qrbkground.bmp"

Glib::RefPtr<QRTestController> QRTestController::current_instance;
int QRTestController::test_id_suffix = 0;

ISMTTLog* QRTestController::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.QRTestController",PACKAGE_NAME);

QRTestController::QRTestController()
{
	m_BgnImagePath = BACKGROUND_IMAGE_PATH; //TODO: get from confiuration
}

QRTestController::~QRTestController()
{
	// TODO Auto-generated destructor stub
}

Glib::RefPtr<QRTestController> QRTestController::GetInstance ()
{
	if ( ! current_instance )
	{
		Glib::RefPtr<QRTestController> new_ref (new QRTestController ());
		current_instance = new_ref;
	}

	return current_instance;
}


//============================= Interface ====================================//

void QRTestController::ExecuteTest (std::list<QrTestParamsType> tests)
{
	QRTestPrintDocument test_doc ("Test ID");
	test_id_suffix = 0;
	Glib::RefPtr<Gdk::Pixbuf> bgn = Gdk::Pixbuf::create_from_file (m_BgnImagePath);

	for (std::list<QrTestParamsType>::const_iterator it = tests.begin ()
			; it != tests.end ()
			; it++)
	{
		for (int i = it->data_size.min; i <= it->data_size.max; i += it->data_size.step)
			for (int j = it->version.min; j <= it->version.max; j += it->version.step)
				for (int k = it->correction_level.min; k <= it->correction_level.max; k += it->correction_level.step)
				{
					if (it->image_based)
					{
						for (int p = it->pixel_size.min; p < it->pixel_size.max; p += it->pixel_size.step)
							if (it->use_background)
							{
								for (int q = it->margin_size.min; q < it->margin_size.max; q += it->margin_size.step)
								{
									std::stringstream ss;
									ss << "test - " << (++test_id_suffix);

									SafeBuffer data = GenData (i);
									QRCodeContent qr (data, p, q, (QRecLevel)k, j, bgn);
									test_doc.AddTestCase (test_id_suffix, ss.str (), qr, it->image_based, it->use_background);
								}
							}
							else
							{
								std::stringstream ss;
								ss << "test - " << (++test_id_suffix);

								SafeBuffer data = GenData (i);
								QRCodeContent qr (data, p, 0, (QRecLevel)k, j, bgn);
								test_doc.AddTestCase (test_id_suffix, ss.str (), qr, it->image_based, it->use_background);
							}
					}
					else
					{
						std::stringstream ss;
						ss << "test - " << (++test_id_suffix);

						SafeBuffer data = GenData (i);
						QRCodeContent qr (data, 0, 0, (QRecLevel)k, j, bgn);
						test_doc.AddTestCase (test_id_suffix, ss.str (), qr, it->image_based, it->use_background);
					}
				}
	}

	std::stringstream ss;
	ss << "Total test = " << test_id_suffix;

	logger->Debug (ss.str());

	test_doc.Print ();
}

std::vector<QRTestController::QrParamsRangeType> QRTestController::ParseRanges (
		std::vector<Glib::ustring> incomming_ranges)
{
	std::vector<QrParamsRangeType> ranges;

	for (std::vector<Glib::ustring>::const_iterator it = incomming_ranges.begin ()
			; it != incomming_ranges.end ()
			; it++)
	{
		std::vector<Glib::ustring> tokens = Glib::Regex::split_simple ("[-,/:]", *it);
		QrParamsRangeType range;

		if (tokens.size() > 1)
		{
			range.min = MIN (atoi (tokens [0].c_str ()), atoi (tokens [1].c_str ()));
			range.max = MAX (atoi (tokens [0].c_str ()), atoi (tokens [1].c_str ()));
		}
		else if (tokens.size() > 0 )
		{
			range.min = atoi (tokens [0].c_str ());
			range.max = atoi (tokens [0].c_str ());
		}
		else if (tokens.size() == 0 )
		{
			range.min = 1;
			range.max = 1;
		}

		ranges.push_back(range);
	}

	return ranges;
}

SafeBuffer QRTestController::GenData (size_t dataSize)
{
	SafeBuffer data;
	size_t size = 0;
	int partial_data;

	struct timeval tv;
	struct timezone tz;

	gettimeofday (&tv, &tz);
	(void)localtime (&tv.tv_sec);

	std::srand ( (long) tv.tv_usec);

	while ( dataSize > size )
	{
		partial_data = rand ();
		data.AddData((unsigned char*)(&partial_data), 1);
		size +=  1;
	}


	return data;
}


