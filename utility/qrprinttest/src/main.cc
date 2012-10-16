/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Marcer Cordoví 2011 <marcel.cordovi@smartmatic.com>
 * 
 * qrprinttest is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * qrprinttest is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm.h>
#include <iostream>
#include <config.h>
#include "QrTestMainWindow.h"

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

#include <Log/SMTTLogManager.h>

#define LOG_CONF_FILENAME LOGDATADIR"/log4-configuration.xml"

using namespace Smartmatic::Log;

int
main (int argc, char *argv[])
{
	SMTTLogManager::Configure(LOG_CONF_FILENAME);
	Gtk::Main kit (argc, argv);
	
	QrTestMainWindow main_win;

	Gtk::Main::run(main_win);

	return 0;
}
