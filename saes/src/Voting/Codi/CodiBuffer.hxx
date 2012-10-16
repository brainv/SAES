/**
 * @file CodiBuffer.hxx
 * @brief Header class codi buffer utility
 * @date 28/02/2012
 * @author Yadickson Soto
 */

#ifndef CODIBUFFER_HXX_
#define CODIBUFFER_HXX_

#include <System/SafeBuffer.h>
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
				 * @class CodiBuffer
				 * @brief Class codi buffer utility
				 * @date 28/02/2012
				 * @author Yadickson Soto
				 */
				class CodiBuffer
				{
				protected:
					/**
					 * @brief Class constructor
					 * @date 28/02/2012
					 * @author Yadickson Soto
					 */
					CodiBuffer();

				public:

					enum RegisterType
					{
						  REGISTER_G ///< type register G
						, REGISTER_S ///< type register S
						, REGISTER_L ///< type register L
						, REGISTER_C ///< type register C
						, REGISTER_H ///< type register H
						, REGISTER_T ///< type register T
						, NONE ///< type register unknown
					}; ///< register type

					/**
					 * @brief Class destroy
					 * @date 28/02/2012
					 * @author Yadickson Soto
					 */
					virtual ~CodiBuffer();

					/**
					 * @brief method insert value in buffer
					 * @param buffer buffer
					 * @param pos position insert value
					 * @param value numeric value
					 * @author Yadickson Soto
					 * @date 27/02/2012
					 */
					static void insertValue(Smartmatic::System::SafeBuffer & buffer, unsigned long pos, unsigned long value);

					/**
					 * @brief method insert value in buffer
					 * @param buffer buffer
					 * @param pos position insert value
					 * @param value string value
					 * @author Yadickson Soto
					 * @date 27/02/2012
					 */
					static void insertValue(Smartmatic::System::SafeBuffer & buffer, unsigned long pos, std::string value);

					/**
					 * @brief method create register by type
					 * @param buffer buffer
					 * @param type type register
					 * @author Yadickson Soto
					 * @date 28/02/2012
					 */
					static void createRegister(Smartmatic::System::SafeBuffer & buffer, RegisterType type);

					/**
					 * @brief method fix size element in buffer
					 * @param buffer buffer
					 * @param size final size element
					 * @author Yadickson Soto
					 * @date 27/02/2012
					 */
					static void fixRegister(Smartmatic::System::SafeBuffer & buffer, unsigned long size);

					/**
					 * @brief method add end register CR + LF
					 * @param buffer buffer
					 * @author Yadickson Soto
					 * @date 27/02/2012
					 */
					static void addEndRegister(Smartmatic::System::SafeBuffer & buffer);

					/**
					 * @brief method getter position register in buffer
					 * @param buffer buffer
					 * @param pos position of register
					 * @param begin result begin position
					 * @param end result end position
					 * @return true position found
					 * @author Yadickson Soto
					 * @date 27/02/2012
					 */
					static bool getPositionRegister(Smartmatic::System::SafeBuffer & buffer, unsigned long pos, unsigned long & begin, unsigned long & end);

					/**
					 * @brief method getter string value position register in buffer
					 * @param buffer buffer
					 * @param pos position of register
					 * @return string value
					 * @author Yadickson Soto
					 * @date 28/02/2012
					 */
					static std::string getStringValue(Smartmatic::System::SafeBuffer & buffer, unsigned long pos);

					/**
					 * @brief method getter long value position register in buffer
					 * @param buffer buffer
					 * @param pos position of register
					 * @return long value
					 * @author Yadickson Soto
					 * @date 28/02/2012
					 */
					static unsigned long getLongValue(Smartmatic::System::SafeBuffer & buffer, unsigned long pos);

					/**
					 * @brief method getter list register of buffer
					 * @param buffer input buffer
					 * @param regG result list register G
					 * @param regS result list register S
					 * @param regL result list register L
					 * @param regC result list register C
					 * @author Yadickson Soto
					 * @date 27/02/2012
					 */
					static void getRegisters(Smartmatic::System::SafeBuffer & buffer,
							std::vector <Smartmatic::System::SafeBuffer> & regG,
							std::vector <Smartmatic::System::SafeBuffer> & regS,
							std::vector <Smartmatic::System::SafeBuffer> & regL,
							std::vector <Smartmatic::System::SafeBuffer> & regH);

					/**
					 * @brief method getter register type
					 * @param buffer input buffer
					 * @return register type
					 * @author Yadickson Soto
					 * @date 28/02/2012
					 */
					static RegisterType getRegisterType(Smartmatic::System::SafeBuffer & buffer);

				private:

					/**
					 * @brief method add register to list
					 * @param buffer input buffer
					 * @param regG result list register G
					 * @param regS result list register S
					 * @param regL result list register L
					 * @param regC result list register C
					 * @author Yadickson Soto
					 * @date 27/02/2012
					 */
					static void addToList(Smartmatic::System::SafeBuffer & buffer,
							std::vector <Smartmatic::System::SafeBuffer> & regG,
							std::vector <Smartmatic::System::SafeBuffer> & regS,
							std::vector <Smartmatic::System::SafeBuffer> & regL,
							std::vector <Smartmatic::System::SafeBuffer> & regH);
				};
			}
		}
	}
}

#endif /* CODIBUFFER_HXX_ */
