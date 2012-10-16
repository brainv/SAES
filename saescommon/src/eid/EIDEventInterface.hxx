/*
 * EIDEventInterface.hxx
 *
 *  Created on: 22/07/2011
 *      Author: soto
 */

#ifndef EIDEVENTINTERFACE_HXX_
#define EIDEVENTINTERFACE_HXX_

#include <iostream>

namespace Smartmatic
{
	namespace SAES
	{
		namespace EID
		{
			class EIDEventInterface
			{
			public:
				EIDEventInterface(){}
				virtual ~EIDEventInterface(){}
				virtual void cardInserted() = 0;
				virtual void cardExtracted() = 0;
			};
		}
	}
}

#endif /* EIDEVENTINTERFACE_HXX_ */
