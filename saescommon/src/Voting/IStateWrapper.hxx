/**
 * @file	IStateWrapper.hxx
 *
 * @brief	Declares the IStateWrapper interface.
 */

#ifndef __STATE_WRAPPER_H__
#define __STATE_WRAPPER_H__

#include "IStateWrapper.hxx"

namespace Smartmatic
{
   namespace SAES
   {
      namespace Voting
      {
        /**
         * @class	IStateWrapper
         *
         * @brief	Header class IStateWrapper.
         *
         * @author	Yadickson Soto &lt;yadickson.soto@smartmatic.com&gt;
         * @date	08-03-2011
         */

        class IStateWrapper
        {
        public:

        	IStateWrapper();

        	virtual ~IStateWrapper();

           /**
            * @fn	void IStateWrapper::setState ( bool state );
            *
            * @brief	method to setter state.
            *
            * @author	Cesar.bonilla
            * @date	4/28/2011
            *
            * @param	state	check state.
            */

           void setState ( bool state );

           /**
            * @fn	virtual bool IStateWrapper::getState () = 0;
            *
            * @brief	method to getter state.
            *
            * @author	Cesar.bonilla
            * @date	4/28/2011
            *
            * @return	value state.
            */

           virtual bool getState () = 0;

        protected:
           bool state; ///< true to state
        };
      }
   }
}

#endif /*__ISTATE_WRAPPER_H__*/
