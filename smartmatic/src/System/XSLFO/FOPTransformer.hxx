/**
 * @file FOPTransformer.hxx
 * @brief Header class FOPTransformer, xml to pdf runtime
 * @date 27/10/2011
 * @author Yadickson Soto
 */

#ifndef FOPTRANSFORMER_HXX_
#define FOPTRANSFORMER_HXX_

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
			 * @class FOPTransformer
			 * @brief Class transformer xml to pdf runtime
			 * @date 27/10/2011
			 * @author Yadickson Soto
			 * @see XSLFOTransformer
			 */
			class FOPTransformer : public XSLFOTransformer
			{
			public:
				/**
				 * @brief Constructor
				 * @date 27/10/2011
				 * @author Yadickson Soto
				 */
				FOPTransformer();
				/**
				 * @brief Destroy
				 * @date 27/10/2011
				 * @author Yadickson Soto
				 */
				virtual ~FOPTransformer();
				/**
				 * @brief Method setter path config file runtine
				 * @param configFile path config file fop runtime
				 * @date 27/10/2011
				 * @author Yadickson Soto
				 */
				static void setConfigFile(std::string configFile);
				/**
				 * @brief Method transformer xml to pdf fop runtine
				 * @param outputFile path output pdf file
				 * @param inputFile path input xml file
				 * @param templateFile path input xlst file
				 * @return true is success transformation
				 * @date 27/10/2011
				 * @author Yadickson Soto
				 */
				virtual bool transformFile(std::string outputFile, std::string inputFile, std::string templateFile);

			private:

				static std::string configFile; ///< path config file fop runtime
				static Smartmatic::Log::ISMTTLog* logger; ///<logger
			};
		}
	}
}

#endif /* FOPTRANSFORMER_HXX_ */
