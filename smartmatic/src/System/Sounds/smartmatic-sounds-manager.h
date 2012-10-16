/**
 * @file	sounds-manager.h
 *
 * @brief	Header file to the  sounds manager class.
 */

#include "System/Sounds/beep-descriptor.h"
#include "System/Sounds/beep-manager.h"
#include <Configuration/SmartmaticConfiguration-schema.hxx>
#include <Configuration/smartmatic-conf-manager.h>

#ifndef _SMTT_SOUNDS_MANAGER_H_
#define _SMTT_SOUNDS_MANAGER_H_

namespace Smartmatic
{
	namespace System		
	{
		namespace Sounds
		{
			/**
			 * @brief	Manager for smtt sounds class. 
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			class SMTTSoundsManager
			{
			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 */

				SMTTSoundsManager();

				/**
				 * @brief	Gets the current SMTT Sounds Manager.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @return	null if it fails, else.
				 */

				static SMTTSoundsManager* Current();

				/**
				 * @brief	Sounds.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	sound	The sound.
				 */

				void Sound(std::string sound);
			protected:

				
				static SMTTSoundsManager* singleton_instance; ///< The singleton instance

				
				Smartmatic::System::Sounds::BeepManager beepManager; ///< Manager for beep

			private:

				

			};
		}
	}
}

#endif // _SMTT_SOUNDS_MANAGER_H_
