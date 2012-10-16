/**
 * @file PollingPlaceInfoWidget.cxx
 * @brief Body class polling place info widget
 * @date 18/10/2011
 * @author: Yadickson Soto
 */

#include "PollingPlaceInfoWidget.hxx"
#include <Operation/MachineOperationManager.hxx>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Resources/election-string-resources-manager.h>

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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::GUI::Widgets;

ISMTTLog* PollingPlaceInfoWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.PollingPlaceInfoWidget",GETTEXT_PACKAGE);

PollingPlaceInfoWidget::PollingPlaceInfoWidget()
: Gtk::Frame()
{
	this->infoWidget = NULL;
	this->messageError = new Gtk::Label();
	this->set_shadow_type(Gtk::SHADOW_NONE);
}

PollingPlaceInfoWidget::~PollingPlaceInfoWidget()
{
	if (infoWidget)
	{
		delete infoWidget;
		infoWidget = NULL;
	}
	if (messageError)
	{
		delete messageError;
		messageError = NULL;
	}
}

void PollingPlaceInfoWidget::fillInfoWidget()
{
	info.clear();
	composePair.clear();

	fillKey();

    bool validate = true;
	this->remove();

	ElectoralConfiguration * electoralConfiguration;

	try
	{
		electoralConfiguration = MachineOperationManager::getInstance()->getElectoralConfiguration();

		Smartmatic::SAES::Voting::VotingDevice::Voting_booths::Voting_boothSequence vbseq =
				electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getVoting_booths().getVoting_booth();

		votingDeviceCustomCodeValue = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getCustom_code();

		if (vbseq.size() > 0)
		{
			Smartmatic::SAES::Voting::VotingDevice::Voting_booth vb = (*(vbseq.begin()));
			std::list <Smartmatic::SAES::Voting::VotingDevice::Region_category> & regionList (
					electoralConfiguration->getRegionCategoryList());

			if (regionList.size() > 0)
			{
			    std::list <std::string> regionKeys;
			    std::list <std::string> regionValues;
			    std::list <std::string>::iterator itrn;

			    std::list <Smartmatic::SAES::Voting::VotingDevice::Region_category>::iterator regit;

			    for(regit = regionList.begin(); regit != regionList.end(); regit++)
			    {
			    	VotingDevice::Region_category rc = (*regit);
		    		regionKeys.push_front(rc.getName_key());
		    		regionValues.push_front(rc.getRegion().getName_key());
			    }

			    int currentRegionKey = 1;

			    for (itrn = regionKeys.begin();
			    	 itrn != regionKeys.end();
			    	 itrn++,
			    	 currentRegionKey++)
			    {
			    	std::string regionKey = ElectionStringResourcesManager::Current()->getResource(*itrn);

			    	switch(currentRegionKey)
			    	{
			    	case 1:
			    		region1Key = regionKey;
			    		break;
			    	case 2:
			    		region2Key = regionKey;
			    		break;
			    	case 3:
			    		region3Key = regionKey;
			    		break;
			    	case 4:
			    		region4Key = regionKey;
			    		break;
			    	case 5:
			    		region5Key = regionKey;
			    		break;
			    	case 6:
			    		region6Key = regionKey;
			    		break;
			    	case 7:
			    		region7Key = regionKey;
			    		break;
			    	}
			    }

			    int currentRegionValue = 1;

			    for (itrn = regionValues.begin();
			    	 itrn != regionValues.end();
			    	 itrn++,
			    	 currentRegionValue++)
			    {
			    	std::string regionValue = ElectionStringResourcesManager::Current()->getResource(*itrn);

			    	switch(currentRegionValue)
			    	{
			    	case 1:
			    		region1Value = regionValue;
			    		break;
			    	case 2:
			    		region2Value = regionValue;
			    		break;
			    	case 3:
			    		region3Value = regionValue;
			    		break;
			    	case 4:
			    		region4Value = regionValue;
			    		break;
			    	case 5:
			    		region5Value = regionValue;
			    		break;
			    	case 6:
			    		region6Value = regionValue;
			    		break;
			    	case 7:
			    		region7Value = regionValue;
			    		break;
			    	}
			    }
			}
			else
			{
				logger->Debug("ERROR - region hierarchies not found");
			}

			votingCenterValue = ElectionStringResourcesManager::Current()->getResource(vb.getPolling_place_name());
			votingCenterAddressValue = ElectionStringResourcesManager::Current()->getResource(vb.getPolling_place_address());

			std::stringstream ss1;
			ss1 << vb.getRegistered_electors();
			registeredElectorsValue = ss1.str();

			std::stringstream ss2;
			ss2 << vb.getPolling_station_code();
			pollingStationCodeValue = ss2.str();
		}
		else
		{
			logger->Debug("Fatal - Error voting booth not found");
			validate = false;
		}
	}
	catch(...)
	{
		logger->Debug("Fatal - Error load electoral configuration");
		validate = false;
	}

    if(!validate)
    {
        messageError->set_label(_(messageErrorKey.c_str()));
        this->add(*messageError);
        return;
    }

    electionNameValue = ElectionStringResourcesManager::Current()->getResource(
            electoralConfiguration->getElection()->getElection().getName_key());

	versionValue = VERSION;

	std::vector < std::vector<std::string> >::iterator mapit;

	for (mapit = composePair.begin();
		 mapit != composePair.end();
		 mapit++)
	{
		std::string composedKey = composeKey((*mapit)[0]);
		std::string composedValue = composeValue((*mapit)[1]);
		compositePair(composedKey, composedValue);
	}

	if (infoWidget) delete infoWidget;

	infoWidget = new InfoWidget(info);
	infoWidget->set_shadow_type(Gtk::SHADOW_NONE);

	this->add(*infoWidget);
}

std::string PollingPlaceInfoWidget::composeKey(std::string toCompose)
{
	std::string compose = Glib::ustring::compose(_(toCompose.c_str()),
			_(votingCenterKey.c_str()),
			_(versionKey.c_str()),
			_(votingCenterAddressKey.c_str()),
			_(electionNameKey.c_str()),
			_(registeredElectorsKey.c_str()),
			_(pollingStationCodeKey.c_str()),
			_(votingDeviceCustomCodeKey.c_str()));

	return Glib::ustring::compose(compose,
			region1Key,
			region2Key,
			region3Key,
			region4Key,
			region5Key,
			region6Key,
			region7Key);
}

std::string PollingPlaceInfoWidget::composeValue(std::string toCompose)
{
	std::string compose = Glib::ustring::compose(_(toCompose.c_str()),
			votingCenterValue,
			versionValue,
			votingCenterAddressValue,
			electionNameValue,
			registeredElectorsValue,
			pollingStationCodeValue,
			votingDeviceCustomCodeValue);

	return Glib::ustring::compose(compose,
			region1Value,
			region2Value,
			region3Value,
			region4Value,
			region5Value,
			region6Value,
			region7Value);
}

void PollingPlaceInfoWidget::addCompositePair(std::string key, std::string value)
{
	int index = composePair.size();

	composePair.push_back(std::vector<std::string> ());
	composePair[index].push_back(key);
	composePair[index].push_back(value);
}

void PollingPlaceInfoWidget::compositePair(std::string key, std::string value)
{
	int index = info.size();

	info.push_back(std::vector<std::string> ());
	info[index].push_back(key);
	info[index].push_back(value);
}
