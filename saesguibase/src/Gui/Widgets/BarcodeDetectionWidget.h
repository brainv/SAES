/*
 * BarcodeDetectionWidget.h
 *
 *  Created on: Jul 23, 2011
 *      Author: Juan.Delgado
 */

#ifndef BARCODEDETECTIONWIDGET_H_
#define BARCODEDETECTIONWIDGET_H_

#include <gtkmm.h>
#include <Widgets/smartmatic-button.h>
#include <Log/ISMTTLog.h>
#include "ProgressWidget.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class BarcodeDetectionWidget: public Gtk::Frame
				{
				public:
					/**
					 * @fn	void BarcodeDetectionWidget::BarcodeDetectionWidget();
					 * @param progress progress widget
					 * @brief	Default constructor
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 */
					BarcodeDetectionWidget(ProgressWidget * progress);

					/**
					 * @fn	void BarcodeDetectionWidget::~BarcodeDetectionWidget();
					 *
					 * @brief	Default finalizer
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 */
					virtual ~BarcodeDetectionWidget();

					/**
					 * @fn	bool BarcodeDetectionWidget::~CheckBarcodeConnected();
					 *
					 * @brief	Default finalizer
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 *
					 * @return True if barcode connected
					 */
					bool CheckBarcodeConnected();

					typedef sigc::signal<void, bool> type_barcode_connected_signal;	///< Definition of barcode signal

					/**
					 * @fn	type_barcode_connected_signal BarcodeDetectionWidget::signal_barcode_connected();
					 *
					 * @brief	Return barcode connected signal
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 *
					 * @return type_barcode_connected_signal
					 */
					type_barcode_connected_signal signal_barcode_connected();

					type_barcode_connected_signal enable_exit();

					void SetDefault();

					void ShowConfigure();

					void ShowFail();

					/**
					 * @brief	Connect all signals
					 *
					 * @author	Juan Delgado
					 */
					void ConnectSignals();

					/**
					 * @brief	Disconnect all signals
					 *
					 * @author	Juan Delgado
					 */
					void DisconnectSignals();

				protected:
					type_barcode_connected_signal m_barcode_connected;   ///< The barcode signal
					type_barcode_connected_signal m_enable_exit;

					/**
					 * @fn	bool BarcodeDetectionWidget::emit_barcode_connected_signal(bool isConnected);
					 *
					 * @brief	Emit the barcode connected signal
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 */
					bool emit_barcode_connected_signal(bool isConnected);

					/**
					 * @fn	void BarcodeDetectionWidget::CommandsResponse(bool commandsOk)
					 *
					 * @brief	Handles the commands response signal
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 *
					 * @param	True if commands sent were ok
					 */
					void CommandsResponse(bool commandsOk);

					/**
					 * @brief	Handles the barcode connected signal
					 *
					 * @author	Juan Delgado
					 */
					void BarcodeConnected();

					/**
					 * @brief	Handles the barcode disconnected signal
					 *
					 * @author	Juan Delgado
					 */
					void BarcodeDisconnected();

				private:
					ProgressWidget * progress; ///< principal frame
					bool sendConfigurationCommands;

					sigc::connection conn_barcodeConnected;
					sigc::connection conn_barcodeDisconnected;
					sigc::connection conn_barcodeResponseCommand;
					sigc::connection conn_barcodeConfigured;

					std::string fileImageConnected;	///< The file image connected
					std::string fileImageNoConnected;	///< The file image no connected
					std::string fileImageRecoveryConnected;	///< The file image recovery connected

					static Smartmatic::Log::ISMTTLog* logger; ///< logger
				};
			}
		}
	}
}

#endif /* BARCODEDETECTIONWIDGET_H_ */
