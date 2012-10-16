/**
 * @file VotingDeviceWrapper.cxx
 * @brief Body class VotingDevice
 */

#include "VotingDeviceWrapper.hxx"
#include <stdio.h>
#include <ctype.h>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <glibmm.h>

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

using namespace Smartmatic::Log;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Voting::VotingDevice;

#define LOGGER_PROJECT "Smartmatic.SAES.Voting.VotingDevice.VotingDeviceWrapper" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* VotingDeviceWrapper::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE);
#else
ISMTTLog* VotingDeviceWrapper::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,"");
#endif

VotingDeviceWrapper::VotingDeviceWrapper(Voting_devices & votingDevices)
{
    this->votingDevices = votingDevices;
}

VotingDeviceWrapper::~VotingDeviceWrapper()
{
}

Voting_devices & VotingDeviceWrapper::getVotingDevices ()
{
    return votingDevices;
}

Voting_device & VotingDeviceWrapper::getFirstVotingDevice() throw (VotingDeviceException)
{
    for (Voting_devices::Voting_deviceIterator
         v (getVotingDevices().getVoting_device ().begin ());
         v != getVotingDevices().getVoting_device ().end ();
         ++v)
    {
       return *v;
    }

    throw VotingDeviceException( _("Smartmatic.SAES.Voting.VotingDevice.VotingDeviceWrapper.FirstVotingDeviceNotFound"),
                                N_("Smartmatic.SAES.Voting.VotingDevice.VotingDeviceWrapper.FirstVotingDeviceNotFound"),
                                logger);
}

Voting_device & VotingDeviceWrapper::getVotingDevice( std::string codeVotingDevice ) throw (VotingDeviceException)
{
    for (Voting_devices::Voting_deviceIterator
         v (getVotingDevices().getVoting_device ().begin ());
         v != getVotingDevices().getVoting_device ().end ();
         ++v)
    {
       if ( codeVotingDevice == (*v).getCode() )
       {
          return *v;
       }
    }

    char text[100];
    sprintf( text, "Voting device with code %s not found.", codeVotingDevice.c_str() );
	logger->Debug(text);
    throw VotingDeviceException( _("Smartmatic.SAES.Voting.VotingDevice.VotingDeviceWrapper.VotingDeviceCodeNotFound")
    		, N_("Smartmatic.SAES.Voting.VotingDevice.VotingDeviceWrapper.VotingDeviceCodeNotFound"),
    		logger);
}

Operation_modes & VotingDeviceWrapper::getOperationModes ( Voting_device & votingDevice )
{
    return votingDevice.getOperation_modes();
}

Voting_booths & VotingDeviceWrapper::getVotingBooths ()
throw (VotingDeviceException)
{
    return getFirstVotingDevice().getVoting_booths();
}

Voting_booths & VotingDeviceWrapper::getVotingBooths ( Voting_device & votingDevice )
{
    return votingDevice.getVoting_booths();
}

Logical_voter_groups & VotingDeviceWrapper::getLogicalVoterGroups()
throw (VotingDeviceException)
{
    return getFirstVotingDevice().getLogical_voter_groups();
}

Logical_voter_groups & VotingDeviceWrapper::getLogicalVoterGroups( Voting_device & votingDevice )
{
    return votingDevice.getLogical_voter_groups();
}

Logical_voter_group & VotingDeviceWrapper::getLogicalVoterGroup(Voting_device & votingDevice, std::string codeLVG )
    throw (VotingDeviceException)
{
	Logical_voter_groups & logicalVoterGroups ( getLogicalVoterGroups ( votingDevice ) );

	for (Logical_voter_groups::Logical_voter_groupIterator
		 v (logicalVoterGroups.getLogical_voter_group().begin ());
		 v != logicalVoterGroups.getLogical_voter_group().end ();
		 ++v)
	{
	   if ( (*v).getCode() == codeLVG )
	   {
		  return *v;
	   }
	}

	char text[100];
	sprintf( text, "Logical Voting Group with code %s not found.", codeLVG.c_str() );
	logger->Debug(text);
	throw VotingDeviceException( _("Smartmatic.SAES.Voting.VotingDevice.VotingDeviceWrapper.LogicalVotingGroupCodeNotFound"),
			N_("Smartmatic.SAES.Voting.VotingDevice.VotingDeviceWrapper.LogicalVotingGroupCodeNotFound"),
			logger);
}

