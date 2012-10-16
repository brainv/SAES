/**
 * @file BeidWidget.cpp
 * @brief Body class beid widget
 * @date 22/04/2011
 * @author Gerardo Hernandez
 */

#include "BeidWidget.h"
#include "Environment/Configurations/resource-path-provider.h"

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

using namespace std;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::Environment;

BeidWidget::BeidWidget(Smartmatic::SAES::EID::CitizenInfo citizenInfo, Glib::RefPtr<Gdk::Pixbuf> pixbuf, bool showIdNumber)
{
	set_homogeneous(FALSE);
	resize(/*rows*/2, /*columns*/1);

	tableTypeCard = manage(new Gtk::Table());
	tableTypeCard->resize(/*rows*/2, /*columns*/4);

	LabelConfiguration contentLavelConfiguration = GetLabelContentValueConfiguration();
	LabelConfiguration contentBoldLavelConfiguration = GetLabelContentBoldValueConfiguration();
	LabelConfiguration headerConfiguration = GetLabelHeaderConfiguration();
	labelbelgique = manage(new Gtk::Label());
	labelbelgique->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.BELGIQUE"));

	labelbelgie = manage(new Gtk::Label());
	labelbelgie->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.BELGIE"));

	labelbelgien = manage(new Gtk::Label());
	labelbelgien->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.BELGIEN"));

	labelbelgium = manage(new Gtk::Label());
	labelbelgium->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.BELGIUM"));

	LabelConfiguration::SetLabelConfiguration(labelbelgique, headerConfiguration);
	LabelConfiguration::SetLabelConfiguration(labelbelgie, headerConfiguration);
	LabelConfiguration::SetLabelConfiguration(labelbelgien, headerConfiguration);
	LabelConfiguration::SetLabelConfiguration(labelbelgium, headerConfiguration);

	LabelConfiguration headerValuesConfiguration = GetLabelHeaderValueConfiguration();

	labelcartee = manage(new Gtk::Label());
	labelcartee->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.CarteE"));

	labelekaart = manage(new Gtk::Label());
	labelekaart->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.EKaart"));

	labelekarte = manage(new Gtk::Label());
	labelekarte->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.EKarte"));

	labelecard = manage(new Gtk::Label());
	labelecard->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.ECard"));

	LabelConfiguration::SetLabelConfiguration(labelcartee, headerValuesConfiguration);
	LabelConfiguration::SetLabelConfiguration(labelekaart, headerValuesConfiguration);
	LabelConfiguration::SetLabelConfiguration(labelekarte, headerValuesConfiguration);
	LabelConfiguration::SetLabelConfiguration(labelecard, headerValuesConfiguration);

	tableTypeCard->attach(*labelbelgique, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 5, 0);
	tableTypeCard->attach(*labelbelgie, 1, 2, 0, 1, Gtk::FILL, Gtk::FILL, 5, 0);
	tableTypeCard->attach(*labelbelgien, 2, 3, 0, 1, Gtk::FILL, Gtk::FILL, 5, 0);
	tableTypeCard->attach(*labelbelgium, 3, 4, 0, 1, Gtk::FILL, Gtk::FILL, 5, 0);

	tableTypeCard->attach(*labelcartee, 0, 1, 1, 2, Gtk::FILL, Gtk::FILL, 5, 0);
	tableTypeCard->attach(*labelekaart, 1, 2, 1, 2, Gtk::FILL, Gtk::FILL, 5, 0);
	tableTypeCard->attach(*labelekarte, 2, 3, 1, 2, Gtk::FILL, Gtk::FILL, 5, 0);
	tableTypeCard->attach(*labelecard, 3, 4, 1, 2, Gtk::FILL, Gtk::FILL, 5, 0);

	attach(*tableTypeCard, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);

	boxIdContent = manage(new Gtk::Table());
	boxIdContent->resize(/*rows*/2, /*columns*/1);

	nameTable = manage(new Gtk::Table());
	nameTable->resize(/*rows*/2, /*columns*/2);

	labelName = manage(new Gtk::Label());
	labelName->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.Name"));  // Nom / Name
	LabelConfiguration::SetLabelConfiguration(labelName, contentLavelConfiguration);

	labelNameValue = manage(new Gtk::Label());
	labelNameValue->set_text(citizenInfo.getSurname());
	LabelConfiguration::SetLabelConfiguration(labelNameValue, contentBoldLavelConfiguration);

	labelGivenNames = manage(new Gtk::Label());
	labelGivenNames->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.GivenNames")); // Prénoms / Given Names
	LabelConfiguration::SetLabelConfiguration(labelGivenNames, contentLavelConfiguration);

	labelGivenNamesValue = manage(new Gtk::Label());
	labelGivenNamesValue->set_text(citizenInfo.getFirstName());
	LabelConfiguration::SetLabelConfiguration(labelGivenNamesValue, contentBoldLavelConfiguration);

	nameTable->attach(*labelName, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
	nameTable->attach(*labelNameValue, 1, 2, 0, 1, Gtk::FILL, Gtk::FILL, 10, 0);
	nameTable->attach(*labelGivenNames, 0, 1, 1, 2, Gtk::FILL, Gtk::FILL, 0, 0);
	nameTable->attach(*labelGivenNamesValue, 1, 2, 1, 2, Gtk::FILL, Gtk::FILL, 10, 0);

	secondBoxIdContent = manage(new Gtk::Table());
	secondBoxIdContent->resize(/*rows*/1, /*columns*/2);

	boxIdContent->attach(*nameTable, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 10, 10);

	pictureTable = manage(new Gtk::Table());
	pictureTable->resize(/*rows*/2, /*columns*/1);

	chipInfoBox = manage(new Gtk::Table());
	chipInfoBox->resize(/*rows*/2, /*columns*/1);

	sexBox = manage(new Gtk::Table());
	sexBox->resize(/*rows*/1, /*columns*/2);

	sexBoxDetail = manage(new Gtk::Table());
	sexBoxDetail->resize(/*rows*/5, /*columns*/1);

	labelTypedeCarte = manage(new Gtk::Label());
	labelTypedeCarte->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.TypeOfCard")); // Type de carte / Type of card
	LabelConfiguration::SetLabelConfiguration(labelTypedeCarte, contentLavelConfiguration);

	labelAttestation = manage(new Gtk::Label());
	labelAttestation->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.RegistrationCertificate")); // Attestation d'enregistrement
	LabelConfiguration::SetLabelConfiguration(labelAttestation, contentBoldLavelConfiguration);

	lableSex = manage(new Gtk::Label());
	lableSex->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.Sex") + citizenInfo.getGender()); // Sexe / Sex
	LabelConfiguration::SetLabelConfiguration(lableSex, contentLavelConfiguration);

	labelCardNo = manage(new Gtk::Label());
	labelCardNo->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.CardNo")); // Nº carte / Card No
	LabelConfiguration::SetLabelConfiguration(labelCardNo, contentLavelConfiguration);

	labelCardNoValue = manage(new Gtk::Label());
	if(showIdNumber)
	{
		labelCardNoValue->set_text(citizenInfo.getNationalNumber());
	}
	else
	{
		labelCardNoValue->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.ShowIdWidget"));
	}

	LabelConfiguration::SetLabelConfiguration(labelCardNoValue, contentBoldLavelConfiguration);

	sexBoxDetail->attach (*labelTypedeCarte, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
	sexBoxDetail->attach (*labelAttestation, 0, 1, 1, 2, Gtk::FILL, Gtk::FILL, 0, 0);
	sexBoxDetail->attach (*lableSex, 0, 1, 2, 3, Gtk::FILL, Gtk::FILL, 0, 0);
	sexBoxDetail->attach (*labelCardNo, 0, 1, 3, 4, Gtk::FILL, Gtk::FILL, 0, 0);
	sexBoxDetail->attach (*labelCardNoValue, 0, 1, 4, 5, Gtk::FILL, Gtk::FILL, 0, 0);

	signatureBox = manage(new Gtk::Table());
	signatureBox->resize(/*rows*/2, /*columns*/1);

	signatureBoxDetail = manage(new Gtk::Table());
	signatureBoxDetail->resize(/*rows*/4, /*columns*/1);

	labelValide = manage(new Gtk::Label());
	labelValide->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.ValidFromUntil")); // Valide du - au / Valid from - until
	LabelConfiguration::SetLabelConfiguration(labelValide, contentLavelConfiguration);

	labelValideValue = manage(new Gtk::Label());
	labelValideValue->set_text(citizenInfo.getValidity() + " - " + citizenInfo.getEndValidity());
	LabelConfiguration::SetLabelConfiguration(labelValideValue, contentBoldLavelConfiguration);

	lableSignatureTitulare = manage(new Gtk::Label());
	lableSignatureTitulare->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.TitularSignature")); // Signature du  titulaire
	LabelConfiguration::SetLabelConfiguration(lableSignatureTitulare, contentLavelConfiguration);

	labelHolderSignature = manage(new Gtk::Label());
	labelHolderSignature->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.HolderSignature")); // Holder's signature
	LabelConfiguration::SetLabelConfiguration(labelHolderSignature, contentLavelConfiguration);

	Glib::RefPtr<Gdk::Pixbuf> img = Gdk::Pixbuf::create_from_file(Smartmatic::Environment::ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/icon_smartcard.gif"));
	chipImage = manage(new Gtk::Image(img));

	pictureImage = manage(new Gtk::Image(pixbuf));
	pictureTable->attach (*pictureImage, 0, 1, 1, 2, Gtk::SHRINK, Gtk::SHRINK, 0, 0);

	signatureBoxDetail->attach (*labelValide, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
	signatureBoxDetail->attach (*labelValideValue, 0, 1, 1, 2, Gtk::FILL, Gtk::FILL, 0, 0);
	signatureBoxDetail->attach (*lableSignatureTitulare, 0, 1, 2, 3, Gtk::FILL, Gtk::FILL, 0, 0);
	signatureBoxDetail->attach (*labelHolderSignature, 0, 1, 3, 4, Gtk::FILL, Gtk::FILL, 0, 0);

	sexBoxDetailAlignment = manage(new Gtk::Alignment());
	sexBoxDetailAlignment->add(*sexBoxDetail);
	sexBoxDetailAlignment->set_padding(0, 0, 30, 5);

	sexBox->attach (*sexBoxDetailAlignment, 1, 2, 0, 1, Gtk::FILL, Gtk::FILL, 10, 0);

	chipImageAlignment = manage(new Gtk::Alignment());
	chipImageAlignment->add(*chipImage);
	chipImageAlignment->set_padding(0, 0, 0, 0);

	sexBox->attach (*chipImageAlignment, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
	signatureBox->attach (*signatureBoxDetail, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);

	chipInfoBox->attach(*sexBox, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
	chipInfoBox->attach(*signatureBox, 0, 1, 1, 2, Gtk::FILL, Gtk::FILL, 0, 0);

	secondBoxIdContent->attach(*chipInfoBox, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
	secondBoxIdContent->attach(*pictureTable, 1, 2, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);

	boxIdContent->attach(*secondBoxIdContent, 0, 1, 1, 2, Gtk::FILL, Gtk::FILL, 0, 0);
	attach(*boxIdContent, 0, 1, 1, 2, Gtk::FILL, Gtk::FILL, 0, 0);

	show_all_children();
}

BeidWidget::~BeidWidget()
{
	//if(pictureImage)
		//delete(pictureImage);
}

LabelConfiguration BeidWidget::GetLabelHeaderConfiguration()
{
	LabelConfiguration configuration;
	configuration.SetLabelAlignment(LeftAlignment);
	configuration.SetVerticalPadding(2);
	configuration.SetHorizontalPadding(2);
	configuration.SetSize(16);
	return configuration;

};

LabelConfiguration BeidWidget::GetLabelHeaderValueConfiguration()
{
	LabelConfiguration configuration;
	configuration.SetLabelAlignment(LeftAlignment);
	configuration.SetVerticalPadding(1);
	configuration.SetHorizontalPadding(1);
	configuration.SetSize(8);
	return configuration;
};

LabelConfiguration BeidWidget::GetLabelContentValueConfiguration()
{
	LabelConfiguration configuration;
	configuration.SetLabelAlignment(LeftAlignment);
	configuration.SetVerticalPadding(1);
	configuration.SetHorizontalPadding(1);
	configuration.SetSize(8);
	return configuration;
};

LabelConfiguration BeidWidget::GetLabelContentBoldValueConfiguration()
{
	LabelConfiguration configuration;
	configuration.SetLabelAlignment(LeftAlignment);
	configuration.SetVerticalPadding(1);
	configuration.SetHorizontalPadding(1);
	configuration.SetSize(8);
	configuration.SetWeight(BoldWeight);
	return configuration;
};

void BeidWidget::ClearWidget()
{
	labelNameValue->set_text("---");
	labelGivenNamesValue->set_text("---");
	lableSex->set_text(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.Sex")); /// "Sexe / Sex -"
	labelCardNoValue->set_text("---");
	labelValideValue->set_text("---");

};

void BeidWidget::UpdateWidgetInfo(Smartmatic::SAES::EID::CitizenInfo citizenInfo, Gtk::Image picture)
{
	labelNameValue->set_text(citizenInfo.getFirstName());
	labelGivenNamesValue->set_text(citizenInfo.getSurname());
	lableSex->set_text(std::string(_("Smartmatic.SAES.GUI.Widgets.BeidWidget.Sex")) + citizenInfo.getGender());
	labelCardNoValue->set_text("---");
	labelValideValue->set_text("---");
};

