/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "System/Sounds/smartmatic-sounds-manager.h"
#include <Environment/Configurations/resource-path-provider.h>
#include "System/Runtime/ProcessLauncher.h"
#include "System/IO/File.h"
#include "System/IO/Path.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace Smartmatic::System::Sounds;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Sounds;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::Runtime;

SMTTSoundsManager * SMTTSoundsManager::singleton_instance = NULL;

SMTTSoundsManager *SMTTSoundsManager::Current ()
{ 
	if ( ! singleton_instance )
		singleton_instance = new SMTTSoundsManager ();

	return singleton_instance;
}

SMTTSoundsManager::SMTTSoundsManager()
{

}

void SMTTSoundsManager::Sound(std::string sound)
{
	bool found = false;

	if (!SmartmaticConfigurationManager::Current()->isUseBeep())
	{
		std::string soundFile = SmartmaticConfigurationManager::Current()->getSoundFile(sound);
		std::string path = Path::Combine(SOUNDDIR, soundFile);
		std::string file = ResourcePathProvider::Current()->GetResourcePath(GETTEXT_PACKAGE, path);

		if (!soundFile.empty() && File::canOpenFile(file))
		{
			found = true;
			std::string command = SmartmaticConfigurationManager::Current()->getAppSound() + " " + file + " &";
			(void)ProcessLauncher::RunProcessThroughSystem(command);
		}
	}
	
	if (!found)
	{
		beepManager.Clear();

		std::vector<BeepDescriptor> beepDescriptors = SmartmaticConfigurationManager::Current()->GetSoundConfiguration(sound);

		for(unsigned int i=0;i < beepDescriptors.size();i++)
		{
			beepManager.AddBeep(beepDescriptors[i]);
		}

		beepManager.Beep();
	}
}
