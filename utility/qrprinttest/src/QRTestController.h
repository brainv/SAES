/*
 * QRTestController.h
 *
 *  Created on: Jul 15, 2011
 *      Author: root
 */

#ifndef QRTESTCONTROLLER_H_
#define QRTESTCONTROLLER_H_


#include <list>
#include <glib.h>
#include <System/SafeBuffer.h>
#include <Log/ISMTTLog.h>

class QRTestController : public Glib::Object
{
public:

	typedef enum
	{
		QRETST_ECLEVEL_L = 0,
		QRETST_ECLEVEL_M = 1,
		QRETST_ECLEVEL_Q = 2,
		QRETST_ECLEVEL_H = 3

	} QrCorrectionLevelEnumType;

	typedef struct
	{
		int min;
		int max;
		int step;

	} QrParamsRangeType;

	typedef struct
	{
		QrParamsRangeType data_size;
		QrParamsRangeType version;
		QrParamsRangeType correction_level;
		QrParamsRangeType pixel_size;
		QrParamsRangeType margin_size;

		bool image_based;
		bool use_background;

	} QrTestParamsType;

	virtual ~QRTestController();
	static Glib::RefPtr<QRTestController> GetInstance ();

	void ExecuteTest (std::list<QrTestParamsType> tests);

	std::vector<QrParamsRangeType> ParseRanges (std::vector<Glib::ustring> incomming_ranges);

protected:

	QRTestController();

private:

	static Glib::RefPtr<QRTestController> current_instance;
	static int test_id_suffix;

	Glib::ustring m_BgnImagePath;

	Smartmatic::System::SafeBuffer GenData (size_t dataSize);

	static Smartmatic::Log::ISMTTLog* logger; ///< The logger
};

#endif /* QRTESTCONTROLLER_H_ */
