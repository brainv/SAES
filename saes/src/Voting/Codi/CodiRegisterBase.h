/*
 * CodiRegisterBase.h
 *
 *  Created on: Feb 16, 2012
 *      Author: Marcel Cordoví
 */

#ifndef CODIREGISTERBASE_H_
#define CODIREGISTERBASE_H_

#include <string>


namespace Smartmatic
{
namespace SAES
{
namespace Voting
{
namespace Codi
{

class CodiRegisterBase
{
public:

	CodiRegisterBase(const std::string& contestCode, const std::string & customCode, const std::string& contestClassCode);

	virtual ~CodiRegisterBase();


	std::string getContestClassCode() const;
    std::string getContestCode() const;
    std::string getCustomCode() const;

protected:

    void setContestClassCode(std::string contestClassCode);
    void setContestCode(std::string contestCode);
    void setCustomCode(std::string customCode);

protected:

    std::string contest_code;
    std::string contest_class_code;
    std::string customCode;
};

} /* namespace Vote */
} /* namespace Voting */
} /* namespace SAES */
} /* namespace Smartmatic */
#endif /* CODIREGISTERBASE_H_ */
