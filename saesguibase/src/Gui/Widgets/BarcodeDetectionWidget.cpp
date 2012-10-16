/*
 * BarcodeDetectionWidget.cpp
 *
 *  Created on: Jul 23, 2011
 *      Author: Juan.Delgado
 */

#include "BarcodeDetectionWidget.h"
#include <Environment/Configurations/resource-path-provider.h>
#include <System/IO/File.h>
#include <Devices/barcode-device.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Log/SMTTLogManager.h>

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

using namespace Gtk;
using namespace std;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::System::IO;

ISMTTLog* BarcodeDetectionWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.BarcodeDetectionWidget",GETTEXT_PACKAGE);

BarcodeDetectionWidget::BarcodeDetectionWidget(ProgressWidget * progress)
: Gtk::Frame(), progress(progress)
{
	sendConfigurationCommands =
			Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetSendBarcodeConfigurationOnReconnectWidget();

	fileImageConnected = "ui/barcode_connected.gif";
	fileImageNoConnected = "ui/barcode_noConnected.gif";
	fileImageRecoveryConnected = "ui/barcode_recoveryConnected.gif";

	progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.BarcodeDetectionWidget.BarcodeNoConnected"));
	progress->setImage(fileImageNoConnected);

	this->set_shadow_type(Gtk::SHADOW_NONE);
	this->add(*progress);
	this->show_all_children();
	this->show();
}

void BarcodeDetectionWidget::ShowConfigure()
{
	progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.BarcodeDetectionWidget.ReconfigureBarcode"));
	progress->setImage(fileImageRecoveryConnected);
}

void BarcodeDetectionWidget::BarcodeConnected()
{
	logger->Debug("BarcodeDetectionWidget Barcode Connected");

	BarcodeDevice::Current()->Resync();

	if(sendConfigurationCommands)
	{
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.BarcodeDetectionWidget.ReconfigureBarcode"));
		progress->setImage(fileImageRecoveryConnected);

		m_enable_exit.emit(false);

		BarcodeDevice::Current()->SendConfigurationCommands("baseconfiguration",true,false);
	}
	else
	{
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.BarcodeDetectionWidget.BarcodeConnected"));
		progress->setImage(fileImageConnected);
		conn_barcodeConfigured = Glib::signal_timeout().connect(sigc::bind<bool>(sigc::mem_fun(this, &BarcodeDetectionWidget::emit_barcode_connected_signal), true), 3000);
	}
}

void BarcodeDetectionWidget::ShowFail()
{
	progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.BarcodeDetectionWidget.BarcodeConfigurationFail"));
}

void BarcodeDetectionWidget::ConnectSignals()
{
	DisconnectSignals();

	conn_barcodeConnected = BarcodeDevice::Current()->signalConnected().connect(sigc::mem_fun(*this, &BarcodeDetectionWidget::BarcodeConnected));
	conn_barcodeDisconnected = BarcodeDevice::Current()->signalDisconnected().connect(sigc::mem_fun(*this, &BarcodeDetectionWidget::BarcodeDisconnected));
	conn_barcodeResponseCommand = BarcodeDevice::Current()->signalCommandsSent().connect(sigc::mem_fun(*this,&BarcodeDetectionWidget::CommandsResponse));
}

void BarcodeDetectionWidget::DisconnectSignals()
{
	conn_barcodeConnected.disconnect();
	conn_barcodeDisconnected.disconnect();
	conn_barcodeResponseCommand.disconnect();
	conn_barcodeConfigured.disconnect();
}

void BarcodeDetectionWidget::BarcodeDisconnected()
{

}

BarcodeDetectionWidget::~BarcodeDetectionWidget()
{
	DisconnectSignals();

	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

bool BarcodeDetectionWidget::CheckBarcodeConnected()
{
	return BarcodeDevice::Current()->Resync();
}

BarcodeDetectionWidget::type_barcode_connected_signal BarcodeDetectionWidget::signal_barcode_connected()
{
	return m_barcode_connected;
}

BarcodeDetectionWidget::type_barcode_connected_signal BarcodeDetectionWidget::enable_exit()
{
	return m_enable_exit;
}

void BarcodeDetectionWidget::CommandsResponse(bool commandsOk)
{
	if(commandsOk)
	{
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.BarcodeDetectionWidget.BarcodeConnected"));
		progress->setImage(fileImageConnected);
		conn_barcodeConfigured = Glib::signal_timeout().connect(sigc::bind<bool>(sigc::mem_fun(this, &BarcodeDetectionWidget::emit_barcode_connected_signal), true), 3000);
	}
	else
	{
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.BarcodeDetectionWidget.ReconnectedBarcode"));
		progress->setImage(fileImageNoConnected);
		m_barcode_connected.emit(false);
		BarcodeDevice::Current()->Close();
	}
	m_enable_exit.emit(true);
}

void BarcodeDetectionWidget::SetDefault()
{
	DisconnectSignals();
	ConnectSignals();
	progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.BarcodeDetectionWidget.BarcodeNoConnected"));
	progress->setImage(fileImageNoConnected);
}

bool BarcodeDetectionWidget::emit_barcode_connected_signal(bool isConnected)
{
	DisconnectSignals();
	m_barcode_connected.emit(isConnected);
	return false;
}

