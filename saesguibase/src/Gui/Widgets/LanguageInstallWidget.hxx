/*
 * LanguageInstallWidget.hxx
 *
 *  Created on: 19/10/2011
 *      Author: soto
 */

#ifndef LANGUAGEINSTALLWIDGET_HXX_
#define LANGUAGEINSTALLWIDGET_HXX_

#include <gtkmm.h>
#include "change-language-widget.h"
#include <Widgets/StepWidget.hxx>

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
				class LanguageInstallWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					LanguageInstallWidget();
					virtual ~LanguageInstallWidget();

					void start();

				private:

					Smartmatic::SAES::GUI::Widgets::ChangeLanguageWidget * languageWidget;
					static Smartmatic::Log::ISMTTLog* logger;   ///< logger

				protected:

					void initialize();
					void dispose();
					void end();
				};
			}
		}
	}
}

#endif /* LANGUAGEINSTALLWIDGET_HXX_ */
