/**
 * @file StateListener.hxx
 * @brief Header class memory state listener
 * @date 19/04/2012
 * @author Yadickson Soto
 */

#ifndef STATELISTENER_HXX_
#define STATELISTENER_HXX_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class StateListener
			 * @brief class memory state listener
			 * @date 19/04/2012
			 * @author Yadickson Soto
			 */
			class StateListener
			{
			public:
				/**
				 * @brief class constructor
				 * @date 19/04/2012
				 * @author Yadickson Soto
				 */
				StateListener();
				/**
				 * @brief class destroy
				 * @date 19/04/2012
				 * @author Yadickson Soto
				 */
				virtual ~StateListener();
				/**
				 * @brief method block
				 * @date 19/04/2012
				 * @author Yadickson Soto
				 */
				virtual void block() = 0;
				/**
				 * @brief method partial
				 * @date 19/04/2012
				 * @author Yadickson Soto
				 */
				virtual void partial() = 0;
				/**
				 * @brief method resume
				 * @date 19/04/2012
				 * @author Yadickson Soto
				 */
				virtual void resume() = 0;
			};
		}
	}
}
#endif /* STATELISTENER_HXX_ */
