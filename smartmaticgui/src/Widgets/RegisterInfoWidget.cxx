/**
 * @file RegisterInfoWidget.cxx
 * @brief Body class register info widget
 * @date 19/05/2012
 * @author Yadickson Soto
 */

#include "RegisterInfoWidget.hxx"
#include <Environment/Configurations/resource-path-provider.h>
#include <Log/ISMTTLog.h>
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

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Configuration;

ISMTTLog* RegisterInfoWidget::logger = SMTTLogManager::GetLogger("Smartmatic.GUI.Widgets.RegisterInfoWidget",GETTEXT_PACKAGE);

RegisterInfoWidget::RegisterInfoWidget()
: Gtk::EventBox()
{
	mainFrame = NULL;
	mainEventbox = NULL;
	mainVBox = NULL;
	headerFrame = NULL;
	headerEventbox = NULL;
	headerLabel = NULL;
	centerFrame = NULL;
	centerEventbox = NULL;
	centerLabel = NULL;
	bottomFrame = NULL;
	bottomEventbox = NULL;
	bottomLabel = NULL;
	table = NULL;

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/RegisterInfoWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - RegisterInfoWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("main-eventbox", mainEventbox);
	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("header-frame", headerFrame);
	builder->get_widget("header-eventbox", headerEventbox);
	builder->get_widget("header-label", headerLabel);
	builder->get_widget("center-frame", centerFrame);
	builder->get_widget("center-eventbox", centerEventbox);
	builder->get_widget("bottom-frame", bottomFrame);
	builder->get_widget("bottom-eventbox", bottomEventbox);
	builder->get_widget("bottom-label", bottomLabel);

	table = new TableWidget(Gtk::FILL, Gtk::FILL);
	table->setSpacings(0, 10);
	table->getTable()->set_homogeneous(false);

	centerLabel = new Gtk::Label();
	centerLabel->set_alignment(0.5, 0.5);

	mainEventbox->set_events(Gdk::BUTTON_PRESS_MASK);
	mainEventbox->signal_button_press_event().connect(sigc::mem_fun(*this, &RegisterInfoWidget::clicked));

	headerFrame->set_no_show_all();
	centerFrame->set_no_show_all();
	bottomFrame->set_no_show_all();

	headerFrame->set_shadow_type(Gtk::SHADOW_IN);
	centerFrame->set_shadow_type(Gtk::SHADOW_IN);
	bottomFrame->set_shadow_type(Gtk::SHADOW_IN);

	headerEventbox->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("White"));
	bottomEventbox->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("White"));

	Pango::FontDescription fontTitle;

	fontTitle = headerLabel->get_style()->get_font();
	fontTitle.set_size(12*Pango::SCALE);
	headerLabel->modify_font(fontTitle);

	fontTitle = centerLabel->get_style()->get_font();
	fontTitle.set_size(10*Pango::SCALE);
	centerLabel->modify_font(fontTitle);

	fontTitle = bottomLabel->get_style()->get_font();
	fontTitle.set_size(12*Pango::SCALE);
	bottomLabel->modify_font(fontTitle);

	showHeader();
	showCenter();
	showBottom();

	flagInfo = false;

	add(*mainFrame);
	show_all_children();
}

RegisterInfoWidget::~RegisterInfoWidget()
{
	remove();

	if (mainEventbox)
	{
		delete mainEventbox;
		mainEventbox = NULL;
	}
	if (mainVBox)
	{
		delete mainVBox;
		mainVBox = NULL;
	}
	if (headerFrame)
	{
		delete headerFrame;
		headerFrame = NULL;
	}
	if (headerEventbox)
	{
		delete headerEventbox;
		headerEventbox = NULL;
	}
	if (headerLabel)
	{
		delete headerLabel;
		headerLabel = NULL;
	}
	if (centerFrame)
	{
		delete centerFrame;
		centerFrame = NULL;
	}
	if (centerEventbox)
	{
		delete centerEventbox;
		centerEventbox = NULL;
	}
	if (centerLabel)
	{
		delete centerLabel;
		centerLabel = NULL;
	}
	if (bottomFrame)
	{
		delete bottomFrame;
		bottomFrame = NULL;
	}
	if (bottomEventbox)
	{
		delete bottomEventbox;
		bottomEventbox = NULL;
	}
	if (bottomLabel)
	{
		delete bottomLabel;
		bottomLabel = NULL;
	}
	if (table)
	{
		delete table;
		table = NULL;
	}
}

