/**
 * @file CodiFile.h
 * @brief Header class codi file
 * @date 16/02/2012
 * @author Yadickson Soto
 */

#ifndef CODIFILE_H_
#define CODIFILE_H_

#include "CodiRegisterS.h"
#include "CodiRegisterL.h"
#include "CodiRegisterC.h"
#include <Log/ISMTTLog.h>
#include <vector>

namespace Smartmatic
{
namespace SAES
{
namespace Voting
{
namespace Codi
{

/**
 * @class CodiFile
 * @brief Class codi file
 * @date 16/02/2012
 * @author Yadickson Soto
 */
class CodiFile
{
public:

	/**
	 * @brief Class constructor
	 * @parm file codi file name
	 * @date 16/02/2012
	 * @author Yadickson Soto
	 */
	CodiFile(const std::string & file);

	/**
	 * @brief Class destroy
	 * @date 16/02/2012
	 * @author Yadickson Soto
	 */
	virtual ~CodiFile();

	/**
	 * @brief method insert register S
	 * @param regS register S
	 * @date 16/02/2012
	 * @author Yadickson Soto
	 */
	void insert_S_reg (const CodiRegister_S & regS);

	/**
	 * @brief method insert register L
	 * @param regL register L
	 * @date 16/02/2012
	 * @author Yadickson Soto
	 */
	void insert_L_reg (const CodiRegister_L & regL);

	/**
	 * @brief method insert register C
	 * @param regC register C
	 * @date 16/02/2012
	 * @author Yadickson Soto
	 */
	void insert_C_reg (const CodiRegister_C & regC);

	/**
	 * @brief method calculate checksum
	 * @date 16/02/2012
	 * @author Yadickson Soto
	 */
	void CalculateChecksums ();

	/**
	 * @brief method getter contest class code
	 * @return contest class code
	 * @author Yadickson Soto
	 * @date 24/02/2012
	 */
	std::string getFile() const;

	/**
	 * @brief method getter registers S
	 * @return registers S
	 * @author Yadickson Soto
	 * @date 01/03/2012
	 */
	std::vector<CodiRegister_S> & getRegsS();

	/**
	 * @brief method getter registers L
	 * @return registers L
	 * @author Yadickson Soto
	 * @date 01/03/2012
	 */
	std::vector<CodiRegister_L> & getRegsL();

	/**
	 * @brief method getter registers C
	 * @return registers C
	 * @author Yadickson Soto
	 * @date 01/03/2012
	 */
	std::vector<CodiRegister_C> & getRegsC();

private:

	std::string file; ///< code file
	std::vector<CodiRegister_S> regs_S; ///< vector register S
	std::vector<CodiRegister_L> regs_L; ///< vector register L
	std::vector<CodiRegister_C> regs_C; ///< vector register C
    static Smartmatic::Log::ISMTTLog* logger; ///< logger
};

} /* namespace Vote */
} /* namespace Voting */
} /* namespace SAES */
} /* namespace Smartmatic */
#endif /* CODIFILE_H_ */
