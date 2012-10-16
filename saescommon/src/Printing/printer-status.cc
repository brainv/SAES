/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * MachineApplication
 * Copyright (C) Marcel Cordoví Solés 2010 <marcel.cordovi@smartmatic.com>
 * 
 * MachineApplication is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MachineApplication is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "printer-status.h"
using namespace Smartmatic::SAES::Printing;

bool PrinterStatus::operator== (PrinterStatus other)
{

	return this->online == other.online
		&& this->processing == other.processing
		&& this->paper_present == other.paper_present
		&& this->paper_jam == other.paper_jam;
}

bool PrinterStatus::operator!= (PrinterStatus other)
{
	return ! ((*this) == other);
}