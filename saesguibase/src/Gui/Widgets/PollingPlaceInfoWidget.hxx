/*
 * PollingPlaceInfoWidget.hxx
 *
 *  Created on: 18/10/2011
 *      Author: soto
 */

#ifndef POLLINGPLACEINFOWIDGET_HXX_
#define POLLINGPLACEINFOWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/info-widget.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class PollingPlaceInfoWidget : public Gtk::Frame
				{
				public:
					PollingPlaceInfoWidget();
					virtual ~PollingPlaceInfoWidget();
					virtual void fillKey() = 0;
					void fillInfoWidget();

				protected:

					Glib::ustring messageErrorKey;

					Glib::ustring region1Key;
					Glib::ustring region2Key;
					Glib::ustring region3Key;
					Glib::ustring region4Key;
					Glib::ustring region5Key;
					Glib::ustring region6Key;
					Glib::ustring region7Key;
					Glib::ustring votingCenterKey;
					Glib::ustring versionKey;
					Glib::ustring votingCenterAddressKey;
					Glib::ustring electionNameKey;
					Glib::ustring registeredElectorsKey;
					Glib::ustring pollingStationCodeKey;
					Glib::ustring votingDeviceCustomCodeKey;

					Glib::ustring region1Value;
					Glib::ustring region2Value;
					Glib::ustring region3Value;
					Glib::ustring region4Value;
					Glib::ustring region5Value;
					Glib::ustring region6Value;
					Glib::ustring region7Value;
					Glib::ustring votingCenterValue;
					Glib::ustring versionValue;
					Glib::ustring votingCenterAddressValue;
					Glib::ustring electionNameValue;
					Glib::ustring registeredElectorsValue;
					Glib::ustring pollingStationCodeValue;
					Glib::ustring votingDeviceCustomCodeValue;

					void addCompositePair(std::string key, std::string value);

				private:

					Gtk::Label * messageError;
					Smartmatic::GUI::Widgets::InfoWidget * infoWidget;
					static Smartmatic::Log::ISMTTLog* logger;   ///< logger

					std::vector< std::vector<std::string> > composePair;
					std::vector< std::vector<std::string> > info;

					std::string composeKey(std::string toCompose);
					std::string composeValue(std::string toCompose);

					void compositePair(std::string key, std::string value);
				};
			}
		}
	}
}

#endif /* POLLINGPLACEINFOWIDGET_HXX_ */
