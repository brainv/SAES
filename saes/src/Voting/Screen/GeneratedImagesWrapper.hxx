/*
 * GeneratedImagesWrapper.hxx
 *
 *  Created on: Jul 21, 2011
 *      Author: Juan.Delgado
 */

#ifndef __GENERATED_IMAGES_WRAPPER_H__
#define __GENERATED_IMAGES_WRAPPER_H__

#include <Voting/Screen/generated-images-schema.hxx>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace Voting
		{
			namespace Screen
			{
				/**
				* @brief	Generated images wrapper.
				*
				* @author	Juan.Delgado
				* @date	15/07/2011
				*/

				class GeneratedImagesWrapper
				{
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Juan.Delgado
					 * @date	15/07/2011
					 */

					GeneratedImagesWrapper();

					/**
					 * @brief	Destructor.
					 *
					 * @author	Juan.Delgado
					 * @date	15/07/2011
					 */

					virtual ~GeneratedImagesWrapper();

					/**
					 * @brief	Destructor.
					 *
					 * @author	Juan.Delgado
					 * @date	15/07/2011
					 *
					 * @return GeneratedImagesInstance
					 */
					GeneratedImages & getGeneratedImages();


					/**
					 * @brief	Persists.
					 *
					 * @author	Juan.Delgado
					 * @date	15/07/2011
					 *
					 * @param	folder Folder name
					 */

					void Persist(std::string folder)
                        throw (Smartmatic::System::Exception::CryptoException,
                                 Smartmatic::System::Exception::SignedException,
                                 Smartmatic::System::Exception::XmlException);

				private:

					GeneratedImages generatedImages;	///The generated images instance
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /*__GENERATED_IMAGES_WRAPPER_H__*/