Logical_voter_group & VotingDeviceWrapper::getLogicalVoterGroup( std::string codeLVG )
    throw (VotingDeviceException)
{
	return getLogicalVoterGroup( getFirstVotingDevice(), codeLVG );
}

Logical_voter_group & VotingDeviceWrapper::getLogicalVoterGroupByContestGroupCode( std::string contestGroupCode )
	throw (VotingDeviceException)
{
    for (Voting_devices::Voting_deviceIterator
         vd (getVotingDevices().getVoting_device ().begin ());
         vd != getVotingDevices().getVoting_device ().end ();
         ++vd)
    {

    	Logical_voter_groups & voterGroups ( getLogicalVoterGroups ( *vd ) );
    	for (Logical_voter_groups::Logical_voter_groupIterator
			 v (voterGroups.getLogical_voter_group().begin ());
			 v != voterGroups.getLogical_voter_group().end ();
			 ++v)
		{
		   if ( (*v).getContest_group_code() == contestGroupCode )
		   {
			  return *v;
		   }
		}
    }

	char text[100];
	sprintf( text, "Logical Voting Group with contest group code %s not found.", contestGroupCode.c_str() );
	logger->Debug(text);
	throw VotingDeviceException(_("Smartmatic.SAES.Voting.VotingDevice.VotingDeviceWrapper.LogicalVotingGroupByContestGroupCodeNotFound"),
			N_("Smartmatic.SAES.Voting.VotingDevice.VotingDeviceWrapper.LogicalVotingGroupByContestGroupCodeNotFound"),
			logger);
}

Tally_reports & VotingDeviceWrapper::getTallyReports( Voting_device & votingDevice )
{
    return votingDevice.getTally_reports();
}

std::list < Custom_attribute_definition > VotingDeviceWrapper::getCustomAttributeDefinitionList( Machine_type machineType )
throw (VotingDeviceException)
{
	return getCustomAttributeDefinitionList ( getFirstVotingDevice(), machineType );
}

std::list < Custom_attribute_definition > VotingDeviceWrapper::getCustomAttributeDefinitionList( Voting_device & votingDevice , Machine_type machineType )
{
    std::list < Custom_attribute_definition > list;

    Logical_voter_groups & logicalVoterGroups ( getLogicalVoterGroups( votingDevice ) );

    if (logicalVoterGroups.getCustom_attribute_definitions() != NULL)
    {
        Custom_attribute_definitions & customAttributeDefinitions ( logicalVoterGroups.getCustom_attribute_definitions().get() );

        for (Custom_attribute_definitions::Custom_attribute_definitionIterator
             c (customAttributeDefinitions.getCustom_attribute_definition ().begin ());
             c != customAttributeDefinitions.getCustom_attribute_definition ().end ();
             ++c)
        {
           if ( (*c).getMachine_type() == machineType )
           {
              list.push_back( *c );
           }
        }
    }

    return list;
}

std::list < Custom_attribute > VotingDeviceWrapper::getCustomAttributeListFromLVGCode(std::string lvgCode)
throw (VotingDeviceException)
{
	Voting_device & votingDevice = getFirstVotingDevice();

	Logical_voter_group & lvg = getLogicalVoterGroup( votingDevice, lvgCode );

	return getCustomAttributeList(lvg);
}


std::list < Custom_attribute > VotingDeviceWrapper::getCustomAttributeList(Logical_voter_group & lvg)
{
    std::list < Custom_attribute > list;

    if ( lvg.getCustom_attributes() == NULL )
    {
        return list;
    }
   
    Custom_attributes & customAttributes ( lvg.getCustom_attributes().get() );

    for (Custom_attributes::Custom_attributeIterator
         c (customAttributes.getCustom_attribute().begin ());
         c != customAttributes.getCustom_attribute().end ();
         ++c)
    {
       list.push_back( *c );
    }

    return list;
}

