/*
 * WizardTimeline.cpp
 *
 *  Created on: May 28, 2011
 *      Author: gerardohernandez
 */

#include "WizardTimeline.h"
#include "Environment/Configurations/resource-path-provider.h"
#include "System/IO/File.h"

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

using namespace Smartmatic::System::IO;
using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Environment;

WizardTimeline::WizardTimeline(vector<string> imagesPath, int imageWidth,
		int imageHeight)
{
	set_shadow_type(Gtk::SHADOW_NONE);
	vector<string>::iterator iter;

	for(iter = imagesPath.begin(); iter != imagesPath.end(); iter++)
	{
		std::string image_path = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, *iter);

		Image* image = NULL;

		if(File::canOpenFile(image_path))
			image = new Image(image_path);
		else
			image = new Image(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/image-not-found.gif"));

		if(imageWidth != -1 && imageHeight != -1)
		{
			Glib::RefPtr<Gdk::Pixbuf> tempPixbuf = image->get_pixbuf();
			tempPixbuf = tempPixbuf->scale_simple(imageWidth, imageHeight, Gdk::INTERP_HYPER);
			image->set(tempPixbuf);
		}

		imageVector.push_back(image);
	}

	SetState(0);
}

WizardTimeline::~WizardTimeline()
{
	vector<Image*>::iterator iter;

	for(iter = imageVector.begin(); iter != imageVector.end(); iter++)
	{
		if(*iter)
			delete *iter;
	}

	imageVector.clear();
}

void WizardTimeline::SetState(int index)
{
	if((int)imageVector.size() >= index)
	{
		vector<Image*>::iterator iter = imageVector.begin();

		for(int i = 0; i < index; i++)
		{
			iter++;
		}

		remove();
		add(*(*iter));
		show_all_children();
	}
}
