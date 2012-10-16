/*
 * PrintVote.cxx
 *
 *  Created on: 23/09/2011
 *      Author: soto
 */

#include "PrintVote.hxx"
#include <Printing/PrinterStatusNotifier.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Log/SMTTLogManager.h>
#include <config.h>

using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Log;

ISMTTLog* PrintVote::logger = SMTTLogManager::GetLogger("Smartmatic.PrintVote",PACKAGE_NAME);

PrintVote::PrintVote(Smartmatic::System::SafeBuffer & bufferIn)
: BasePrintDocument (false), buffer(bufferIn)
{
	PrinterStatusNotifier notifier;
	notifier.getStatusMessage();
}

PrintVote::~PrintVote()
{

}

void PrintVote::PrintDoc()
{
	QRCodeConfig config = SAESConfigurationManager::Current()->getQRCodeVoteConfig(buffer.GetSize());

	Glib::RefPtr<Gdk::Pixbuf> backgroundImage;
	int pixel_size = config.getSizeQRCode();
	int margin = config.getMarginQRCode();
	int version = config.getVersionQRCode();
	QRecLevel correctionLevel = SAESConfigurationManager::Current()->GetCorrectionModeQRCode(config.getCorrectionModeQRCode());

	logger->Debug("----------QRCodeConfig-----------");

	{
		std::stringstream ss;
		ss << "DataSize             : " << buffer.GetSize();
		logger->Debug(ss.str());
	}
	{
		std::stringstream ss;
		ss << "CorrectionModeQRCode : " << config.getCorrectionModeQRCode();
		logger->Debug(ss.str());
	}
	{
		std::stringstream ss;
		ss << "Pixel                : " << config.getSizeQRCode();
		logger->Debug(ss.str());
	}
	{
		std::stringstream ss;
		ss << "VersionQRCode        : " << config.getVersionQRCode();
		logger->Debug(ss.str());
	}

	if (buffer.GetSize() > 0)
	{
		DocumentTextOptions textOptionGeneric;
		this->NewTextBlock(textOptionGeneric);
		this->DrawString("---------------------------------------------------", true);

		{
			std::stringstream ss;
			ss << "DataSize             : " << buffer.GetSize();
			this->DrawString(ss.str(), true);
		}
		{
			std::stringstream ss;
			ss << "CorrectionModeQRCode : " << config.getCorrectionModeQRCode();
			this->DrawString(ss.str(), true);
		}
		{
			std::stringstream ss;
			ss << "Pixel                : " << config.getSizeQRCode();
			this->DrawString(ss.str(), true);
		}
		{
			std::stringstream ss;
			ss << "VersionQRCode        : " << config.getVersionQRCode();
			this->DrawString(ss.str(), true);
		}

		this->DrawString("---------------------------------------------------", true);

		this->DrawQRCode (
				  buffer
				, pixel_size
				, margin
				, correctionLevel
				, version
				// Image content
				, backgroundImage
				, Smartmatic::SAES::Printing::Center);

		this->NewTextBlock(textOptionGeneric);

		for (int i = 0; i < 8;i++)
		{
			this->DrawString("", true);
		}

		this->DrawString(".", true);
	}

}

void PrintVote::BeginPrint()
{

}

void PrintVote::EndPrint()
{

}
