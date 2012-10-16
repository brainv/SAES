/**
 * @file XMLRoffTransformer.h
 * @brief Header class XMLRoffTransformer, xml to pdf runtime
 * @date 28/04/2011
 * @author Yadickson Soto
 */

#ifndef XMLROFFTRANSFORMER_H_
#define XMLROFFTRANSFORMER_H_

#include <iostream>
#include "XSLFOTransformer.h"

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace System
	{
		namespace XSLFO
		{
			/**
			 * @brief	Wrapper class for XSLFO transformer (gets data from an xml, and uses and xsl as stylesheet to generate a pdf)
			 *
			 * @author	marcelm
			 * @date	28/04/2011
			 * @see XSLFOTransformer
			 */

			class XMLRoffTransformer : public XSLFOTransformer
			{

			public:

			  /**
			   * @brief	Default constructor.
			   *
			   * @author	marcelm
			   * @date	28/04/2011
			   */

				XMLRoffTransformer();

			  /**
			   * @brief	Destroy
			   *
			   * @author	marcelm
			   * @date	28/04/2011
			   */

			  virtual ~XMLRoffTransformer();

			/**
			* @enum TransformFormat
			* @brief Type format transformation
			*/
			  enum TransformFormat
			  {
					TRANSFORM_AUTO, ///<auto (default pdf)
					TRANSFORM_PDF, ///<pdf file
					TRANSFORM_POSTSCRIPT, ///< postscript file
					TRANSFORM_SVG ///<svg file
			  };

			/**
			* @enum TransformBackend
			* @brief Type backend transformation
			*/
			  enum TransformBackend
			  {
					TRANSFORM_GP, ///< gp backend
					TRANSFORM_CAIRO ///< cairo backend
			  };

			/**
			* @enum TransformCompat
			* @brief Type compat transformation
			*/
			  enum TransformCompat
			  {
					TRANSFORM_COMPAT, ///< compat
					TRANSFORM_NOCOMPAT ///< no compat
			  };

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
			  virtual bool transformFile(std::string outputFile, std::string inputFile, std::string templateFile);
				/**
				 * @brief Method setter format type
				 * @param format type format transformation
				 * @date 27/10/2011
				 * @author Yadickson Soto
				 */
			  void setFormat(TransformFormat format);
				/**
				 * @brief Method setter backend type
				 * @param backend type backend transformation
				 * @date 27/10/2011
				 * @author Yadickson Soto
				 */
			  void setBackend(TransformBackend backend);
				/**
				 * @brief Method setter compat type
				 * @param compat type compat transformation
				 * @date 27/10/2011
				 * @author Yadickson Soto
				 */
			  void setCompat(TransformCompat compat);

			protected:

			private:

			  TransformFormat format; ///< type format transformation
			  TransformBackend backend; ///< type backend transformation
			  TransformCompat compat; ///< type compat transformation

			  static Smartmatic::Log::ISMTTLog* logger; ///<logger
			};
		}
	}
}

#endif /* XMLROFFTRANSFORMER_H_ */
