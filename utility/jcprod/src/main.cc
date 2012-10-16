/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Cordovi 2011 <marcel.cordovi@smartmatic.com>
 * 
 * jcprod is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * jcprod is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm.h>
#include <iostream>


#ifdef ENABLE_NLS
#  include <libintl.h>
#endif


#include <AppController.h>
#include <AppMainWindow.h>


/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/jcprod/ui/jcprod.ui" */
#define UI_FILE "src/jcprod.ui"
   
int
main (int argc, char *argv[])
{
	
	if(!Glib::thread_supported())
		Glib::thread_init();

	AppController controller;

	Gtk::Main kit(argc, argv);
	AppMainWindow main_win (&controller);
	kit.run(main_win);

	return 0;
}
