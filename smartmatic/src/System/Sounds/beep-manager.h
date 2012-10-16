/**
 * @file	beep-manager.h
 *
 * @brief	Header file to the beep manager class.
 */

#include <map>
#include <vector>
#include <stdlib.h>
#include "System/Sounds/beep-descriptor.h"

#ifndef _BEEP_DESCRIPTOR_H_
#define _BEEP_DESCRIPTOR_H_

namespace Smartmatic
{
	namespace System		
	{
		namespace Sounds
		{
			/**
			 * @brief	Manager for beeps class. 
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			class BeepManager
			{
			public:

			/**
			 * @brief	Adds a beep.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @param	frequency			  	The frequency.
			 * @param	time				  	The time.
			 * @param	repetitions			  	The repetitions.
			 * @param	timeBetweenRepetitions	The time between repetitions.
			 */

			void AddBeep(int frequency, int time, int repetitions, int timeBetweenRepetitions);

			/**
			 * @brief	Adds a beep. 
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @param	beepDescriptor	The beep descriptor.
			 */

			void AddBeep(BeepDescriptor beepDescriptor);

			/**
			 * @brief	Beeps this object.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			void Beep();

			/**
			 * @brief	Clears this object to its blank/initial state.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			void Clear(); 


			protected:

			private:

			
			std::vector<BeepDescriptor> beeps; ///< The beeps

			};
		}
	}
}

#endif // _BEEP_DESCRIPTOR_H_
