/*
 * CodiFormatUtillity.h
 *
 *  Created on: Feb 11, 2012
 *      Author: Marcel Cordoví
 */

#ifndef CODIFORMATUTILLITY_H_
#define CODIFORMATUTILLITY_H_

#include <vector>

namespace Smartmatic
{
namespace SAES
{
namespace Voting
{
namespace Codi
{

class CodiFormatUtility
{
public:

	CodiFormatUtility();

	virtual ~CodiFormatUtility();

	static long CodiCheckSum (std::vector<unsigned long> countArray);
};

} /* namespace Vote */
} /* namespace Voting */
} /* namespace SAES */
} /* namespace Smartmatic */
#endif /* CODIFORMATUTILLITY_H_ */
