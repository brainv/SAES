/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <sstream>
#include <iostream>
#include <fstream>
#include <glib.h>
#include "Voting/PBReports/pollworkers-wrapper.h"
#include <Runtime/Environment/saes-directories.h>
#include "System/guid-class.h"
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <Security/Encryption.hxx>
#include <sstream>
#include <Log/SMTTLogManager.h>
#include "Log/ISMTTLog.h"
#include <Runtime/Environment/DirectoryManager.hxx>

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

using namespace Smartmatic::System;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Voting::Status;

ISMTTLog* PollworkersWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper", GETTEXT_PACKAGE);

PollworkersWrapper::PollworkersWrapper()
{
	pollworkers = NULL;
}

PollworkersWrapper::~PollworkersWrapper()
{
}

void PollworkersWrapper::Persist()
    throw (CryptoException,
           SignedException,
           XmlException)
{
	logger->Debug("Persistence Pollworkers");

    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    Smartmatic::SAES::Voting::PBReports::NamespaceInfomap map;
    map[""].name = NAMESPACE_PBREPORTS;
    map[""].schema = "";

    std::ostringstream os;
    std::string data;

    try
    {
    	serializePollworkers(os,*pollworkers, map, "UTF-8");
    	data = os.str();
    }
    catch(...)
    {
    	logger->Debug("ERROR - Persistence Pollworkers");
    	throw XmlException(
    			_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ErrorParseFile"),
    			N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ErrorParseFile"),
    			logger);
    	return;
    }

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getPollworkersFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getPollworkersFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
        Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileDom,
                Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
        File::copyFile(fileDom, fileFlash);
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileFlash,
        		Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
        File::copyFile(fileFlash, fileDom);
    }
}

bool PollworkersWrapper::Load(std::string xmlFile)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    bool loadFile = false;

    if (!Smartmatic::System::IO::File::canOpenFile( xmlFile ))
    {
        pollworkers = new Pollworkers();
        Notes notes;
        Workers workers;
        pollworkers->setWorkers(workers);
        pollworkers->setNotes(notes);
    }
    else
    {
        try
        {
        	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(xmlFile, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
            std::istringstream istr (data);
            pollworkers = new Pollworkers(*(parsePollworkers(istr,Smartmatic::SAES::Voting::PBReports::Flags::dont_validate)));
            loadFile = true;
        }
        catch (const ::xsd::cxx::tree::exception< char >& e)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__ << " " << e;
            logger->Debug(ss.str());
            logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ErrorLoadingPollWorkers"));
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ErrorParseFile"), logger);
        }
        catch (...)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__;
            logger->Debug(ss.str());
            logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ErrorLoadingPollWorkers"));
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ErrorParseFile"), logger);
        }
    }
    return loadFile;
}

bool PollworkersWrapper::init ()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Dispose();
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    return Load(directories.getPollworkersFileFullPath());
}

bool PollworkersWrapper::getWorker(std::string customCode, Worker & worker)
{
	bool found = false;

	Workers::WorkerIterator it;
	
	for ( it = pollworkers->getWorkers().getWorker().begin();
			it != pollworkers->getWorkers().getWorker().end();
		 ++it)
	{
		Worker w = (*it);

	   if (customCode == w.getCustom_code())
	   {
		  found = true;
		  worker = w;
		  break;
	   }
	}

	return found;
}

void PollworkersWrapper::AddWorker(Worker &worker)
{
	GuidClass guidC = GuidClass::NewGuid();
	worker.setCustom_code((std::string)guidC.ToString());

	Glib::TimeVal time;
	time.assign_current_time();
	std::string now = time.as_iso8601();

	worker.setCreate_date(now);
	pollworkers->getWorkers().getWorker().push_back(worker);

	switch(worker.getMember_type ())
	{
		case WorkerMemberType::POLLWORKERS_PRESIDENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedPresident"));
			break;
		case WorkerMemberType::POLLWORKERS_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedSecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_ASSISTENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedAssistent"));
			break;
		case WorkerMemberType::POLLWORKERS_WITNESS:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedWitness"));
			break;
		case WorkerMemberType::POLLWORKERS_POLICE:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedPolice"));
			break;
		case WorkerMemberType::POLLWORKERS_ASSISTANT_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedAssistantSecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_PRESIDENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedDeputyPresident"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedDeputySecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_ASSISTENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedDeputyAssistent"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_WITNESS:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedDeputyWitness"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_POLICE:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedDeputySecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_ASSISTANT_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedDeputyAssistantSecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.AddedDeputy"));
			break;
	}

	return;
}

