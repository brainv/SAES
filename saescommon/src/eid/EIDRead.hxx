/*
 * EIDRead.hxx
 *
 *  Created on: 20/07/2011
 *      Author: soto
 */

#ifndef EIDREAD_HXX_
#define EIDREAD_HXX_

#include <gtkmm.h>
#include "beidlib/eidlib.h"
#include "CitizenInfo.h"

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
			class EIDRead
			{
			protected:
				EIDRead();

			public:
				~EIDRead();

				static void getSISData( CitizenInfo & info, eIDMW::BEID_SISCard& card );

				static void getEIDData( CitizenInfo & info, eIDMW::BEID_EIDCard& card );

				static void getSISCardData( CitizenInfo & info, eIDMW::BEID_ReaderContext& readerContext );

				static void getKidsCardData( CitizenInfo & info, eIDMW::BEID_ReaderContext& readerContext );

				static void getForeignerCardData( CitizenInfo & info, eIDMW::BEID_ReaderContext& readerContext );

				static void getEidCardData( CitizenInfo & info, eIDMW::BEID_ReaderContext& readerContext );

				static Glib::RefPtr<Gdk::Pixbuf> getEIDPicture( eIDMW::BEID_EIDCard& card );

				static Glib::RefPtr<Gdk::Pixbuf> getKidsCardPicture( eIDMW::BEID_ReaderContext& readerContext );

				static Glib::RefPtr<Gdk::Pixbuf> getForeignerCardPicture( eIDMW::BEID_ReaderContext& readerContext );

				static Glib::RefPtr<Gdk::Pixbuf> getEidCardPicture( eIDMW::BEID_ReaderContext& readerContext );

			private:
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		}
	}
}

#endif /* EIDREAD_HXX_ */
