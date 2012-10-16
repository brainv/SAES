/*
 * ContingencyCardReport.h
 *
 *  Created on: Oct 19, 2011
 *      Author: root
 */

#ifndef CONTINGENCYCARDREPORT_H_
#define CONTINGENCYCARDREPORT_H_


#include <Voting/ElectoralConfiguration.hxx>
#include "Printing/DocumentOptions.h"
#include "Printing/BasePrintDocument.h"


namespace Smartmatic
{
namespace SAES
{
namespace Printing
{

class ContingencyCardReport : public Smartmatic::SAES::Printing::BasePrintDocument
{

public:

	ContingencyCardReport(const std::string& pin, Smartmatic::SAES::Voting::ElectoralConfiguration*);

	virtual ~ContingencyCardReport();

protected:

	virtual void PrintDoc();
	virtual void BeginPrint();
	virtual void EndPrint();

	void PrintHeader (
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo);

	void PrintCardInfoSection (
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo);

	void PrintRegionInfo (
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
			Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo);

private:

	static Smartmatic::Log::ISMTTLog* logger; /**<logger*/

	Smartmatic::SAES::Voting::ElectoralConfiguration* m_ElectoralConf;

	std::string m_Pin;

	std::vector<Glib::ustring> GetRegionsStrings(const Smartmatic::SAES::Voting::VotingDevice::Voting_booth & votingBooth);

};

} /* namespace Printing */
} /* namespace SAES */
} /* namespace Smartmatic */
#endif /* CONTINGENCYCARDREPORT_H_ */
