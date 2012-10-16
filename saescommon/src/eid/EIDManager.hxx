/*
 * EIDManager.hxx
 *
 *  Created on: 20/07/2011
 *      Author: soto
 */

#ifndef EIDMANAGER_HXX_
#define EIDMANAGER_HXX_

#include <iostream>
#include <gtkmm.h>
#include <list>
#include <System/SafeBuffer.h>
#include "CitizenInfo.h"
#include "EIDEventInterface.hxx"

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace EID
		{
			class EIDManager
			{
			public:
				enum EIDResult
				{
					EIDMANAGER_ERROR_GETING_FUNCTION_LIST,
					EIDMANAGER_INITIALIZE_FAILED,
					EIDMANAGER_GET_SLOT_LIST_FAILED,
					EIDMANAGER_OPEN_SESSION_FAILED,
					EIDMANAGER_FIND_OBJECTS_INIT_FAILED,
					EIDMANAGER_FIND_OBJECTS_FAILED,
					EIDMANAGER_SIGNATURE_KEY_NOT_FOUND,
					EIDMANAGER_FIND_OBJECTS_FINAL_FAILED,
					EIDMANAGER_SIGNATURE_INIT_FAILED,
					EIDMANAGER_SIGNATURE_FAILED,
					EIDMANAGER_CLOSE_SESSION_FAILED,
					EIDMANAGER_FINALIZE_FAILED,
					EIDMANAGER_FAILD,
					EIDMANAGER_SUCCESS
				};

			protected:
				EIDManager();

			public:
				~EIDManager();

				static void init(EIDEventInterface * eventinterface);

				static bool isReaderPresent();

				static std::list <std::string> getReadeNames();

				static bool isCardPresent();

				static bool isCardPresent( std::string readerName );

				static CitizenInfo getData( bool & result );

				static CitizenInfo getData( bool & result, std::string readerName );

				static Glib::RefPtr<Gdk::Pixbuf> getPicture();

				static Glib::RefPtr<Gdk::Pixbuf> getPicture( bool & result );

				static Glib::RefPtr<Gdk::Pixbuf> getPicture( bool & result, std::string readerName );

				static bool verifyPing();

				static bool verifyPing( unsigned long & count );

				static bool verifyPing( unsigned long & count, std::string readerName );

				static bool signPKCS11(
						Smartmatic::System::SafeBuffer & buffer,
						Smartmatic::System::SafeBuffer & result );

				static bool signPKCS11(
						Smartmatic::System::SafeBuffer & buffer,
						Smartmatic::System::SafeBuffer & result,
						std::string readerName );

				static void stop();

				static void release();

			private:
				static bool flagStop;
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		}
	}
}

#endif /* EIDMANAGER_HXX_ */