void RegisterInfoWidget::addHeader(std::string title, std::string content)
{
	headerLabel->set_label(title + " <b>" + content + "</b>");
}

void RegisterInfoWidget::addCenter(std::string title, std::string content)
{
	flagInfo = true;

	Gtk::Label * labelTitle = manage(new Gtk::Label(title));
	Gtk::Label * labelText = manage(new Gtk::Label(content));

	Pango::FontDescription fontTitle;
	fontTitle = labelTitle->get_style()->get_font();
	fontTitle.set_size(12*Pango::SCALE);
	labelTitle->modify_font(fontTitle);

	fontTitle = labelText->get_style()->get_font();
	fontTitle.set_size(12*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	labelText->modify_font(fontTitle);

	labelTitle->set_alignment(0.0, 0.5);
	labelText->set_alignment(0.0, 0.5);

	labelTitle->set_justify(Gtk::JUSTIFY_LEFT);
	labelText->set_justify(Gtk::JUSTIFY_LEFT);

	int row = table->getCountElements() / 2;

	table->put(labelTitle, row, 0);
	table->put(labelText, row, 1);

	centerEventbox->remove();
	centerEventbox->add(*table);
	centerEventbox->show_all_children();
}

void RegisterInfoWidget::addBottom(std::string title, std::string content)
{
	bottomLabel->set_label(title + " <b>" + content + "</b>");
}

void RegisterInfoWidget::putCenterMessage(std::string message)
{
	flagInfo = false;
	centerLabel->set_label(message);
	centerLabel->set_alignment(0.5, 0.5);
	centerLabel->set_line_wrap(false);

	centerEventbox->remove();
	centerEventbox->add(*centerLabel);
	centerEventbox->show_all_children();
}

void RegisterInfoWidget::putWrapMessage(std::string message)
{
	flagInfo = false;
	centerLabel->set_label(message);
	centerLabel->set_alignment(0.0, 0.0);
	centerLabel->set_line_wrap(true);
	centerLabel->set_line_wrap_mode(Pango::WRAP_WORD);

	centerEventbox->remove();
	centerEventbox->add(*centerLabel);
	centerEventbox->show_all_children();
}

void RegisterInfoWidget::clearAll()
{
	clearHeader();
	clearCenter();
	clearBottom();
}

void RegisterInfoWidget::clearHeader()
{
	headerLabel->set_label("");
}

void RegisterInfoWidget::clearCenter()
{
	flagInfo = false;
	centerLabel->set_label("");
	table->clear();
}

void RegisterInfoWidget::clearBottom()
{
	bottomLabel->set_label("");
}

void RegisterInfoWidget::showHeader(bool show)
{
	headerFrame->set_visible(show);
}

void RegisterInfoWidget::showCenter(bool show)
{
	centerFrame->set_visible(show);
}

void RegisterInfoWidget::showBottom(bool show)
{
	bottomFrame->set_visible(show);
}

void RegisterInfoWidget::hideHeader()
{
	headerFrame->hide();
}

void RegisterInfoWidget::hideCenter()
{
	centerFrame->hide();
}

void RegisterInfoWidget::hideBottom()
{
	bottomFrame->hide();
}

void RegisterInfoWidget::setHeaderConfig(Smartmatic::GUI::Configuration::LabelConfiguration labelConf)
{
	LabelConfiguration::SetLabelConfiguration(headerLabel, labelConf);
}

void RegisterInfoWidget::setCenterConfig(Smartmatic::GUI::Configuration::LabelConfiguration labelConf)
{
	LabelConfiguration::SetLabelConfiguration(centerLabel, labelConf);
}

void RegisterInfoWidget::setBottomConfig(Smartmatic::GUI::Configuration::LabelConfiguration labelConf)
{
	LabelConfiguration::SetLabelConfiguration(bottomLabel, labelConf);
}

bool RegisterInfoWidget::clicked(GdkEventButton* event)
{
	logger->Debug("Click");

	signal.emit(flagInfo);
	return true;
}

sigc::signal<void, bool> RegisterInfoWidget::getSignalClick()
{
	return signal;
}
