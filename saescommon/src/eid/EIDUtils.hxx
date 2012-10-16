/*
 * EIDUtils.hxx
 *
 *  Created on: 20/07/2011
 *      Author: soto
 */

#ifndef EIDUTILS_HXX_
#define EIDUTILS_HXX_

#include <iostream>

namespace Smartmatic
{
	namespace SAES
	{
		namespace EID
		{
			class EIDUtils
			{
			protected:
				EIDUtils();

			public:
				~EIDUtils();

				static std::string utf8ToAnsi(const char* pUtf8);
			};
		}
	}
}

#endif /* EIDUTILS_HXX_ */
