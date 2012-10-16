/*
 * Barcode.cxx
 *
 *  Created on: 23/09/2011
 *      Author: soto
 */

#include "Barcode.hxx"
#include "VoteRecorder.hxx"
#include "SaveVote.hxx"
#include "PrintVote.hxx"
#include <Devices/barcode-device.h>
#include <Runtime/Environment/filename-hasher.h>

#include <iostream>

using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Runtime::Environment;

Barcode::Barcode()
{
	BarcodeDevice::Current()->Resync();
	BarcodeDevice::Current()->signalConnected().connect(sigc::mem_fun(*this, &Barcode::reconnectedBarcode));
	BarcodeDevice::Current()->signalDisconnected().connect(sigc::mem_fun(*this, &Barcode::disconnectedBarcode));
	BarcodeDevice::Current()->signalDetected().connect(sigc::mem_fun(*this, &Barcode::recievedData));
}

Barcode::~Barcode()
{
	BarcodeDevice::Current()->Close();
}

void Barcode::reconnectedBarcode()
{
	BarcodeDevice::Current()->Resync();
}

void Barcode::disconnectedBarcode()
{

}

void Barcode::recievedData (SafeBuffer * data)
{
	if(!VoteRecorder::getInstance()->RecordVote(*data))
		std::cerr << "Non valid code map" << std::endl;
}

void Barcode::close()
{
	BarcodeDevice::Current()->Close();
}
