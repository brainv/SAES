/*
 * FillAssistedActivationFunctionality.h
 *
 *  Created on: Jul 25, 2011
 *      Author: Juan.Delgado
 */

#ifndef FILLASSISTEDACTIVATIONINFOFUNCTIONALITY_H_
#define FILLASSISTEDACTIVATIONINFOFUNCTIONALITY_H_

#include <gtkmm.h>
#include <Log/ISMTTLog.h>
#include <Functionalities/menu-option-descriptor.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Log/ISMTTLog.h>
#include <Widgets/smartmatic-button.h>
#include <Widgets/notebook-container.h>
#include <Gui/Widgets/assisted-activation-manager-widget.h>
#include <Voting/PBReports/assisted-activation-schema.hxx>
#include "Gui/Widgets/AssistedActivationWidget.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				class FillAssistedActivationInfoFunctionality : public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{
				public:
					/**
					 * @brief	Gets the current.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else.
					 */
					static FillAssistedActivationInfoFunctionality* Current();

				protected:
					/**
					 * @brief	Gets the logger.
					 *
					 * @author	Juan.Delgado
					 * @date	25/07/2011
					 *
					 * @return	null if it fails, else the logger.
					 */

					Smartmatic::Log::ISMTTLog* getLogger();

					/**
					 * @brief	Gets the start log message.
					 *
					 * @author	Juan.Delgado
					 * @date	25/07/2011
					 *
					 * @return	The start log message.
					 */

					Glib::ustring getStartLogMessage();

					/**
					 * @brief	Gets the finish log message.
					 *
					 * @author	Juan.Delgado
					 * @date	25/07/2011
					 *
					 * @return	The finish log message.
					 */

					Glib::ustring getFinishLogMessage();
					/**
					 * @brief method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();

				private:
					Smartmatic::SAES::GUI::Widgets::AssistedActivationManagerWidget* assistedManager;
					Smartmatic::GUI::Widgets::NotebookContainer* notebookContainer;
					Smartmatic::GUI::Widgets::SmartmaticButton* addInfoButton;

					std::vector<Gtk::Widget*> vectorWidget;
					std::vector<Smartmatic::SAES::GUI::Widgets::AssistedActivationWidget* > assistedManagerList;
					Gtk::HButtonBox* hboxBtn;
					Gtk::HBox* box;
					Gtk::HBox* outsideBox;
					Gtk::Alignment* alignWizard;
					int tablePos;
					int currentPage;
					bool isLoading;

					void on_AssistedManagerFinish(Smartmatic::SAES::Voting::PBReports::Activation activation);
					void on_addInfoButton_clicked();
					Gtk::Widget* CreateNewPage();


					static FillAssistedActivationInfoFunctionality *current_instance;

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Juan.Delgado
					 * @date	25/07/2011
					 */

					FillAssistedActivationInfoFunctionality();

					/**
					 * @brief	Finalizer.
					 *
					 * @author	Juan.Delgado
					 * @date	25/07/2011
					 */
					~FillAssistedActivationInfoFunctionality();


					/**
					 * @brief	Gets the frame.
					 *
					 * @author	Juan.Delgado
					 * @date	25/07/2011
					 *
					 * @return	null if it fails, else the frame.
					 */

					Gtk::Widget* GetFrame();

					void Dispose();

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Juan.Delgado
					 * @date	25/07/2011
					 */

					void Initialize();

					/**
					 * @brief	Gets the window title.
					 *
					 * @author	Juan.Delgado
					 * @date	25/07/2011
					 *
					 * @return	The window title.
					 */

					std::string GetWindowTitle();

					/**
					 * @brief	Gets the menu option type.
					 *
					 * @author	Juan.Delgado
					 * @date	25/07/2011
					 *
					 * @return	The menu option type.
					 */

					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();

				private:
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

				};
			}
		}
	}
}

#endif /* FILLASSISTEDACTIVATIONINFOFUNCTIONALITY_H_ */
