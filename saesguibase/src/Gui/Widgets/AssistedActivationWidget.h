/*
 * AssistedActivationWidget.h
 *
 *  Created on: Jul 26, 2011
 *      Author: Juan.Delgado
 */

#ifndef ASSISTEDACTIVATIONWIDGET_H_
#define ASSISTEDACTIVATIONWIDGET_H_

#include <gtkmm.h>
#include <Voting/PBReports/assisted-activation-schema.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class AssistedActivationWidgetPerson: public Gtk::Frame
				{
				public:
					AssistedActivationWidgetPerson(std::string title, std::string name);

					virtual ~AssistedActivationWidgetPerson();
				};

				class AssistedActivationWidget: public Gtk::Frame
				{
				public:

					AssistedActivationWidget(Smartmatic::SAES::Voting::PBReports::Activation activation);

					virtual ~AssistedActivationWidget();
				};
			}
		}
	}
}

#endif /* ASSISTEDACTIVATIONWIDGET_H_ */
