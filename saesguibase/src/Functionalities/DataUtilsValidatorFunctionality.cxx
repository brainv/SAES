/**
 * @file DataUtilsValidatorFunctionality.cxx
 * @brief Body class data utils validator functionality
 * @date 18/07/2012
 * @author Yadickson Soto
 */

#include "DataUtilsValidatorFunctionality.hxx"
#include "Gui/Widgets/FactoryMethodWidget.hxx"
#include "Gui/Widgets/AbstractFactoryWidget.hxx"
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <Voting/VotingDevice/card-data-wrapper.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/IO/Path.h>
#include <System/IO/Directory.h>
#include <System/IO/File.h>
#include <System/Utils/StringUtils.hxx>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Resources/election-string-resources-manager.h>
#include <Voting/Election/ElectionInstalationLanguages.h>
#include <Voting/set-language-functionality.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::VotingCenters;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Utils;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Resources;

ISMTTLog* DataUtilsValidatorFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality",GETTEXT_PACKAGE);

DataUtilsValidatorFunctionality* DataUtilsValidatorFunctionality::instance = NULL;

DataUtilsValidatorFunctionality::DataUtilsValidatorFunctionality()
{
	dataUtilsWidget = NULL;
	electoralConfiguration = NULL;
	votingExperienceController = NULL;

	currentDirectories = MachineOperationManager::getInstance()->getSaesInstallDirectories();
	centerCaseSensitive = SAESGUIConfigurationManager::Current()->getPMInstallationWidgetConfig().getLoginCaseSensitiveConfiguration();
}

DataUtilsValidatorFunctionality::~DataUtilsValidatorFunctionality()
{
	deleteElement();
}

DataUtilsValidatorFunctionality * DataUtilsValidatorFunctionality::getInstance()
{
	if (!instance)
	{
		instance = new DataUtilsValidatorFunctionality();
	}

	return instance;
}

std::string DataUtilsValidatorFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.WindowTitle");
}

bool DataUtilsValidatorFunctionality::ShowWindowTitle()
{
	return false;
}

Smartmatic::Log::ISMTTLog* DataUtilsValidatorFunctionality::getLogger()
{
	return logger;
}

Glib::ustring DataUtilsValidatorFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.LogStartFunctionality");
}

Glib::ustring DataUtilsValidatorFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.LogCloseFunctionality");
}

Smartmatic::Functionality::MenuOptionDescriptor DataUtilsValidatorFunctionality::GetMenuOptionType()
{
	return Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor(Smartmatic::SAES::Functionality::MenuType::DATA_UTILS_VALIDATOR,false);
}

Gtk::Widget * DataUtilsValidatorFunctionality::GetFrame()
{
	dataUtilsWidget = AbstractFactoryWidget::createDataUtilsValidatorWidget();

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this,&DataUtilsValidatorFunctionality::startValidate), 1000);

	return dataUtilsWidget;
}

void DataUtilsValidatorFunctionality::Dispose()
{

}

void DataUtilsValidatorFunctionality::Initialize()
{
	electoralConfiguration = new ElectoralConfiguration();
	MachineOperationManager::getInstance()->StopDetection();
}

void DataUtilsValidatorFunctionality::deleteElement()
{
	if (dataUtilsWidget)
	{
		delete dataUtilsWidget;
		dataUtilsWidget = NULL;
	}
	if (electoralConfiguration)
	{
		delete electoralConfiguration;
		electoralConfiguration = NULL;
	}
	if (votingExperienceController)
	{
		delete votingExperienceController;
		votingExperienceController = NULL;
	}
}

void DataUtilsValidatorFunctionality::block()
{
	logger->Debug("Block functionality");
}

void DataUtilsValidatorFunctionality::partial()
{
	logger->Debug("Partial functionality");
}

void DataUtilsValidatorFunctionality::resume()
{
	logger->Debug("Resume functionality");
}

