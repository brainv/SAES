/**
 * @file RefreshListener.hxx
 * @briefHeader class refresh listener
 * @date 03/04/2012
 * @author Yadickson Soto
 */

#ifndef REFRESHLISTENER_HXX_
#define REFRESHLISTENER_HXX_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class RefreshListener
			 * @brief Refresh listener.
			 * @date 03/04/2012
			 * @author Yadickson Soto
			 */
			class RefreshListener
			{
			public:
				/**
				 * @brief class constructor
				 * @date 03/04/2012
				 * @author Yadickson Soto
				 */
				RefreshListener();
				/**
				 * @brief class destroy
				 * @date 03/04/2012
				 * @author Yadickson Soto
				 */
				virtual ~RefreshListener();
				/**
				 * @brief virtual method refresh
				 * @date 03/04/2012
				 * @author Yadickson Soto
				 */
				virtual void refresh() = 0;
			};

		}
	}
}
#endif /* REFRESHLISTENER_HXX_ */
