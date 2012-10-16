/*
 * VMPollingPlaceInfoWidget.cxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#include "VMPollingPlaceInfoWidget.hxx"
#define N_(String) (String)

using namespace Smartmatic::SAES::GUI::Widgets;

VMPollingPlaceInfoWidget::VMPollingPlaceInfoWidget()
: PollingPlaceInfoWidget()
{

}

VMPollingPlaceInfoWidget::~VMPollingPlaceInfoWidget()
{

}

void VMPollingPlaceInfoWidget::fillKey()
{
	messageErrorKey = N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.ErrorConfiguration");

	versionKey = N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.Version");
    votingCenterKey = N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.PollingPlace");
	votingCenterAddressKey = N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.PollingPlaceAddress");
	electionNameKey = N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.ElectionNameKey");
	registeredElectorsKey = N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.RegisteredElectorsKey");
	pollingStationCodeKey = N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.PollingStationCodeKey");
	votingDeviceCustomCodeKey = N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.PollingStationNumberKey");

	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.VMInstallationWindow.SuccessfulAuthentication"), " ");
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoKey1"), N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoValue1"));
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoKey2"), N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoValue2"));
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoKey3"), N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoValue3"));
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoKey4"), N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoValue4"));
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoKey5"), N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoValue5"));
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoKey6"), N_("Smartmatic.SAES.GUI.Windows.PMInstallationWidget.InfoValue6"));
}
