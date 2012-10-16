/**
 * @file	descriptor.h
 *
 * @brief	Header file to the beep descriptor class.
 */

#ifndef _BEEP_DESCRIPTOR2_H_
#define _BEEP_DESCRIPTOR2_H_

#include <sstream>
#include <iostream>

namespace Smartmatic
{
	namespace System		
	{
		namespace Sounds
		{
			/**
			 * @brief	Beep descriptor class. 
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			class BeepDescriptor
			{
			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 */

				BeepDescriptor();

				/**
				 * @brief	Default constructor.
				 * @param   soundFile sound file
				 * @author	Yadickson Soto
				 * @date	19/07/2012
				 */

				BeepDescriptor(std::string soundFile);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	frequency			  	The frequency of beep sound.
				 * @param	time				  	The time of beep sound.
				 * @param	repetitions			  	The repetitions.
				 * @param	timeBetweenRepetitions	The time between beep sound repetitions.
				 */

				BeepDescriptor(int frequency, int time, int repetitions, int timeBetweenRepetitions);

				/**
				 * @brief	Gets the beep line.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @return	The beep line.
				 */

				std::string GetBeepLine();

			protected:

			private:

				
				int frequency; ///< The frequency
				
				int time; ///< The time
				
				int repetitions; ///< The repetitions
				
				int timeBetweenRepetitions;	///< The time between repetitions

				std::string soundFile; ///< sound file
			};
		}
	}
}
		

#endif // _BEEP_DESCRIPTOR2_H_
