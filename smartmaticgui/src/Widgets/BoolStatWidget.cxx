/**
 * @file BoolStatWidget.cxx
 * @brief Body class boolean state widget
 * @date 08/05/2012
 * @author Yadickson Soto
 */

#include "BoolStatWidget.hxx"

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

#define OPTION_TRUE  N_("Smartmatic.GUI.Widgets.BoolStatWidget.True") ///< option true
#define OPTION_FALSE N_("Smartmatic.GUI.Widgets.BoolStatWidget.False") ///< option false

using namespace Smartmatic::GUI::Widgets;

std::string BoolStatWidget::True = "true"; ///< true
std::string BoolStatWidget::False = "false"; ///< false
std::string BoolStatWidget::None = ""; ///< none

BoolStatWidget::BoolStatWidget(std::string name, std::string code, bool mandatory)
: IStatWidget(name, code)
{
	std::vector <Glib::ustring> vector;
	vector.push_back(BoolStatWidget::None);
	vector.push_back(_(OPTION_TRUE));
	vector.push_back(_(OPTION_FALSE));

	comboBox = new SmartmaticComboBox();
	comboBox->set_size_request(-1, -1);
	comboBox->SetOptions(vector);
	comboBox->SetSelection(_(OPTION_FALSE));
	comboBox->signal_combo_changed().connect(sigc::mem_fun(*this,&BoolStatWidget::comboChanged));

	this->mandatory = mandatory;
	add(*comboBox);
}

BoolStatWidget::~BoolStatWidget()
{
	remove();

	if (comboBox)
	{
		delete comboBox;
		comboBox = NULL;
	}
}

std::string BoolStatWidget::getValue()
{
	std::string value;

	if (comboBox->GetSelection() == _(OPTION_TRUE))
	{
		value = True;
	}
	else if (comboBox->GetSelection() == _(OPTION_FALSE))
	{
		value = False;
	}
	else
	{
		value = BoolStatWidget::None;
	}

	return value;
}

void BoolStatWidget::setValue(std::string value)
{
	set_name("");

	if (value == True)
	{
		comboBox->SetSelection(_(OPTION_TRUE));
	}
	else if (value == False)
	{
		comboBox->SetSelection(_(OPTION_FALSE));
	}
	else
	{
		comboBox->SetSelection(BoolStatWidget::None);
	}
}

void BoolStatWidget::setEnable(bool enable)
{
	comboBox->set_sensitive(enable);
}

void BoolStatWidget::setSize(int width, int height)
{
	IStatWidget::setSize(comboBox, width, height);
}

bool BoolStatWidget::validate()
{
	bool validate = true;

	if (mandatory)
	{
		validate = comboBox->GetSelection() != BoolStatWidget::None;

		if (!validate)
		{
			set_name("combo_error_frame");
		}
	}

	return validate;
}

void BoolStatWidget::comboChanged(Glib::ustring text)
{
	set_name("");
}
