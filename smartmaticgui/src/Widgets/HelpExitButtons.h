/*
 * HelpExitButtons.h
 *
 *  Created on: May 31, 2011
 *      Author: Juan Carlos Delgado
 */

#include <gtkmm.h>
#include "Widgets/exit-button-listener.h"
#include "Widgets/help-button-listener.h"
#include "Widgets/smartmatic-button.h"

#ifndef HELPEXITBUTTONS_H_
#define HELPEXITBUTTONS_H_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class HelpExitButtons : public Gtk::HBox
			{
			public:
				HelpExitButtons(ExitButtonListener *exitListener, bool showExitButton,
								HelpButtonListener* helpListener, bool showHelpButton);

				~HelpExitButtons();

				void ExitButton_SetSensitive(bool sensitive);

				void ExitButton_SetVisible(bool visible);

				void ExitButton_SetName(std::string name);

				void HelpButton_SetSensitive(bool sensitive);

				void HelpButton_SetVisible(bool visible);

				void HelpButton_SetName(std::string name);

			protected:
				SmartmaticButton* exitButton;
				SmartmaticButton* helpButton;

				ExitButtonListener *exitListener;
				HelpButtonListener *helpListener;

				void on_exitButton_clicked();
				void on_helpButton_clicked();

			};
		}
	}
}

#endif /* HELPEXITBUTTONS_H_ */
