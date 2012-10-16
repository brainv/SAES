/*
 * VMAuthenticationPollingPlaceInfoWidget.cxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#include "VMAuthenticationPollingPlaceInfoWidget.hxx"

#define N_(String) (String)

using namespace Smartmatic::SAES::GUI::Widgets;

VMAuthenticationPollingPlaceInfoWidget::VMAuthenticationPollingPlaceInfoWidget()
: PollingPlaceInfoWidget()
{

}

VMAuthenticationPollingPlaceInfoWidget::~VMAuthenticationPollingPlaceInfoWidget()
{

}

void VMAuthenticationPollingPlaceInfoWidget::fillKey()
{
	messageErrorKey = " ";

	versionKey = N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.Version");
    votingCenterKey = N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.PollingPlace");
	votingCenterAddressKey = N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.PollingPlaceAddress");
	electionNameKey = N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.ElectionNameKey");
	registeredElectorsKey = N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.RegisteredElectorsKey");
	pollingStationCodeKey = N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.PollingStationCodeKey");
	votingDeviceCustomCodeKey = N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.PollingStationNumberKey");

	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoKey1"), N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoValue1"));
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoKey2"), N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoValue2"));
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoKey3"), N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoValue3"));
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoKey4"), N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoValue4"));
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoKey5"), N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoValue5"));
	addCompositePair(N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoKey6"), N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.InfoValue6"));
}
