/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saeshardware
 * Copyright (C)  2011 <>
 * 
 * saeshardware is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saeshardware is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "command-base-p168-a.h"

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

using namespace std;
using namespace Smartmatic::SAES::HW::Commands;

CommandBaseP168A::CommandBaseP168A():CommandStructure()
{
	addListener(this);
}


void CommandBaseP168A::getOrderOfCommand()
{
	addSection(sections::Sender);
	addSection(sections::CommandByte);
	addSection (sections::Lenght);
	addSection (sections::Data);

}


std::vector<unsigned char> ProviderLenghtP168A::getLenght(int commandDataSize)
{
	std::vector<unsigned char> lenght;
	unsigned char ByteLenght1 = commandDataSize & 0x000000ff;
	lenght.push_back(ByteLenght1);
	return lenght;
}

std::vector<unsigned char> ProviderCheckSumP168A::getCheckSum(vector<unsigned char> data)
{
	int checkTotal = 0;
	std::vector<unsigned char> checksum;
	int size = data.size();
	for(int i=0;i<size;i++)
	{
		checkTotal += data[i];
	}
	checksum.push_back(checkTotal);
	return checksum;
}

std::vector<unsigned char> ProviderTrailerP168A::getTrailer()
{
	std::vector<unsigned char> trailer;
	return trailer;
}

std::vector<unsigned char> ProviderSenderP168A::getSender()
{
	std::vector<unsigned char> sender;
	sender.push_back(0x1B);
	return sender;
}

std::vector<unsigned char> CommandBaseP168A::Execute(Smartmatic::SAES::HW::Connections::IConnection* connectionProvider)
{
	ProviderSenderP168A sender;
	ProviderLenghtP168A lenght;
	if(result.size() == 0)
	{
		result = this->GetData(&sender, NULL, &lenght, NULL, NULL,NULL,NULL);
	}

	std::vector<unsigned char> response = this->sendData(connectionProvider);

	GetSpecificResponseFromRaw();
	return rawResponse;
}
