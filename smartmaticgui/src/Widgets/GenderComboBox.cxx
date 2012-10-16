/**
 * @file GenderComboBox.cxx
 * @brief Body class gender widget
 * @date 05/06/2012
 * @author Yadickson Soto
 */

#include "GenderComboBox.hxx"
#include <Configuration/s-m-t-t-g-u-i-conf-manager.h>

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

#define OPTION_FEMALE N_("Smartmatic.GUI.Widgets.GenderComboBox.Female") ///< option female
#define OPTION_MALE N_("Smartmatic.GUI.Widgets.GenderComboBox.Male") ///< option male

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;

std::string GenderComboBox::Female = "f"; ///< female
std::string GenderComboBox::Male = "m"; ///< male
std::string GenderComboBox::None = ""; ///< none

GenderComboBox::GenderComboBox()
: SmartmaticComboBox()
{
	SMTTGUIConfigurationManager::Current()->getGenderFemaleConfiguration(femaleList);
	SMTTGUIConfigurationManager::Current()->getGenderMaleConfiguration(maleList);
	initialize(femaleList, maleList);
}

GenderComboBox::GenderComboBox(std::list<std::string> & femaleList, std::list<std::string> & maleList)
{
	initialize(femaleList, maleList);
}

GenderComboBox::~GenderComboBox()
{

}

void GenderComboBox::initialize(std::list<std::string> & femaleList, std::list<std::string> & maleList)
{
	std::vector <Glib::ustring> vector;
	vector.push_back(GenderComboBox::None);
	vector.push_back(_(OPTION_FEMALE));
	vector.push_back(_(OPTION_MALE));

	SetOptions(vector);
	SetSelection(_(OPTION_MALE));

	this->femaleList = femaleList;
	this->maleList = maleList;
}

std::string GenderComboBox::getValue()
{
	std::string value;

	if (GetSelection() == _(OPTION_FEMALE))
	{
		value = Female;
	}
	else if (GetSelection() == _(OPTION_MALE))
	{
		value = Male;
	}
	else
	{
		value = None;
	}

	return value;
}

void GenderComboBox::setValue(std::string value)
{
	std::list<std::string>::iterator it;

	for (it = femaleList.begin();
			it != femaleList.end();
			it++)
	{
		if (value == (*it))
		{
			SetSelection(_(OPTION_FEMALE));
			return;
		}
	}

	for (it = maleList.begin();
			it != maleList.end();
			it++)
	{
		if (value == (*it))
		{
			SetSelection(_(OPTION_MALE));
			return;
		}
	}

	SetSelection(GenderComboBox::None);
}
