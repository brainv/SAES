/**
 * @file FormatLabel.cxx
 * @brief Body class format label text
 * @date 11/04/2012
 * @author Yadickson Soto
 */

#include "FormatLabel.hxx"
#include <Operation/MachineOperationManager.hxx>
#include <Resources/election-string-resources-manager.h>
#include <Voting/set-language-functionality.h>

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

using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Voting;

FormatLabel::FormatLabel()
{
	//french resource
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardUsedFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PrinterErrorFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorWriteCardFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorReadingCardFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardFR");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsDemoFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ValidatingCardInsertedFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorInfoVotingCardDataFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardValidityPeriodExpiredFR");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsOfficialFR");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsSimulatedFR");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsRecoveryFR");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.BarcodeErrorTryAgainFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CriticalAlarmCardNotRemoveFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardOrScanVoteFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardAndBarcodeNotFoundFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ReconfigureBarcodeFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardCorrectInsertionIndicationFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardNotProperlyInsertedFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.LabelPreviewCloseQuestionFR");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ButtonBackPreviewFR");

	//netherland resource
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardUsedNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PrinterErrorNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorWriteCardNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorReadingCardNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardNL");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsDemoNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ValidatingCardInsertedNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorInfoVotingCardDataNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardValidityPeriodExpiredNL");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsOfficialNL");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsSimulatedNL");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsRecoveryNL");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.BarcodeErrorTryAgainNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CriticalAlarmCardNotRemoveNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardOrScanVoteNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardAndBarcodeNotFoundNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ReconfigureBarcodeNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardCorrectInsertionIndicationNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardNotProperlyInsertedNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.LabelPreviewCloseQuestionNL");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ButtonBackPreviewNL");

	//deutsch resource
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardUsedDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PrinterErrorDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorWriteCardDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorReadingCardDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardDE");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsDemoDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ValidatingCardInsertedDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorInfoVotingCardDataDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardValidityPeriodExpiredDE");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsOfficialDE");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsSimulatedDE");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsRecoveryDE");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.BarcodeErrorTryAgainDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CriticalAlarmCardNotRemoveDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardOrScanVoteDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardAndBarcodeNotFoundDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ReconfigureBarcodeDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardCorrectInsertionIndicationDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardNotProperlyInsertedDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.LabelPreviewCloseQuestionDE");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ButtonBackPreviewDE");

	//spanish resource
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardUsedES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PrinterErrorES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorWriteCardES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorReadingCardES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardES");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsDemoES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ValidatingCardInsertedES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorInfoVotingCardDataES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardValidityPeriodExpiredES");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsOfficialES");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsSimulatedES");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsRecoveryES");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.BarcodeErrorTryAgainES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CriticalAlarmCardNotRemoveES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardOrScanVoteES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardAndBarcodeNotFoundES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ReconfigureBarcodeES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardCorrectInsertionIndicationES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardNotProperlyInsertedES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.LabelPreviewCloseQuestionES");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ButtonBackPreviewES");

	//english resource
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardUsedEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PrinterErrorEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorWriteCardEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorReadingCardEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardEN");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsDemoEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ValidatingCardInsertedEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorInfoVotingCardDataEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardValidityPeriodExpiredEN");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsOfficialEN");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsSimulatedEN");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsRecoveryEN");
	(void)N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.BarcodeErrorTryAgainEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CriticalAlarmCardNotRemoveEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardOrScanVoteEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardAndBarcodeNotFoundEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ReconfigureBarcodeEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardCorrectInsertionIndicationEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardNotProperlyInsertedEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.LabelPreviewCloseQuestionEN");
	(void)N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ButtonBackPreviewEN");
}

FormatLabel::~FormatLabel()
{

}

std::string FormatLabel::format(std::string text)
{
	if (text.empty() || text == " ")
	{
		return " ";
	}

	std::string language;
	std::string country;

	SetLanguageFunctionality::getCurrentLanguageCountry(language, country);

	Smartmatic::SAES::Voting::Election::Languages & lang (MachineOperationManager::getInstance()->getElectoralConfiguration()->getLanguages());
	Smartmatic::SAES::Voting::Election::Languages::LanguageSequence & sequence (lang.getLanguage());

	Smartmatic::SAES::Voting::Election::Languages::LanguageIterator it;

	std::list<Smartmatic::SAES::Voting::Election::Language> languages;

	for (it = sequence.begin(); it != sequence.end(); it++)
	{
		if(languages.empty())
		{
			languages.push_back(*it);
		}
		else if(languages.front().getPrecedence() < it->getPrecedence())
		{
			languages.push_back(*it);
		}
		else
		{
			languages.push_front(*it);
		}
	}

	std::list<Smartmatic::SAES::Voting::Election::Language>::iterator iter;

	std::string formattedString;

	for (iter = languages.begin(); iter != languages.end(); iter++)
	{
		std::string currentLanguage(text);
		currentLanguage.append(iter->getLanguage());

		std::string tr = _(currentLanguage.c_str());

		if (tr != currentLanguage && !tr.empty())
		{
			formattedString.append(tr);
			formattedString.append("\n");
		}
		else
		{
			std::string lanCode;
			lanCode = iter->getCode();
			SetLanguageFunctionality::SetNewVotingLanguage(lanCode);

			tr = _(text.c_str());

			formattedString.append(tr);
			formattedString.append("\n");
		}
	}

	if (!formattedString.empty())
	{
		formattedString.resize(formattedString.size() - 1);
	}
	else
	{
		formattedString = _(text.c_str());
	}

	SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(language, country);

	return formattedString;
}

void FormatLabel::checkComposeString(std::string & stringToCheck)
{
	if(stringToCheck.size() > 2)
	{
		if(stringToCheck[stringToCheck.size() - 1] == ' ' &&
		   stringToCheck[stringToCheck.size() - 2] == '-')
		{
			size_t pos = stringToCheck.size();
			stringToCheck.erase(pos - 3, 3);
		}
	}
}

Glib::ustring FormatLabel::contestText(Contest & contest, Glib::ustring & format)
{
	Glib::ustring contestClassName;
    Glib::ustring contestClassDescription;
    Glib::ustring contestTitle;
    Glib::ustring contestAbstract;
    Glib::ustring contestHelp;

    try
    {
		Smartmatic::SAES::Voting::Election::Contest_class & contestClass (MachineOperationManager::getInstance()->getElectoralConfiguration()->getElection()->getContestClass(contest.getContest_class_code()));

		contestClassName = ElectionStringResourcesManager::Current()->getResource(contestClass.getName_key());
		contestClassDescription = ElectionStringResourcesManager::Current()->getResource(contestClass.getDescription_key());

		contestTitle = ElectionStringResourcesManager::Current()->getResource(contest.getTitle_key());
		contestAbstract= ElectionStringResourcesManager::Current()->getResource(contest.getAbstract_key());
		contestHelp= ElectionStringResourcesManager::Current()->getResource(contest.getHelp_key());
    }
    catch(...)
    {

    }

    Glib::ustring newFormat = Glib::ustring::compose(format,
    		contestClassName,
    		contestClassDescription,
    		contestTitle,
    		contestAbstract,
    		contestHelp);

    return newFormat;
}
