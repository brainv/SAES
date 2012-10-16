/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C) Rafael Ferrero 2011 <rafael.ferrero@smartmatic.com>
 * 
 * trunk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * trunk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LogLine.h"
using namespace Smartmatic::SAES::Log;

std::string LogLine::getDate()
{
	return this->date;
}

void LogLine::setDate(std::string date)
{
	this->date = date;
}

std::string LogLine::getLibrary()
{
	return this->library;
}

void LogLine::setLibrary(std::string library)
{
	this->library = library;
}

std::string LogLine::getMessage()
{
	return this->message;
}

void LogLine::setMessage(std::string message)
{
	this->message = message;
}

std::vector<std::string> LogLine::getMessageParams()
{
	return this->messageParams;
}

void LogLine::setMessageParams(std::vector<std::string> messageParams)
{
	this->messageParams = messageParams;
}

LogLine::LevelLog LogLine::getLevel()
{
	return this->level;
}

void LogLine::setLevel(LogLine::LevelLog level)
{
	this->level = level;
}

std::string LogLine::getTimeSinceStart()
{
	return this->timeSinceStart;
}

void LogLine::setTimeSinceStart(std::string timeSinceStart)
{
	this->timeSinceStart = timeSinceStart;
}