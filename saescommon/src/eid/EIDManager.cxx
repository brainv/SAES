/**
 * @file EIDManager.cxx
 * @brief Body class eid manager
 * @date 20/07/2011
 * @author Yadickson Soto
 */

#include "EIDManager.hxx"
#include "EIDRead.hxx"
#include "EIDPin.hxx"
#include "EIDSign.hxx"
#include "EIDEvent.hxx"
#include <stdlib.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace eIDMW;
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;

bool EIDManager::flagStop = false;
ISMTTLog* EIDManager::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.EID.EIDManager",GETTEXT_PACKAGE);

EIDManager::EIDManager()
{

}

EIDManager::~EIDManager()
{

}

bool EIDManager::isReaderPresent()
{
	unsigned long nrReaders = 0;

	try
	{
		nrReaders = ReaderSet.readerCount(true);
	}
	catch (...)
	{
		std::stringstream ss;
		ss << "FATAL - Exception unknown. (" << __func__ << ")";
		logger->Debug(ss.str());
	}

	return nrReaders > 0;
}

std::list <std::string> EIDManager::getReadeNames()
{
	std::list <std::string> list;

	try
	{
		unsigned long nrReaders  = ReaderSet.readerCount(true);
		const char* const* readerList = ReaderSet.readerList(true);

		for ( size_t readerIdx=0; readerIdx<nrReaders; readerIdx++)
		{
			list.push_back ( readerList[readerIdx] );
		}

	}
	catch (...)
	{
		std::stringstream ss;
		ss << "FATAL - Exception unknown. (" << __func__ << ")";
		logger->Debug(ss.str());
	}

	return list;
}

bool EIDManager::isCardPresent()
{
	bool present = false;

	std::list <std::string> list = EIDManager::getReadeNames();

	if (list.size() > 0)
	{
		present = EIDManager::isCardPresent(*(list.begin()));
	}

	return present;
}

bool EIDManager::isCardPresent( std::string readerName )
{
	bool present = false;

	try
	{
		BEID_ReaderContext& readerContext = ReaderSet.getReaderByName( readerName.c_str() );
		present = readerContext.isCardPresent();
		readerContext.releaseCard(true);
	}
	catch (...)
	{
		std::stringstream ss;
		ss << "FATAL - Exception unknown found " << readerName << ". (" << __func__ << ")";
		logger->Debug(ss.str());
	}

	return present;
}

CitizenInfo EIDManager::getData( bool & result )
{
	CitizenInfo info;

	std::list <std::string> list = EIDManager::getReadeNames();

	if (list.size() > 0)
	{
		info = EIDManager::getData(result, *(list.begin()));
	}

	return info;
}

CitizenInfo EIDManager::getData( bool & result, std::string readerName )
{
	CitizenInfo info;
	result = false;

	if (!EIDManager::isCardPresent(readerName))
	{
		return info;
	}

	try
	{
		BEID_ReaderContext& readerContext = ReaderSet.getReaderByName( readerName.c_str() );

		switch(readerContext.getCardType())
		{
		case BEID_CARDTYPE_EID:
			EIDRead::getEidCardData( info, readerContext );
			result = true;
			break;
		case BEID_CARDTYPE_KIDS:
			EIDRead::getKidsCardData( info, readerContext );
			result = true;
			break;
		case BEID_CARDTYPE_FOREIGNER:
			EIDRead::getForeignerCardData( info, readerContext );
			result = true;
			break;
		case BEID_CARDTYPE_SIS:
			EIDRead::getSISCardData( info, readerContext );
			result = true;
			break;
		case BEID_CARDTYPE_UNKNOWN:
		default:
			result = false;
			break;
		}

		readerContext.releaseCard(true);
	}
	catch(...)
	{
		result = false;
		std::stringstream ss;
		ss << "FATAL - Exception unknown. (" << __func__ << ")";
		logger->Debug(ss.str());
	}

	return info;
}

Glib::RefPtr<Gdk::Pixbuf> EIDManager::getPicture()
{
	bool result;
	return EIDManager::getPicture(result);
}

Glib::RefPtr<Gdk::Pixbuf> EIDManager::getPicture( bool & result )
{
	Glib::RefPtr<Gdk::Pixbuf> img;
	result = false;

	std::list <std::string> list = EIDManager::getReadeNames();

	if (list.size() > 0)
	{
		img = EIDManager::getPicture(result, *(list.begin()));
	}

	return img;
}