void VotingDeviceWrapper::getLogicalVoterGroupList( Voting_device & votingDevice, std::list < Logical_voter_group > & list )
{
    list.clear();

    Logical_voter_groups & logicalVoterGroups ( getLogicalVoterGroups( votingDevice ) );

    for (Logical_voter_groups::Logical_voter_groupIterator
         l (logicalVoterGroups.getLogical_voter_group ().begin ());
         l != logicalVoterGroups.getLogical_voter_group ().end ();
         ++l)
    {
       list.push_back( *l );
    }
}

bool VotingDeviceWrapper::IsLogicalVoterGroupPresent(std::string lvgCode)
{
	for (Voting_devices::Voting_deviceIterator
	         v (getVotingDevices().getVoting_device ().begin ());
	         v != getVotingDevices().getVoting_device ().end ();
	         ++v)
	 {
	       Logical_voter_groups& lvgs = v->getLogical_voter_groups();

	       for (Logical_voter_groups::Logical_voter_groupIterator
	                l (lvgs.getLogical_voter_group ().begin ());
	                l != lvgs.getLogical_voter_group ().end ();
	                ++l)
	           {
	              if(l->getCode() == lvgCode )
	              {
	            	  return true;
	              }
	           }
	 }
	return false;
}


bool VotingDeviceWrapper::GetCustomAttributeDefinition(std::string caCode,Custom_attribute_definition& customAttrDef )
{
	try
	{
	for (Voting_devices::Voting_deviceIterator
	         v (getVotingDevices().getVoting_device ().begin ());
	         v != getVotingDevices().getVoting_device ().end ();
	         ++v)
	    {

	    if (v->getLogical_voter_groups().getCustom_attribute_definitions() != NULL)
	    {
            Custom_attribute_definitions & customAttributeDefinitions(v->getLogical_voter_groups().getCustom_attribute_definitions().get());

             for (Custom_attribute_definitions::Custom_attribute_definitionIterator
                     c (customAttributeDefinitions.getCustom_attribute_definition ().begin ());
                     c != customAttributeDefinitions.getCustom_attribute_definition ().end ();
                     ++c)
                {
                   if ( c->getCode() == caCode)
                   {
                       customAttrDef =  *c;
                       return true;
                   }
                }
            }
	    }
	}
	catch(...)
	{
		//catch any exception from autogenerated code and return false
	}
	return false;
}

bool VotingDeviceWrapper::IsLanguagesPresent ()
{
	return getVotingDevices ().getLanguages ().present ();
}

void VotingDeviceWrapper::setLanguages (Smartmatic::SAES::Voting::Election::Languages & lang)
{
	getVotingDevices ().getLanguages ().set (lang);
}

Smartmatic::SAES::Voting::Election::Languages & VotingDeviceWrapper::getLanguages ()
{
	return getVotingDevices ().getLanguages ().get ();
}

void VotingDeviceWrapper::getRegionCategoryList(std::list <Region_category> & list)
throw (VotingDeviceException)
{
	list.clear();

	Voting_booths::Voting_boothSequence vbseq = getFirstVotingDevice().getVoting_booths().getVoting_booth();

	if (vbseq.size() > 0)
	{
		Voting_booth vb = (*(vbseq.begin()));
		Region_hierarchies::Region_hierarchySequence shseq = vb.getRegion_hierarchies().getRegion_hierarchy();

		bool force = shseq.size() == 1;

		if (shseq.size() > 0)
		{
		    Region_hierarchies::Region_hierarchyIterator iter;

		    for(iter = shseq.begin(); iter != shseq.end(); iter++)
		    {
		    	Region_hierarchy rh = (*iter);

		    	if (rh.getIs_default() || force)
		    	{
			    	Region_category categoryOptional = rh.getCategory();
		    		list.push_back(categoryOptional);

					while (categoryOptional.getCategory().present())
					{
						Region_category temp = categoryOptional.getCategory().get();
						categoryOptional = temp;
						list.push_back(categoryOptional);
					}

		    		break;
		    	}
		    }
		}
	}
}