void DataUtilsValidatorFunctionality::startValidate()
{
	keyMap.clear();
	votingCenters.clear();

	std::string votingCentersFilePath = currentDirectories->getVotingCentersInstalationFileFullPath();

	bool loadVotingCenter = VotingCentersWrapper::getInstance()->LoadFile(votingCentersFilePath);
	bool loadKey = loadKeys();

	logger->Debug("Voting Centers File path is: " + votingCentersFilePath);

	if(loadVotingCenter && loadKey)
	{
		std::list< VotingCenter > & list (VotingCentersWrapper::getInstance()->getVotingCenters());
		std::list< VotingCenter >::iterator itVc;

		{
			std::stringstream ss;
			ss << "Number of voting centers: " << list.size();
			logger->Debug(ss.str());
		}

		for (itVc = list.begin(); itVc != list.end(); itVc++)
		{
			votingCenters.push_back((*itVc));
		}

		currentCenter = 0;
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this,&DataUtilsValidatorFunctionality::nextVotingCenter), 500);
	}
	else if (!loadVotingCenter)
	{
		dataUtilsWidget->showError(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.ErrorLoadVotingCenterFile"));
		logger->Debug("Could not open file: " + votingCentersFilePath);
	}
	else if (!loadKey)
	{
		dataUtilsWidget->showError(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.ErrorLoadVotingCenterFile"));
		logger->Debug("Could not open key file");
	}
}

void DataUtilsValidatorFunctionality::nextVotingCenter()
{
	if (currentCenter < votingCenters.size())
	{
		center = votingCenters[currentCenter];
		currentCenter++;

		logger->Debug("Process voting center " + center.getCode());

		dataUtilsWidget->setCenter(center.getCode());
		dataUtilsWidget->showProgress(center.getCode(), currentCenter, votingCenters.size());

		std::string folderName = center.getFolder_name();
		std::string programUnit = (center.getProgram_unit() != NULL ? center.getProgram_unit().get() : "");

		currentDirectories->setWorkingPath(folderName);
		currentDirectories->setProgramUnitName(programUnit);

		logger->Debug("Generate Center: " + folderName);

		folderPath = Path::Combine(currentDirectories->getVotingExperienceValidationFolderFullPath(), folderName);

		dataUtilsWidget->addResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.InitializesTheCenterValidation"));

		if(!Glib::thread_supported())
			Glib::thread_init();
		Glib::Thread::create(sigc::mem_fun(*this, &DataUtilsValidatorFunctionality::validateCenter), false);
	}
	else
	{
		dataUtilsWidget->showResult();
	}
}

void DataUtilsValidatorFunctionality::validateCenter()
{
	std::string currentDirectoryPath = currentDirectories->getBasePath();

	if(Smartmatic::System::IO::Directory::DirectoryExists(currentDirectoryPath))
	{
		logger->Debug("Loading Configuration of: " + currentDirectoryPath);

		if(loadElectoralConfiguration())
		{
			dataUtilsWidget->addResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.LoadLanguages"));

			Languages::LanguageSequence & sequence (electoralConfiguration->getLanguages().getLanguage() );

			if(sequence.size() == 0)
			{
				logger->Debug("Could not load languages of the configuration");
				dataUtilsWidget->addFailResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.LanguageNotFound"));
			}
			else
			{
				try
				{
					dataUtilsWidget->addResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.CreateCards"));

					Voting_device vd = MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();

					std::list < Custom_attribute_definition > listCAD =
							MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getCustomAttributeDefinitionList(vd, VotingDevice::Machine_type::VOTING_DEVICES_PM);

					std::vector<Custom_attribute*> attributes;  ///< The attributes

					for(std::list<VotingDevice::Custom_attribute_definition>::iterator l (listCAD.begin()); l != listCAD.end(); ++l)
					{
						for ( VotingDevice::Custom_attribute_definition::ValueIterator c ((*l).getValue().begin()); c != (*l).getValue().end(); ++c)
						{
							VotingDevice::Custom_attribute* attribute = new VotingDevice::Custom_attribute();
							attribute->setCode(l->getCode());
							attribute->setValue(*c);
							attributes.push_back(attribute);

							std::string name = getResource(*c);

							try
							{
								dataUtilsWidget->addResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.CreateCard") + std::string(" ") + name);

								VotingDevice::Card_data cardData;
								VotingDevice::CardDataWrapper::GenerateCardData(MachineOperationManager::getInstance()->getElectoralConfiguration(), attributes, cardData, false, Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_DEMOSTRATION_VOTE_CARD);

								if(!votingExperienceController->init(cardData))
								{
									logger->Debug("Error validate info card");
									dataUtilsWidget->addFailResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.InitVotingExperienceFail"));
								}
							}
							catch(CryptoException & ex)
							{
								dataUtilsWidget->addFailResult(ex.getMessage());
							}
							catch(ElectionException & ex)
							{
								dataUtilsWidget->addFailResult(ex.getMessage());
							}
							catch(VotingDeviceException & ex)
							{
								dataUtilsWidget->addFailResult(ex.getMessage());
							}
							catch(...)
							{
								dataUtilsWidget->addFailResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.InitVotingExperienceFail"));
							}

							attributes.clear();
							delete attribute;
							votingExperienceController->dispose();
						}
					}
				}
				catch(ElectionException & ex)
				{
					dataUtilsWidget->addFailResult(ex.getMessage());
				}
				catch(VotingDeviceException & ex)
				{
					dataUtilsWidget->addFailResult(ex.getMessage());
				}
				catch(...)
				{
					logger->Debug("Error validate center");
				}
			}
		}
		else
		{
			dataUtilsWidget->addFailResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.LoadConfigurationFail"));
			logger->Debug("Error loading the configuration");
		}
	}
	else
	{
		dataUtilsWidget->addFailResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.CenterFolderNotFound"));
		logger->Debug("Directory no exist: " + currentDirectoryPath);
	}

	Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &DataUtilsValidatorFunctionality::nextVotingCenter), 100);
}

