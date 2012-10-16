/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "InitializationStatus.hxx"

using namespace std;
using namespace Smartmatic::SAES::Operation::Initiator;

InitializationStatus::InitializationStatus()
{
	isSuccess = false;
	message = "";

	initializationStatus[TestStatus::DirectoryStructure] = TestStatus::NotTested;
	initializationStatus[TestStatus::FilesPresence] = TestStatus::NotTested;
    initializationStatus[TestStatus::FlashPresence] = TestStatus::NotTested;
    initializationStatus[TestStatus::FlashStructure] = TestStatus::NotTested;
    initializationStatus[TestStatus::FilesValidation] = TestStatus::NotTested;
    initializationStatus[TestStatus::ConfigurationLoad] = TestStatus::NotTested;
    initializationStatus[TestStatus::MemoryUsed] = TestStatus::NotTested;
    initializationStatus[TestStatus::MemoryComplete] = TestStatus::NotTested;
}

InitializationStatus::~InitializationStatus()
{
	initializationStatus.clear();
}
	
bool InitializationStatus::getSuccess()
{
	return isSuccess;
}

string InitializationStatus::getMessage()
{
	return message;
}

string InitializationStatus::getImageFileName()
{
	return imageFileName;
}

string InitializationStatus::getImageErrorFileName()
{
	return imageErrorFileName;
}

map<TestStatus::Tests, TestStatus::Tests> & InitializationStatus::getStatuses()
{
	return initializationStatus;
}

void InitializationStatus::setSuccess(bool result)
{
	isSuccess = result;
}

void InitializationStatus::setMessage(string msg)
{
	message.clear();
	message.append(msg);
}

void InitializationStatus::setImageFileName(string img)
{
	imageFileName = img;
}

void InitializationStatus::setImageErrorFileName(string imgErrorFileName)
{
	imageErrorFileName = imgErrorFileName;
}

void InitializationStatus::setStatuses(TestStatus::Tests test, TestStatus::Tests status)
{
	initializationStatus[test] = status;
}