Glib::RefPtr<Gdk::Pixbuf> EIDManager::getPicture( bool & result, std::string readerName )
{
	Glib::RefPtr<Gdk::Pixbuf> img;
	result = false;

	if (!EIDManager::isCardPresent(readerName))
	{
		return img;
	}

	try
	{
		BEID_ReaderContext& readerContext = ReaderSet.getReaderByName( readerName.c_str() );

		switch(readerContext.getCardType())
		{
		case BEID_CARDTYPE_EID:
			img = EIDRead::getEidCardPicture( readerContext );
			result = true;
			break;
		case BEID_CARDTYPE_KIDS:
			img = EIDRead::getKidsCardPicture( readerContext );
			result = true;
			break;
		case BEID_CARDTYPE_FOREIGNER:
			img = EIDRead::getForeignerCardPicture( readerContext );
			result = true;
			break;
		case BEID_CARDTYPE_SIS:
		case BEID_CARDTYPE_UNKNOWN:
		default:
			result = false;
			break;
		}

		readerContext.releaseCard(true);
	}
	catch(...)
	{
		result = false;
		std::stringstream ss;
		ss << "FATAL - Exception unknown. (" << __func__ << ")";
		logger->Debug(ss.str());
	}

	return img;
}

bool EIDManager::verifyPing()
{
	 unsigned long count;
	 return EIDManager::verifyPing(count);
}

bool EIDManager::verifyPing( unsigned long & count )
{
	bool validate = false;
	count = 0;

	std::list <std::string> list = EIDManager::getReadeNames();

	if (list.size() > 0)
	{
		validate = EIDManager::verifyPing(count, *(list.begin()));
	}

	return validate;
}

bool EIDManager::verifyPing( unsigned long & count, std::string readerName )
{
	bool validate = false;
	count = 0;

	if (!EIDManager::isCardPresent(readerName))
	{
		count = 0;
		return validate;
	}

	try
	{
		BEID_ReaderContext& readerContext = ReaderSet.getReaderByName( readerName.c_str() );

		switch(readerContext.getCardType())
		{
		case BEID_CARDTYPE_EID:
			validate = EIDPin::verify(readerContext.getEIDCard(), count);
			break;
		case BEID_CARDTYPE_KIDS:
			validate = EIDPin::verify(readerContext.getKidsCard(), count);
			break;
		case BEID_CARDTYPE_FOREIGNER:
			validate = EIDPin::verify(readerContext.getForeignerCard(), count);
			break;
		case BEID_CARDTYPE_SIS:
		case BEID_CARDTYPE_UNKNOWN:
		default:
			break;
		}

		readerContext.releaseCard(true);
	}
	catch(...)
	{
		std::stringstream ss;
		ss << "FATAL - Exception unknown. (" << __func__ << ")";
		logger->Debug(ss.str());
	}

	return validate;
}

bool EIDManager::signPKCS11(
		Smartmatic::System::SafeBuffer & buffer,
		Smartmatic::System::SafeBuffer & result )
{
	bool sign = false;

	std::list <std::string> list = EIDManager::getReadeNames();

	if (list.size() > 0)
	{
		sign = EIDManager::signPKCS11(buffer, result, *(list.begin()));
	}

	return sign;
}

bool EIDManager::signPKCS11(
		Smartmatic::System::SafeBuffer & buffer,
		Smartmatic::System::SafeBuffer & result,
		std::string readerName )
{
	bool sign = false;

	if (!EIDManager::isCardPresent(readerName))
	{
		return sign;
	}

	sign = Smartmatic::SAES::EID::EIDSign::singPCKS11(buffer, result);

	return sign;
}

void EIDManager::release()
{
	logger->Debug("Release EID Manager.");
	try
	{
		ReaderSet.releaseSDK();
	}
	catch(...)
	{
		std::stringstream ss;
		ss << "FATAL - Exception unknown. (" << __func__ << ")";
		logger->Debug(ss.str());
	}
}

void EIDManager::init(EIDEventInterface * eventinterface)
{
	logger->Debug("Init EID Manager.");

	bool useCallback  = SAESCommonConfigurationManager::Current()->getBEIDConfiguration().getUseCallbackEvent();

	if (useCallback && !flagStop)
	{
		logger->Debug("Use call back event");
		EIDEvent::attach();
		EIDEvent::init(eventinterface);
	}

	flagStop = true;
}

void EIDManager::stop()
{
	if (flagStop)
	{
		logger->Debug("Stop EID Manager.");

		bool useCallback  = SAESCommonConfigurationManager::Current()->getBEIDConfiguration().getUseCallbackEvent();

		if (useCallback)
		{
			EIDEvent::detach();
		}

		flagStop = false;
	}
}
