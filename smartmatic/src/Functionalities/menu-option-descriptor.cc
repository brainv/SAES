/**
 * @file	menu-option-descriptor.cc
 *
 * @brief	menu option descriptor class.
 */

#include "menu-option-descriptor.h"

using namespace std;
using namespace Smartmatic::Functionality;


MenuOptionDescriptor::MenuOptionDescriptor()
{
	
}


const Glib::ustring& MenuOptionDescriptor::getMenuOption() const 
{
	return option;
}


bool MenuOptionDescriptor::getIsMenu() const
{
	return option == "Menu";
}


bool MenuOptionDescriptor::operator<(const MenuOptionDescriptor& other) const
{
	bool isMinus = this->getMenuOption() < other.getMenuOption();
	return isMinus;
}


void MenuOptionDescriptor::setMenuOption(Glib::ustring& specificOption)
{
	option = specificOption;
}
