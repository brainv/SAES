/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "saes-functionality-manager.h"

using namespace Smartmatic::SAES::Functionality;

SaesFunctionalityManager* SaesFunctionalityManager::singleton_instance = NULL;

SaesFunctionalityManager* SaesFunctionalityManager::Current()
{
    if(!singleton_instance)
        singleton_instance = new SaesFunctionalityManager();
    return singleton_instance;
}

bool SaesFunctionalityManager::ExecuteChallenge(Smartmatic::Functionality::Functionality<Smartmatic::Functionality::MenuOptionDescriptor>* funct)
{
    bool result = false;

    bool isRole = funct->GetIsRolePassword();

    Smartmatic::GUI::Windows::PasswordWindow passwordWindow (isRole, funct->getChallengeConfiguration());

    passwordWindow.ShowDialog();

    if(passwordWindow.GetPasswordCorrect())
    {
        result = true;
    }

    return result;
}