bool DataUtilsValidatorFunctionality::loadElectoralConfiguration()
{
	bool validate = true;
	std::string password;

	dataUtilsWidget->addResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.StartLoadConfiguration"));

	try
	{
		MachineOperationManager::getInstance()->setElectoralConfiguration( electoralConfiguration );

		if (getPassword(password))
		{
			if (!password.empty())
			{
				std::string centerCode = center.getCode();
				logger->Debug("Authentication " + centerCode + " -> " + password);

				dataUtilsWidget->addResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.Authentication"));
				validate = MachineOperationManager::getInstance()->authentication(centerCode, password, centerCaseSensitive);
			}

			if (validate)
			{
				if (votingExperienceController)
				{
					delete votingExperienceController;
					votingExperienceController = NULL;
				}

				votingExperienceController = new VotingExperienceController ( electoralConfiguration );
				MachineOperationManager::getInstance()->setVotingExperienceController( votingExperienceController );

				dataUtilsWidget->addResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.InitElectoralConfiguration"));

				electoralConfiguration->init(currentDirectories);

				dataUtilsWidget->addResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.LoadElectoralConfiguration"));

				electoralConfiguration->loadAllData();
			}
			else
			{
				dataUtilsWidget->addFailResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.AuthenticationFail"));
			}
		}
		else
		{
			dataUtilsWidget->addFailResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.PasswordNotFound"));
			validate = false;
		}

	}
	catch(ElectionException & ex)
	{
		dataUtilsWidget->addFailResult(ex.getMessage());
		validate = false;
	}
	catch(VotingDeviceException & ex)
	{
		dataUtilsWidget->addFailResult(ex.getMessage());
		validate = false;
	}
	catch(CryptoException & ex)
	{
		dataUtilsWidget->addFailResult(ex.getMessage());
		validate = false;
	}
	catch(SignedException & ex)
	{
		dataUtilsWidget->addFailResult(ex.getMessage());
		validate = false;
	}
	catch(FileSystemException & ex)
	{
		dataUtilsWidget->addFailResult(ex.getMessage());
		validate = false;
	}
	catch(...)
	{
		dataUtilsWidget->addFailResult(_("Smartmatic.SAES.GUI.Functionality.DataUtilsValidatorFunctionality.ErrorLoadElectoralConfiguration"));
		validate = false;
	}

	return validate;
}

bool DataUtilsValidatorFunctionality::loadKeys()
{
	bool validate = false;

	if (SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getSecretKeyEncrypted())
	{
		std::string file = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getKeyFile();
		std::string separator = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getSeparator();
		unsigned int positionCode = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getPositionCode();
		unsigned int positionPassword = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getPositionPassword();

		std::string dom = currentDirectories->getDOMMemoryBasePath();
		std::string filePath = Path::Combine(dom, file);

		if (File::canOpenFile(filePath))
		{
			validate = true;

		    try
		    {
				std::ifstream ifs;
				ifs.exceptions (std::ifstream::badbit | std::ifstream::failbit);
				ifs.open (filePath.c_str());

				std::string contents;

				while(ifs.good())
				{
					getline(ifs, contents);
					std::vector <std::string> vector;

					StringUtils::split(contents, separator, vector);

					if (vector.size() >= positionCode && vector.size() >= positionPassword)
					{
						std::string code = StringUtils::trim(vector[positionCode]);
						std::string pass = StringUtils::trim(vector[positionPassword]);
						keyMap[code] = pass;
					}
				}

				ifs.close();
		    }
		    catch (std::ifstream::failure & ex)
		    {

		    }
		}
		else
		{
			logger->Debug("Error load file " + filePath);
		}
	}
	else
	{
		validate = true;
	}

	return validate;
}

bool DataUtilsValidatorFunctionality::getPassword(std::string & password)
{
	bool validate = true;

	if (SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getSecretKeyEncrypted())
	{
		if (keyMap.find(center.getCode()) != keyMap.end())
		{
			password = keyMap[center.getCode()];
		}
		else
		{
			logger->Debug("Not password for " + center.getCode());
			validate = false;
		}
	}

	return validate;
}

std::string DataUtilsValidatorFunctionality::getResource(std::string key)
{
	Languages::LanguageSequence & sequence (electoralConfiguration->getLanguages().getLanguage() );
	Languages::LanguageIterator it;

	std::string language, country;
	SetLanguageFunctionality::getCurrentLanguageCountry(language, country);

	ElectionInstalationLanguages::getInstance()->clearLanguage();
	bool found = false;

	for (it = sequence.begin(); it != sequence.end(); ++it)
	{
		ElectionInstalationLanguages::getInstance()->addInstallationLanguages((*it));

		if (!found)
		{
			if ((*it).getLanguage() == language)
			{
				found = true;
			}

			SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry((*it).getLanguage(), (*it).getCountry());
		}
	}

	std::string result = ElectionStringResourcesManager::Current()->getResource(key);
	SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(language, country);

	return result;
}
