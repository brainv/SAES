/**
 * @file CodiInfo.hxx
 * @brief Header class codi info utility
 * @date 28/02/2012
 * @author Yadickson Soto
 */

#ifndef CODIINFO_HXX_
#define CODIINFO_HXX_

#include <string>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Voting
		{
			namespace Codi
			{
				/**
				 * @class CodiInfo
				 * @brief Class codi info utility
				 * @date 28/02/2012
				 * @author Yadickson Soto
				 */
				class CodiInfo
				{
				protected:
					/**
					 * @brief Class constructor
					 * @date 28/02/2012
					 * @author Yadickson Soto
					 */
					CodiInfo();

				public:
					/**
					 * @brief Class destroy
					 * @date 28/02/2012
					 * @author Yadickson Soto
					 */
					virtual ~CodiInfo();

					/**
					 * @brief method getter election type by custom code
					 * @param customCode custom code
					 * @return election type
					 * @date 28/02/2012
					 * @author Yadickson Soto
					 */
					static std::string getElectionType(std::string customCode);

					/**
					 * @brief method getter input NIS code by custom code
					 * @param customCode custom code
					 * @return NIS code
					 * @date 28/02/2012
					 * @author Yadickson Soto
					 */
					static std::string getInputNisCode(std::string customCode);

					/**
					 * @brief method getter output NIS code by custom code
					 * @param electoralConfiguration electoral configuration
					 * @param customCode custom code
					 * @param customniscode custom niscode
					 * @return NIS code
					 * @date 28/02/2012
					 * @author Yadickson Soto
					 */
					static std::string getOutputNisCode(
							std::string customCode,
							std::string customniscode);

					/**
					 * @brief method getter language by custom code
					 * @param customCode custom code
					 * @return language
					 * @date 28/02/2012
					 * @author Yadickson Soto
					 */
					static std::string getLanguage(std::string customCode);
				};
			}
		}
	}
}
#endif /* CODIINFO_HXX_ */
