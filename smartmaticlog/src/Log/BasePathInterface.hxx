/**
 * @file BasePathInterface.hxx
 * @brief Header file of class BasePathInterface
 *
 * @author Yadickson Soto
 * @date 18/07/2011
 */

#ifndef BASEPATHINTERFACE_HXX_
#define BASEPATHINTERFACE_HXX_

#include <Log/LogInterface.hxx>

namespace Smartmatic
{
	namespace Log
	{
		/**
		 * @class BasePathInterface
		 * @brief Base class for path file from log
		 *
		 * @see LogInterface
		 *
		 * @author	Yadickson Soto
		 * @date	18/07/2011
		 */
		class BasePathInterface : public LogInterface
		{
			public:
				/**
				 * @brief	Constructor class.
				 * @param 	code code base path.
				 *
				 * @author	Yadickson Soto
				 * @date	18/07/2011
				 *
				 */
				BasePathInterface (std::string code);
				/**
				 * @brief	Destroy.
				 *
				 * @author	Yadickson Soto
				 * @date	18/07/2011
				 *
				 */
				virtual ~BasePathInterface();
				/**
				 * @brief	Virtual method for get file full path.
				 * @param 	file file name for log.
				 * @return file full path
				 *
				 * @author	Yadickson Soto
				 * @date	18/07/2011
				 *
				 */
				virtual std::string getFileFullPath( std::string & file ) = 0;
				/**
				 * @brief	Virtual method for get is can write file.
				 * @return 	true is can write log file.
				 *
				 * @author	Yadickson Soto
				 * @date	18/07/2011
				 *
				 */
				virtual bool canWriter() = 0;
		};
	}
}

#endif /* BASEPATHINTERFACE_HXX_ */
