/*
 * ResultWidget.cxx
 *
 *  Created on: 24/10/2011
 *      Author: soto
 */

#include "ResultWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Configuration;

ISMTTLog* ResultWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.ResultWidget",GETTEXT_PACKAGE);

ResultWidget::ResultWidget()
: EventBox()
{
	this->mainFrame = NULL;
	this->label = NULL;
	this->image = NULL;
	this->status = true;
	this->initialize();
	add(*mainFrame);
}

ResultWidget::~ResultWidget()
{
	dispose();
}

void ResultWidget::initialize()
{
	dispose();

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/ResultWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - ResultWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("label", label);
	builder->get_widget("image", image);

	this->set_events(Gdk::BUTTON_PRESS_MASK);
	this->signal_button_press_event().connect(sigc::mem_fun(*this, &ResultWidget::clicked));
}

void ResultWidget::dispose()
{
	this->remove();

	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (image)
	{
		delete image;
		image = NULL;
	}
	if (label)
	{
		delete label;
		label = NULL;
	}
}

void ResultWidget::setText(std::string text, bool center)
{
	if (center)
	{
		label->set_justify(Gtk::JUSTIFY_CENTER);
		label->set_alignment(0.5, 0.5);
	}
	else
	{
		label->set_justify(Gtk::JUSTIFY_RIGHT);
		label->set_alignment(0, 0.5);
	}

	label->set_text(text);
}

void ResultWidget::setStatus(bool status)
{
	this->status = status;
	std::string iconFile;
	iconFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, (status ? "ui/result-ok.png" : "ui/result-error.png"));
	image->set(iconFile);
}

std::string ResultWidget::getText()
{
	return label->get_text();
}

bool ResultWidget::getStatus()
{
	return status;
}

void ResultWidget::addResult(Result & result)
{
	status = status && result.status;
	list.push_back(result);
}

void ResultWidget::setResult(std::list <Result> & list)
{
	this->list.clear();
	this->list.insert(this->list.end(), list.begin(), list.end());

	std::list <Result>::iterator it;

	for (it = list.begin();
			it != list.end() && status;
			it++)
	{
		status = status && (*it).status;
	}

	setStatus(status);
}

std::list <ResultWidget::Result> & ResultWidget::getResult()
{
	return list;
}

void ResultWidget::setLabelConfig(Smartmatic::GUI::Configuration::LabelConfiguration & labelConf)
{
	LabelConfiguration::SetLabelConfiguration(label, labelConf);
}

bool ResultWidget::clicked(GdkEventButton* event)
{
	signal.emit(this);
	return true;
}

sigc::signal<void, ResultWidget * > ResultWidget::getSignalClick()
{
	return signal;
}

