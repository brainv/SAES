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

#include "printer-client.h"

using namespace Smartmatic::SAES::Printing;

PrinterClient::PrinterClient()
{

}

PrinterClient::~PrinterClient()
{

}

void PrinterClient::on_ticket_printed (Gtk::PrintOperationResult result)
{
}

void PrinterClient::on_job_finished (
    const Glib::RefPtr<Gtk::PrintOperation>& operation)
{
}

void PrinterClient::on_status_reported (PrinterStatus *status)
{
}
