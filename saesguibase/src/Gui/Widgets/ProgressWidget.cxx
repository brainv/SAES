/**
 * @file ProgressWidget.cxx
 * @brief Body class progress widget
 * @date 18/10/2011
 * @author Yadickson Soto
 */

#include "ProgressWidget.hxx"
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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Configuration;

ISMTTLog* ProgressWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.ProgressWidget",GETTEXT_PACKAGE);

ProgressWidget::ProgressWidget()
: Gtk::EventBox()
{
	this->mainFrame = NULL;
	this->mainVBox = NULL;
	this->progressImage = NULL;
	this->progressTitle = NULL;
	this->progressLabel = NULL;
	this->progressFooter = NULL;

	this->initialize();
	this->add(*mainFrame);
	this->show_all_children();
}

ProgressWidget::~ProgressWidget()
{
	dispose();
}

void ProgressWidget::initialize()
{
	dispose();

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/ProgressWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - ProgressWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("progress-image", progressImage);
	builder->get_widget("progress-title", progressTitle);
	builder->get_widget("progress-label", progressLabel);
	builder->get_widget("progress-footer", progressFooter);

	Pango::FontDescription fontTitle = progressTitle->get_style()->get_font();
	fontTitle.set_size(20 * Pango::SCALE);
	progressTitle->modify_font(fontTitle);

	Pango::FontDescription fontLabel = progressLabel->get_style()->get_font();
	fontLabel.set_size(20 * Pango::SCALE);
	progressLabel->modify_font(fontLabel);

	progressTitle->set_visible(false);
	progressTitle->set_no_show_all();

	progressFooter->set_visible(false);
	progressFooter->set_no_show_all();
}

void ProgressWidget::dispose()
{
	this->remove();

	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (mainVBox)
	{
		delete mainVBox;
		mainVBox = NULL;
	}
	if (progressImage)
	{
		delete progressImage;
		progressImage = NULL;
	}
	if (progressLabel)
	{
		delete progressLabel;
		progressLabel = NULL;
	}
	if (progressTitle)
	{
		delete progressTitle;
		progressTitle = NULL;
	}
	if (progressFooter)
	{
		delete progressFooter;
		progressFooter = NULL;
	}
}

void ProgressWidget::setImage(ProgressWidget::ProgressImage image)
{
	std::string iconFile;

	switch(image)
	{
		case NONE:
			progressImage->clear();
			return;
		case NOT_FOUND:
			iconFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/image-not-found.gif");
			break;
		case PROGRESS:
			iconFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/loading.gif");
			break;
		default:
			return;
	}

	try
	{
		progressImage->set(Gdk::PixbufAnimation::create_from_file(iconFile));
	}
	catch(...)
	{
		logger->Debug("ERROR - load image " + iconFile);
	}
}

void ProgressWidget::setImage(std::string image)
{
	std::string iconFile;

	try
	{
		iconFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, image);
		progressImage->set(Gdk::PixbufAnimation::create_from_file(iconFile));
	}
	catch(...)
	{
		setImage(NOT_FOUND);
		logger->Debug("ERROR - load image " + iconFile);
	}
}

void ProgressWidget::setImage(Glib::RefPtr<Gdk::Pixbuf> pixbuff)
{
	progressImage->set(pixbuff);
}

void ProgressWidget::setTitle(std::string text)
{
	progressTitle->set_visible(true);
	progressTitle->set_text(_(text.c_str()));
}

void ProgressWidget::setText(std::string text)
{
	progressLabel->set_text(_(text.c_str()));
}

void ProgressWidget::setFooter(std::string text)
{
	progressFooter->set_text(_(text.c_str()));
}

void ProgressWidget::setTitleConfig(LabelConfiguration labelConf)
{
	LabelConfiguration::SetLabelConfiguration(progressTitle, labelConf);
}

void ProgressWidget::setTextConfig(LabelConfiguration labelConf)
{
	LabelConfiguration::SetLabelConfiguration(progressLabel, labelConf);
}

void ProgressWidget::setFooterConfig(LabelConfiguration labelConf)
{
	LabelConfiguration::SetLabelConfiguration(progressFooter, labelConf);
}

void ProgressWidget::hideTitle()
{
	progressTitle->hide();
}

void ProgressWidget::showTitle()
{
	progressTitle->show();
}

void ProgressWidget::hideImage()
{
	progressImage->hide();
}

void ProgressWidget::showImage()
{
	progressImage->show();
}

void ProgressWidget::hideText()
{
	progressLabel->hide();
}

void ProgressWidget::showText()
{
	progressLabel->show();
}

void ProgressWidget::hideFooter()
{
	progressFooter->hide();
}

void ProgressWidget::showFooter()
{
	progressFooter->show();
}
