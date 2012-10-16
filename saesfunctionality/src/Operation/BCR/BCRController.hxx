/**
 * @file BCRController.hxx
 * @brief Header class BCRController
 * @date 09/02/2012
 * @author Yadickson Soto
 */

#ifndef BCRCONTROLLER_HXX_
#define BCRCONTROLLER_HXX_

#include <iostream>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Operation
		{
			namespace BCR
			{
				/**
				 * @class BCRController
				 * @brief Class BCR Controller
				 * @date 09/02/2012
				 * @author Yadickson Soto
				 */
				class BCRController
				{
				private:
					/**
					 * @brief Class constructor
					 * @date 09/02/2012
					 * @author Yadickson Soto
					 */
					BCRController();

					static BCRController * instance; ///< Instance

				public:
					/**
					 * @brief Class destroy
					 * @date 09/02/2012
					 * @author Yadickson Soto
					 */
					virtual ~BCRController();

					/**
					 * @brief Method getter instance class
					 * @return instance class
					 * @date 09/02/2012
					 * @author Yadickson Soto
					 */
					static BCRController * getInstance();
				};

			}
		}
	}
}
#endif /* BCRCONTROLLER_HXX_ */
