/*
 * PCSCDManager.hxx
 *
 *  Created on: 16/08/2011
 *      Author: soto
 */

#ifndef PCSCDMANAGER_HXX_
#define PCSCDMANAGER_HXX_

namespace Smartmatic
{
	namespace SAES
	{
		namespace PCSCD
		{
			class PCSCDManager
			{
			public:

				static void start(bool force = false);
				static void stop(bool force = false);
				static void kill();
			};
		}
	}

}

#endif /* PCSCDMANAGER_HXX_ */
