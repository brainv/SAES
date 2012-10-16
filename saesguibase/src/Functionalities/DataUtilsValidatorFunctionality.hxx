/**
 * @file DataUtilsValidatorFunctionality.hxx
 * @brief Header class data utils validator functionality
 * @date 18/07/2012
 * @author Yadickson Soto
 */

#ifndef DATAUTILSVALIDATORFUNCTIONALITY_HXX_
#define DATAUTILSVALIDATORFUNCTIONALITY_HXX_

#include <gtkmm.h>
#include <Functionalities/menu-option-descriptor.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Runtime/Environment/SaesInstallDirectories.hxx>
#include <Voting/VotingCenters/voting-centers-schema.hxx>
#include <Operation/Voting/VotingExperienceController.hxx>
#include <Gui/Widgets/DataUtilsValidatorWidget.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				/**
				 * @class DataUtilsValidatorFunctionality
				 * @brief Class data utils validator functionality
				 * @date 18/07/2012
				 * @author Yadickson Soto
				 */
				class DataUtilsValidatorFunctionality : public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{
				private:
					/**
					 * @brief Class constructor
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					DataUtilsValidatorFunctionality();

					static DataUtilsValidatorFunctionality * instance; ///< instance of class
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

					Smartmatic::SAES::GUI::Widgets::DataUtilsValidatorWidget * dataUtilsWidget; ///< data utils widget

					Smartmatic::SAES::Runtime::Environment::SaesInstallDirectories * currentDirectories;   ///< The current directories
					std::vector< Smartmatic::SAES::Voting::VotingCenters::VotingCenter > votingCenters; ///< all voting centers
					Smartmatic::SAES::Voting::VotingCenters::VotingCenter center; ///< current center

					std::map <std::string, std::string> keyMap; ///< key map

					Smartmatic::SAES::Voting::ElectoralConfiguration *electoralConfiguration;   ///< The electoral configuration
					Smartmatic::SAES::Operation::Voting::VotingExperienceController * votingExperienceController; ///< voting experience controller

					unsigned int currentCenter; ///< current center
					std::string folderPath;	///< The folder path
					bool centerCaseSensitive; ///< center case sensitive

				protected:

					/**
					 * @brief	Gets the window title.
					 * @return	The window title.
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					virtual std::string GetWindowTitle();
					/**
					 * @brief	getter isshow window title.
					 * @return	true is show window title.
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					virtual bool ShowWindowTitle();
					/**
					 * @brief	Gets the menu option type.
					 * @return	The menu option type.
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();
					/**
					 * @brief	Gets the frame.
					 * @return	null if it fails, else the frame.
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					Gtk::Widget * GetFrame();
					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					void Dispose();
					/**
					 * @brief	Initializes this object.
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					void Initialize();
					/**
					 * @brief	Gets the logger.
					 * @return	null if it fails, else the logger.
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					Smartmatic::Log::ISMTTLog* getLogger();
					/**
					 * @brief	Gets the start log message.
					 * @return	The start log message.
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					Glib::ustring getStartLogMessage();
					/**
					 * @brief	Gets the finish log message.
					 * @return	The finish log message.
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					Glib::ustring getFinishLogMessage();
					/**
					 * @brief method delete all element
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();
					/**
					 * @brief method block functionality
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					virtual void block();
					/**
					 * @brief method partial functionality
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					virtual void partial();
					/**
					 * @brief method resume functionality
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					virtual void resume();
					/**
					 * @brief method start validate
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					void startValidate();
					/**
					 * @brief method validate next voting center
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					void nextVotingCenter();
					/**
					 * @brief method validate voting center
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					void validateCenter();
					/**
					 * @brief method validate voting center
					 * @return true is load config success
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					bool loadElectoralConfiguration();
					/**
					 * @brief method getter password
					 * @param password password
					 * @return true is load password success
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					bool getPassword(std::string & password);
					/**
					 * @brief method load keys
					 * @return true is load keys success
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					bool loadKeys();

					std::string getResource(std::string key);

				public:
					/**
					 * @brief Method getter instance
					 * @return instance of class
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					static DataUtilsValidatorFunctionality * getInstance();
					/**
					 * @brief Class destroy
					 * @date 18/07/2012
					 * @author Yadickson Soto
					 */
					virtual ~DataUtilsValidatorFunctionality();
				};
			}
		}
	}
}
#endif /* DATAUTILSVALIDATORFUNCTIONALITY_HXX_ */