void PollworkersWrapper::RemoveWorker(Worker & worker)
{
	Workers::WorkerIterator it;

	for ( it = pollworkers->getWorkers().getWorker().begin();
			it != pollworkers->getWorkers().getWorker().end();
		 ++it)
	{
		Worker w = (*it);

	   if (worker.getCustom_code() == w.getCustom_code())
	   {
		   pollworkers->getWorkers().getWorker().erase(it);
		   break;
	   }
	}

	switch(worker.getMember_type())
	{
		case WorkerMemberType::POLLWORKERS_PRESIDENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedPresident"));
			break;
		case WorkerMemberType::POLLWORKERS_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedSecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_ASSISTENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedAssistent"));
			break;
		case WorkerMemberType::POLLWORKERS_WITNESS:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedWitness"));
			break;
		case WorkerMemberType::POLLWORKERS_POLICE:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedPolice"));
			break;
		case WorkerMemberType::POLLWORKERS_ASSISTANT_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedAssistantSecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_PRESIDENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedDeputyPresident"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedDeputySecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_ASSISTENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedDeputyAssistent"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_WITNESS:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedDeputyWitness"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_POLICE:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedDeputySecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_ASSISTANT_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedDeputyAssistantSecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.DeletedDeputy"));
			break;
	}
}

void PollworkersWrapper::ModifyWorker(Worker & worker)
{
	Workers::WorkerIterator it;

	for ( it = pollworkers->getWorkers().getWorker().begin();
			it != pollworkers->getWorkers().getWorker().end();
		 ++it)
	{
		Worker w = (*it);

	   if (worker.getCustom_code() == w.getCustom_code())
	   {
		   worker.setCreate_date(w.getCreate_date());

    	   pollworkers->getWorkers().getWorker().erase(it);
		   pollworkers->getWorkers().getWorker().push_back(worker);
		   break;
	   }
	}

	switch(worker.getMember_type())
	{
		case WorkerMemberType::POLLWORKERS_PRESIDENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedPresident"));
			break;
		case WorkerMemberType::POLLWORKERS_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedSecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_ASSISTENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedAssistent"));
			break;
		case WorkerMemberType::POLLWORKERS_WITNESS:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedWitness"));
			break;
		case WorkerMemberType::POLLWORKERS_POLICE:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedPolice"));
			break;
		case WorkerMemberType::POLLWORKERS_ASSISTANT_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedAssistantSecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_PRESIDENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedDeputyPresident"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedDeputySecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_ASSISTENT:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedDeputyAssistent"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_WITNESS:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedDeputyWitness"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_POLICE:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedDeputySecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY_ASSISTANT_SECRETARY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedDeputyAssistantSecretary"));
			break;
		case WorkerMemberType::POLLWORKERS_DEPUTY:
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.ModifiedDeputy"));
			break;
	}
}

Workers & PollworkersWrapper::getWorkers()
{
	return pollworkers->getWorkers();
}

void PollworkersWrapper::AddNote(Note &note)
{
	GuidClass guidC = GuidClass::NewGuid();
	note.setCustom_code(guidC.ToString());

	Glib::TimeVal time;
	time.assign_current_time();
	std::string now = time.as_iso8601();

	note.setCreate_date(now);

	pollworkers->getNotes().getNote().push_back (note);
	logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.NoteAdded"));
}

void PollworkersWrapper::RemoveNote(std::string customCode)
{
	for (Notes::NoteIterator
         n (pollworkers->getNotes ().getNote().begin ());
         n != pollworkers->getNotes ().getNote().end ();
         ++n)
    {
       if ( customCode.compare((*n).getCustom_code()) == 0 )
       {
          pollworkers->getNotes ().getNote().erase(n);
          logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.NoteDeleted"));
		  break;
       }
    }
}

void PollworkersWrapper::ModifyNote(Note & note)
{
	for (Notes::NoteIterator
         n (pollworkers->getNotes ().getNote().begin ());
         n != pollworkers->getNotes ().getNote().end ();
         ++n)
    {
       if ( note.getCustom_code().compare((*n).getCustom_code())== 0 )
       {
    	   Note current = (*n);
    	   note.setCreate_date(current.getCreate_date());
    	   note.setType(current.getType());

    	   pollworkers->getNotes ().getNote().erase(n);
    	   pollworkers->getNotes ().getNote().push_back(note);
		  logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PollworkersWrapper.NoteModified"));
		  break;
       }
    }
}

Note PollworkersWrapper::getNote(std::string customCode)
{
	Note emptyNote ("", "", "", NoteWorkerMemberType::POLLWORKERS_POLLWORKERS);

	for (Notes::NoteIterator
         n (pollworkers->getNotes ().getNote().begin ());
         n != pollworkers->getNotes ().getNote().end ();
         ++n)
    {
       if ( customCode.compare((*n).getCustom_code()) == 0 )
       {
    	   emptyNote = *n;
    	   break;
       }
    }

	return emptyNote;
}

Pollworkers * PollworkersWrapper::getPollworkers()
{
    return pollworkers;
}

Notes & PollworkersWrapper::getNotes()
{
	return pollworkers->getNotes();
}

void PollworkersWrapper::Dispose ()
{
    if (pollworkers != NULL)
    {
        delete pollworkers;
        pollworkers = NULL;
    }
}

unsigned int PollworkersWrapper::getCount(WorkerMemberType type)
{
	unsigned int count = 0;

	Workers::WorkerIterator it;

	for ( it = pollworkers->getWorkers().getWorker().begin();
			it != pollworkers->getWorkers().getWorker().end();
		 ++it)
	{
		if (type == (*it).getMember_type())
		{
			count++;
		}
	}

	return count;
}
