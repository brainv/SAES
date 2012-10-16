/**
 * @file BCRController.cxx
 * @brief Body class BCRController
 * @date 09/02/2012
 * @author Yadickson Soto
 */

#include "BCRController.hxx"

using namespace Smartmatic::SAES::Operation::BCR;

BCRController * BCRController::instance = NULL;

BCRController::BCRController()
{

}

BCRController::~BCRController()
{

}

BCRController * BCRController::getInstance()
{
	if (!instance)
	{
		instance = new BCRController();
	}

	return instance;
}
