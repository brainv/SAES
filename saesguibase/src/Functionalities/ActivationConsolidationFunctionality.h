/*
 * ActivationConsolidationFunctionality.h
 *
 *  Created on: Sep 2, 2011
 *      Author: Juan Delgado
 */

#ifndef ACTIVATIONCONSOLIDATIONFUNCTIONALITY_H_
#define ACTIVATIONCONSOLIDATIONFUNCTIONALITY_H_

#include <gtkmm.h>
#include <Log/ISMTTLog.h>
#include <Functionalities/menu-option-descriptor.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Configuration/label-configuration.h>
#include <Gui/Widgets/ConsolidationStatsWidget.h>
#include <Gui/Widgets/ActivationStatsWidget.h>
#include <Gui/Widgets/CardActivatorEventBox.h>
#include <Gui/Widgets/BarcodeDetectionWidget.h>
#include <Voting/VotingDevice/voting-devices-schema.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				class ActivationConsolidationFunctionality : public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{
				public:
					/**
					 * @brief	Gets the instance of class.
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
					 *
					 * @return	null if it fails, else instance of class.
					 */
					static ActivationConsolidationFunctionality* Current();

				protected:

					/**
					 * @brief method block functionality
					 * @date 19/04/2012
					 * @author Yadickson Soto
					 */
					virtual void block();
					/**
					 * @brief method partial functionality
					 * @date 19/04/2012
					 * @author Yadickson Soto
					 */
					virtual void partial();
					/**
					 * @brief method resume functionality
					 * @date 19/04/2012
					 * @author Yadickson Soto
					 */
					virtual void resume();
					/**
					 * @brief method refresh
					 * @date 14/06/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();

				private:
					static ActivationConsolidationFunctionality *current_instance;   ///< The current instance

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011d
					 */
					ActivationConsolidationFunctionality();

					/**
					 * @brief	Default destructor.
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
					 */
					virtual ~ActivationConsolidationFunctionality();

					/**
					 * @brief	Gets the window title.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The window title.
					 */

					std::string GetWindowTitle();

					/**
					 * @brief	Gets the menu option type.
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
					 *
					 * @return	The menu option type.
					 */
					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();

					/**
					 * @brief	Gets the frame.
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
					 *
					 * @return	null if it fails, else the frame.
					 */
					Gtk::Widget * GetFrame();

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
					 */
					void Dispose();

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
					 */
					void Initialize();

					/**
					 * @brief	Gets the logger.
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
					 *
					 * @return	null if it fails, else the logger.
					 */
					Smartmatic::Log::ISMTTLog* getLogger();

					/**
					 * @brief	Gets the start log message.
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
					 *
					 * @return	The start log message.
					 */
					Glib::ustring getStartLogMessage();

					/**
					 * @brief	Gets the finish log message.
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
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

					/**
					 * @brief	Sets the custom attribute vector
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
					 *
					 * @param	the custom attribute vector
					 */
					void SetCustomAttributeVector(std::vector< Smartmatic::SAES::Voting::VotingDevice::Custom_attribute > vecCA);

					/**
					 * @brief	Handles if barcode is connected
					 *
					 * @author	Juan Delgado
					 * @date	02/09/2011
					 *
					 * @param	true if barcode is connected
					 */
					void BarcodeConnected(bool isConnected);

					void statusSendCommands(bool status);

					void showBarcodeConnected();

					void hideBarcodeConnected();

					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

					sigc::connection signalStartSendCommand; ///< signal start send command
					sigc::connection signalEndSendCommand; ///< signal end send command
					sigc::connection connBarcodeDisconnected;  ///< The connection back
					sigc::connection connBarcodeConnected;///< The connection for barcode connected

					Smartmatic::SAES::GUI::Widgets::ActivationStatsWidget * activationWidget;
					Smartmatic::SAES::GUI::Widgets::ConsolidationStatsWidget * consolidationWidget;
					Smartmatic::SAES::GUI::Widgets::CardActivatorEventBox * cardActivatorBox;
					Smartmatic::SAES::GUI::Widgets::BarcodeDetectionWidget* barcodeWidget; ///< The barcode detection widget

					Gtk::HBox * outsideBox;
				};
			}
		}
	}
}

#endif /* ACTIVATIONCONSOLIDATIONFUNCTIONALITY_H_ */
