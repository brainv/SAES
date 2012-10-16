/**
 * @file PoliceNoteWrapper.cxx
 * @brief Body class voting disabled wrapper
 * @date 21/05/2012
 * @author Yadickson Soto
 */

#include "PoliceNoteWrapper.hxx"
#include "System/guid-class.h"
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <Security/Encryption.hxx>
#include <sstream>
#include <Log/SMTTLogManager.h>
#include "Log/ISMTTLog.h"
#include <Runtime/Environment/DirectoryManager.hxx>
#include <Runtime/Environment/saes-directories.h>

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

ISMTTLog* PoliceNoteWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.PBReports.PoliceNoteWrapper",GETTEXT_PACKAGE);

PoliceNoteWrapper::PoliceNoteWrapper()
{
	policeNotes = NULL;
}

PoliceNoteWrapper::~PoliceNoteWrapper()
{
}

void PoliceNoteWrapper::persistence()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    Smartmatic::SAES::Voting::PBReports::NamespaceInfomap map;
    map[""].name = NAMESPACE_PBREPORTS;
    map[""].schema = "";

    std::ostringstream os;
    serializePoliceNotes(os,*policeNotes, map, "UTF-8");

    std::string data = os.str();

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getPoliceNotesFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getPoliceNotesFileFullPath(BasePathType::CONFIGURATION_FLASH);

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

    logger->Audit("Smartmatic.SAES.Voting.PBReports.PoliceNoteWrapper.PersistencePoliceNote");
}

bool PoliceNoteWrapper::load(std::string xmlFile)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    bool loadFile = false;

    if (!Smartmatic::System::IO::File::canOpenFile( xmlFile ))
    {
    	policeNotes = new PoliceNotes();
    	PoliceNotes::PoliceNoteSequence seq;
    	policeNotes->setPoliceNote(seq);
    }
    else
    {
        try
        {
        	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(xmlFile, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
            std::istringstream istr (data);
            policeNotes = new PoliceNotes(*(parsePoliceNotes(istr,Smartmatic::SAES::Voting::PBReports::Flags::dont_validate)));
            loadFile = true;
        }
        catch (const ::xsd::cxx::tree::exception< char >& e)
        {
            std::cerr << "FATAL - " << __func__ << e << std::endl;
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.PoliceNoteWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.PoliceNoteWrapper.ErrorParseFile"), logger);
        }
    }
    return loadFile;
}


bool PoliceNoteWrapper::init ()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    dispose();
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    return load(directories.getPoliceNotesFileFullPath());
}

void PoliceNoteWrapper::addPoliceNote(PoliceNote & policeNote)
{
	GuidClass guidC = GuidClass::NewGuid();
	policeNote.setCustom_code((std::string)guidC.ToString());

	Glib::TimeVal time;
	time.assign_current_time();
	std::string now = time.as_iso8601();

	policeNote.setCreate_date(now);

	policeNotes->getPoliceNote().push_back(policeNote);
	logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PoliceNoteWrapper.AddPoliceNote"));
}

void PoliceNoteWrapper::removePoliceNote(std::string customCode)
{
	for (PoliceNotes::PoliceNoteIterator
         it (policeNotes->getPoliceNote().begin ());
         it != policeNotes->getPoliceNote().end ();
         ++it)
    {
		if ( customCode == (*it).getCustom_code() )
		{
			policeNotes->getPoliceNote().erase(it);
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PoliceNoteWrapper.RemovePoliceNote"));
			break;
		}
    }
}

bool PoliceNoteWrapper::modifyPoliceNote(PoliceNote & policeNote)
{
	bool modify = false;

	for (PoliceNotes::PoliceNoteIterator
         it (policeNotes->getPoliceNote().begin ());
         it != policeNotes->getPoliceNote().end ();
         ++it)
    {
		if ( policeNote.getCustom_code() == (*it).getCustom_code())
		{
			policeNote.setCreate_date((*it).getCreate_date());
			*it = policeNote;
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.PoliceNoteWrapper.ModifyPoliceNote"));
			modify = true;
			break;
		}
    }

	if (!modify)
	{
		addPoliceNote(policeNote);
	}

	return modify;
}

PoliceNote PoliceNoteWrapper::getPoliceNote(std::string customCode)
{
	PoliceNote policeNote;

	for (PoliceNotes::PoliceNoteIterator
         it (policeNotes->getPoliceNote().begin ());
         it != policeNotes->getPoliceNote().end ();
         ++it)
    {
		if ( customCode == (*it).getCustom_code())
		{
			policeNote = *it;
		}
    }

	return policeNote;
}

PoliceNotes PoliceNoteWrapper::getPoliceNotes()
{
	return *policeNotes;
}

void PoliceNoteWrapper::dispose ()
{
	if (policeNotes != NULL)
	{
		delete policeNotes;
		policeNotes = NULL;
	}
}
