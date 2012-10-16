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

#include "smtt-gui-image-resource-manager.h"

using namespace Smartmatic::GUI::Configuration;

SmttGuiImageResourceManager * SmttGuiImageResourceManager::singleton_instance = NULL;

SmttGuiImageResourceManager *SmttGuiImageResourceManager::Current ()
{ 
	if ( ! singleton_instance )
	{	
		singleton_instance = new SmttGuiImageResourceManager ();
		singleton_instance->Initialize();
	}
	return singleton_instance;
}

void  SmttGuiImageResourceManager::init()
{
	return;
}