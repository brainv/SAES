/**
 * @file  XSLFOTransformer.h
 * @brief	Header class XSLFOTransformer.
 *
 * @author	Yadickson Soto
 * @date	28-04-2011
 *
 */

#ifndef XSLFOTRANSFORMER_H_
#define XSLFOTRANSFORMER_H_

#include <iostream>

namespace Smartmatic
{
	namespace System
	{
		namespace XSLFO
		{
			/**
			 * @class XSLFOTransformer
			 * @brief	Abstract class for xml to pdf transformer.
			 *
			 * @author	Yadickson Soto
			 * @date	15-07-2011
			 *
			 * @see LogInterface
			 *
			 */
			class XSLFOTransformer
			{
			public:

				/**
				 * @brief	Constructor class.
				 *
				 * @author	Yadickson Soto
				 * @date	15-07-2011
				 *
				 */
				XSLFOTransformer(){};
				/**
				 * @brief	Destroy.
				 *
				 * @author	Yadickson Soto
				 * @date	15-07-2011
				 *
				 */
				virtual ~XSLFOTransformer(){};
				/**
				   * @brief	Gets the data.
				   *
				   * @author	marcelm
				   * @date	28/04/2011
				   *
				   * @param	outputFile		The Path of the file that will be generated.
				   * @param	inputFile		The path of the file with the input data.
				   * @param	templateFile	The path of the file with the template sheet.
				   * @return	true if success, false if it fails.
				   */
				virtual bool transformFile(std::string outputFile, std::string inputFile, std::string templateFile) = 0;
			};
		}
	}
}
#endif /* XSLFOTRANSFORMER_H_ */
