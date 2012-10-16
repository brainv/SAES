/*
 * LogBasePath.hxx
 *
 *  Created on: 25/07/2011
 *      Author: soto
 */

#ifndef LOGBASEPATH_HXX_
#define LOGBASEPATH_HXX_

#include <Log/BasePathInterface.hxx>
#include <Configuration/SaesCommonConfiguration-schema.hxx>
#include <Runtime/Environment/saes-directories.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Log
		{
			class LogBasePath : public Smartmatic::Log::BasePathInterface
			{
				public:
					LogBasePath ( Smartmatic::SAES::Common::Configuration::BasePathType type );

					std::string getFileFullPath( std::string & file );
					bool canWriter();

				private:
					Smartmatic::SAES::Common::Configuration::BasePathType type;
					Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
			};
		}
	}
}

#endif /* LOGBASEPATH_HXX_ */
