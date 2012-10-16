/*
 * WizardTimeline.h
 *
 *  Created on: May 28, 2011
 *      Author: gerardohernandez
 */

#include <gtkmm.h>

#ifndef WIZARDTIMELINE_H_
#define WIZARDTIMELINE_H_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class WizardTimeline : public Gtk::Frame
			{
				public:
					WizardTimeline(){}
					WizardTimeline(std::vector<std::string> imagesPath, int imageWidth = -1,
							int imageHeight = -1);
					virtual ~WizardTimeline();

					void SetState(int index);

				private:
					std::vector<Gtk::Image*> imageVector;

			};
		}
	}
}

#endif /* WIZARDTIMELINE_H_ */
