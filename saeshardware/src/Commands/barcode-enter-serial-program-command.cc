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

#include "barcode-enter-serial-program-command.h"

using namespace Smartmatic::SAES::HW::Commands;
using namespace std;
BarcodeEnterSerialProgramCommand::BarcodeEnterSerialProgramCommand():CommandBaseBarcode()
{   
	hasResponse = true;
}

void BarcodeEnterSerialProgramCommand::Initialize()
{
	Data.push_back(0x99);
	Data.push_back(0x99);
	Data.push_back(0x99);
}

bool BarcodeEnterSerialProgramCommand::ProccessResponse(vector<unsigned char> response)
{
	if(response.size()>=1/*&& response[0]==0x02 && response[1]==0x06*/)
	{		
		return true;
	}
	return false;
}

void BarcodeEnterSerialProgramCommand::GetSpecificResponseFromRaw()
{
	
}

