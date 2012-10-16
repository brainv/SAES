/*
 * Barcode.hxx
 *
 *  Created on: 23/09/2011
 *      Author: soto
 */

#ifndef BARCODE_HXX_
#define BARCODE_HXX_

#include <System/SafeBuffer.h>

class Barcode
{
public:
	Barcode();
	virtual ~Barcode();

	void reconnectedBarcode();
	void disconnectedBarcode();
	void recievedData (Smartmatic::System::SafeBuffer * data);
	void close();
};

#endif /* BARCODE_HXX_ */
