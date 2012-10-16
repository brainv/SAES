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
#include "Voting/PBReports/closing-notes-wrapper.h"
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
using namespace std;

ISMTTLog* ClosingNotesWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper",GETTEXT_PACKAGE);

ClosingNotesWrapper::ClosingNotesWrapper()
{
	closingNotes = NULL;
}

ClosingNotesWrapper::~ClosingNotesWrapper()
{
}

void ClosingNotesWrapper::Persist()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    Smartmatic::SAES::Voting::PBReports::NamespaceInfomap map;
    map[""].name = NAMESPACE_PBREPORTS;
    map[""].schema = "";

    std::ostringstream os;
    serializeCloseElectionNotes(os,*closingNotes, map, "UTF-8");

    std::string data = os.str();

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getClosingNotesFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getClosingNotesFileFullPath(BasePathType::CONFIGURATION_FLASH);

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

bool ClosingNotesWrapper::Load(std::string xmlFile)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    bool loadFile = false;

    if (!Smartmatic::System::IO::File::canOpenFile( xmlFile ))
    {
        closingNotes = new CloseElectionNotes();
        CloseNotes notes;
        closingNotes->setCloseNotes(notes);
    }
    else
    {
        try
        {
        	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(xmlFile, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
            std::istringstream istr (data);
            closingNotes = new CloseElectionNotes(*(parseCloseElectionNotes(istr,Smartmatic::SAES::Voting::PBReports::Flags::dont_validate)));
            logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper.ClosingNotesLoadedSuccessfully"));
            loadFile = true;
        }
        catch (const ::xsd::cxx::tree::exception< char >& e)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__ << " " << e;
            logger->Debug(ss.str());
            logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper.ErrorLoadingCloseNotes"));
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper.ErrorParseFile"), logger);
        }
        catch(...)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__;
            logger->Debug(ss.str());
            logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper.ErrorLoadingCloseNotes"));
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper.ErrorParseFile"), logger);
        }
    }
    return loadFile;
}

bool ClosingNotesWrapper::init ()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Dispose();
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    return Load(directories.getClosingNotesFileFullPath());
}

void ClosingNotesWrapper::AddNote(CloseNote &note)
{
	GuidClass guidC = GuidClass::NewGuid();
	note.setCustom_code((std::string)guidC.ToString());

	Glib::TimeVal time;
	time.assign_current_time();
	std::string now = time.as_iso8601();

	note.setCreate_date(now);

	closingNotes->getCloseNotes().getCloseNote().push_back (note);
	logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper.NoteAdded"));
}

void ClosingNotesWrapper::RemoveNote(CloseNote note)
{
	for (CloseNotes::CloseNoteIterator
         p (closingNotes->getCloseNotes ().getCloseNote().begin ());
         p != closingNotes->getCloseNotes ().getCloseNote().end ();
         ++p)
    {
       if (note.getCustom_code().compare((*p).getCustom_code())== 0)
       {
          closingNotes->getCloseNotes ().getCloseNote().erase(p);
          logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper.NoteRemoved"));
		  break;
       }
    }
}

bool ClosingNotesWrapper::modifyNote(CloseNote & note)
{
	bool modify = false;
	
	for (CloseNotes::CloseNoteIterator
         p (closingNotes->getCloseNotes ().getCloseNote().begin ());
         p != closingNotes->getCloseNotes ().getCloseNote().end ();
         ++p)
    {
       if ( note.getCustom_code().compare((*p).getCustom_code()) == 0 )
       {
    	   note.setCreate_date((*p).getCreate_date());
    	   (*p) = note;
    	   logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.ClosingNotesWrapper.NoteModified"));
    	   modify = true;
    	   break;
       }
    }

	if (!modify)
	{
		AddNote(note);
	}

	return modify;
}

CloseNote ClosingNotesWrapper::getNote(std::string customCode)
{
	for (CloseNotes::CloseNoteIterator
         p (closingNotes->getCloseNotes ().getCloseNote().begin ());
         p != closingNotes->getCloseNotes ().getCloseNote().end ();
         ++p)
    {
       if ( customCode.compare((*p).getCustom_code()) == 0 )
       {
          return *p;
       }
    }
	CloseNote dummyNote;
	return dummyNote;
}

CloseNotes ClosingNotesWrapper::getNotes()
{
	return closingNotes->getCloseNotes();
}

CloseElectionNotes * ClosingNotesWrapper::getCloseElectionNotes()
{
    return closingNotes;
}

void ClosingNotesWrapper::Dispose ()
{
    if (closingNotes != NULL)
    {
        delete closingNotes;
        closingNotes = NULL;
    }
}
