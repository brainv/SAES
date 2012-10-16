/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmatic
 * Copyright (C)  2011 <>
 * 
 * smartmatic is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmatic is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "System/Sounds/beep-manager.h"
#include <System/Runtime/ProcessLauncher.h>

using namespace std;
using namespace Smartmatic::System::Sounds;
using namespace Smartmatic::System::Runtime;

void BeepManager::AddBeep(int frequency, int time, int repetitions, int timeBetweenRepetitions)
{
	BeepDescriptor beepDescriptor (frequency, time, repetitions, timeBetweenRepetitions);
	beeps.push_back(beepDescriptor);
};

void BeepManager::Beep()
{
	std::string beeplinebase = "beep ";

	for(unsigned int i = 0; i<beeps.size(); i++)
	{
		beeplinebase += beeps[i].GetBeepLine();
		if(i<beeps.size()-1)
		{
			beeplinebase +=" -n ";
		}
	};

		beeplinebase += " &";
		(void)ProcessLauncher::RunProcessThroughSystem(beeplinebase.c_str());
};

void BeepManager::Clear()
{
	beeps.clear();
};

void BeepManager::AddBeep(BeepDescriptor beepDescriptor)
{
	beeps.push_back(beepDescriptor);
};


