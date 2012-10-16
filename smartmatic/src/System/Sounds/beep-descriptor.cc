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

#include "System/Sounds/beep-descriptor.h"

using namespace Smartmatic::System::Sounds;

BeepDescriptor::BeepDescriptor()
{

};

BeepDescriptor::BeepDescriptor(int frequencyArg, int timeArg, int repetitionsArg, int timeBetweenRepetitionsArg)
{
	frequency = frequencyArg;
	time = timeArg;
	repetitions = repetitionsArg;
	timeBetweenRepetitions = timeBetweenRepetitionsArg;
};

std::string BeepDescriptor::GetBeepLine()
{
	std::string beepLine;
	std::stringstream frecuencyS;
	std::stringstream timeS;
	std::stringstream repetitionsS;
	std::stringstream timeBetweenRepetitionsS;
	frecuencyS << frequency;
	timeS << time;
	repetitionsS << repetitions;
	timeBetweenRepetitionsS << timeBetweenRepetitions;

	beepLine = " -f " + frecuencyS.str() + " -l " + timeS.str() + " -r " + repetitionsS.str() + " -d " + timeBetweenRepetitionsS.str();
		
	return beepLine;
};
