/*
 * AssistedActivationWidget.cpp
 *
 *  Created on: Jul 26, 2011
 *      Author: Juan.Delgado
 */

#include "AssistedActivationWidget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Configuration/SaesGUIConfiguration-schema.hxx"
#include <Widgets/SmartmaticTextView.h>
#include <Configuration/label-configuration.h>

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
using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::PBReports;

AssistedActivationWidgetPerson::AssistedActivationWidgetPerson(std::string title, std::string name)
{
	ColorConfiguration colorConfTitle = SAESGUIConfigurationManager::Current()->getAssistedActivationPreviewTitleColor();
	Gdk::Color selectedColorTitle;
	selectedColorTitle.set_rgb(colorConfTitle.getRed(), colorConfTitle.getGreen(), colorConfTitle.getBlue());

	ColorConfiguration colorConfContent = SAESGUIConfigurationManager::Current()->getAssistedActivationPreviewContentColor();
	Gdk::Color selectedColorPrincipal;
	selectedColorPrincipal.set_rgb(colorConfContent.getRed(), colorConfContent.getGreen(), colorConfContent.getBlue());

	static Smartmatic::GUI::Configuration::LabelConfiguration labelNameConf = SAESGUIConfigurationManager::Current()->GetNameLabelConfiguration();

	Pango::FontDescription fontTitle;

	Label* titleLabel = manage(new Label(title));
	titleLabel->set_alignment(0.5, 0.5);
	fontTitle = titleLabel->get_style()->get_font();
	fontTitle.set_size(13*Pango::SCALE);
	titleLabel->modify_font(fontTitle);

	EventBox* titleEvent = manage(new EventBox());
	titleEvent->add(*titleLabel);
	titleEvent->show_all_children();
	titleEvent->modify_bg(Gtk::STATE_NORMAL, selectedColorTitle);
	titleEvent->set_size_request(-1, 30);

	Label* nameLabel = manage(new Label(name));

	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(nameLabel, labelNameConf);

	EventBox* nameEvent = manage(new EventBox());
	nameEvent->add(*nameLabel);
	nameEvent->show_all_children();
	nameEvent->modify_bg(Gtk::STATE_NORMAL, selectedColorPrincipal);
	nameEvent->set_size_request(-1, 30);

	VBox* vbox = manage(new VBox());
	vbox->pack_start(*titleEvent);
	vbox->pack_start(*nameEvent);

	add(*vbox);
	show_all_children();
	set_size_request(230, -1);
}

AssistedActivationWidgetPerson::~AssistedActivationWidgetPerson()
{

}

AssistedActivationWidget::AssistedActivationWidget(Activation activation)
{
	AssistedActivationWidgetPerson* pollWorker = manage(new AssistedActivationWidgetPerson(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.Pollworker"),
			activation.getPollworker().getFirstName() + " " + activation.getPollworker().getSurname()));
	AssistedActivationWidgetPerson* voter = manage(new AssistedActivationWidgetPerson(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.Voter"),
			activation.getVoter().getFirstName() + " " + activation.getVoter().getSurname()));
	AssistedActivationWidgetPerson* propossed = manage(new AssistedActivationWidgetPerson(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.PropossedPerson"),
			activation.getPropossedPerson().getFirstName() + " " + activation.getPropossedPerson().getSurname()));

	Table* table = manage(new Table());
	table->attach(*pollWorker, 0,1,0,1, FILL, FILL, 3,5);
	table->attach(*voter, 1,2,0,1, FILL, FILL, 3,5);
	table->attach(*propossed, 0,2,1,2, FILL, FILL, 120,3);

	Pango::FontDescription fontTitle;

	string typeActivation;

	switch(activation.getActivationMode())
	{
		case ActivationMode::ASSISTED_ACTIVATION_PROXY:
			typeActivation = _("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.ProxyActivation");
			break;
		case ActivationMode:: ASSISTED_ACTIVATION_PRESENTIAL:
			typeActivation = _("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.PresentialActivation");
			break;
	}
	typeActivation.append(" ");

	Label* impugnationLabel = manage(new Label());
	impugnationLabel->set_alignment(0.5, 0.5);
	fontTitle = impugnationLabel->get_style()->get_font();
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	fontTitle.set_size(14*Pango::SCALE);
	impugnationLabel->modify_font(fontTitle);

	table->attach(*impugnationLabel, 0,2,2,3, FILL, FILL, 0, 10);

	if(activation.getWasImpugned())
	{
		typeActivation.append(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.ActivationImpugnated"));

		AssistedActivationWidgetPerson* impugnator = manage(new AssistedActivationWidgetPerson(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.Impugnator"),
					activation.getImpugnator().get().getFirstName() + " " + activation.getImpugnator().get().getSurname()));
		AssistedActivationWidgetPerson* designated = manage(new AssistedActivationWidgetPerson(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.DesignatedPerson"),
					activation.getDesignatedPerson().get().getFirstName() + " " + activation.getDesignatedPerson().get().getSurname()));

		table->attach(*impugnator, 0,1,3,4, FILL, FILL, 3,5);
		table->attach(*designated, 1,2,3,4, FILL, FILL, 3,5);

		Label* reasonLabel = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.ReasonTitle")));
		reasonLabel->set_alignment(0.5, 0.5);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
		fontTitle = reasonLabel->get_style()->get_font();
		fontTitle.set_size(14*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
		reasonLabel->modify_font(fontTitle);

		table->attach(*reasonLabel, 0,2,4,5, FILL, FILL, 0, 10);

		string impugnationText = activation.getImpugnationReason().get();

		/*Glib::RefPtr<TextBuffer> buffer = TextBuffer::create();
		buffer->set_text(impugnationText);

		SmartmaticTextView* textReason = manage(new SmartmaticTextView());
		textReason->set_buffer(buffer);
		textReason->set_wrap_mode(WRAP_WORD);
		textReason->set_sensitive(false);

		ScrolledWindow* scrollReason = manage(new ScrolledWindow());
		scrollReason->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
		scrollReason->add(*textReason);
		scrollReason->show_all_children ();
		scrollReason->set_size_request(-1, 80);

		table->attach(*scrollReason, 0,2,5,6, FILL, FILL, 3, 5);*/
	}
	else
	{
		typeActivation.append(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.ActivationNotImpugnated"));
	}

	impugnationLabel->set_text(typeActivation);

	add(*table);
	show_all_children();
	set_shadow_type(SHADOW_IN);
}

AssistedActivationWidget::~AssistedActivationWidget()
{
}
