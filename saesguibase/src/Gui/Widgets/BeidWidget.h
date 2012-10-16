/**
 * @file	BeidWidget.h
 *
 * @brief	Declares the beid widget class.
 * 			
 * @autor   Gerardo Hernandez			
 */

#ifndef BEIDWIDGET_H_
#define BEIDWIDGET_H_
#include <gtkmm.h>
#include "eid/CitizenInfo.h"
#include "Configuration/label-configuration.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	BeidWidget
				 *
				 * @brief	Beid widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class BeidWidget : public Gtk::Table
				{
					public:

						/**
						 * @fn	BeidWidget::BeidWidget(Smartmatic::SAES::EID::CitizenInfo citizenInfo,
						 * 		Glib::RefPtr<Gdk::Pixbuf> pixbuf);
						 *
						 * @brief	Constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	citizenInfo	Information describing the citizen.
						 * @param	pixbuf	   	The pixbuf.
						 */

						BeidWidget(Smartmatic::SAES::EID::CitizenInfo citizenInfo, Glib::RefPtr<Gdk::Pixbuf> pixbuf, bool showIdNumber = true);

						/**
						 * @fn	virtual BeidWidget::~BeidWidget();
						 *
						 * @brief	Finaliser.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						virtual ~BeidWidget();

					protected:
						Gtk::Table* tableTypeCard;  ///< The table type card

						Gtk::Table* boxIdContent;   ///< The box identifier content
						Gtk::Table* nameTable;  ///< The name table

						Gtk::Table* secondBoxIdContent; ///< The second box identifier content
						Gtk::Table* pictureTable;   ///< The picture table

						Gtk::Table* chipInfoBox;	///< The chip information box

						Gtk::Table* sexBox; ///< The sex box
						Gtk::Table* sexBoxDetail;   ///< The sex box detail
						Gtk::Alignment* sexBoxDetailAlignment;  ///< The sex box detail alignment
						Gtk::Table* signatureBox;   ///< The signature box
						Gtk::Table* signatureBoxDetail; ///< The signature box detail

						Gtk::Image* chipImage;  ///< The chip image
						Gtk::Alignment* chipImageAlignment; ///< The chip image alignment
						Gtk::Image* pictureImage;   ///< The picture image


						Gtk::Label* labelbelgique;  ///< The labelbelgique
						Gtk::Label* labelbelgie;	///< The labelbelgie
						Gtk::Label* labelbelgien;   ///< The labelbelgien
						Gtk::Label* labelbelgium;   ///< The labelbelgium
						Gtk::Label* labelcartee;	///< The labelcartee
						Gtk::Label* labelekaart;	///< The labelekaart
						Gtk::Label* labelekarte;	///< The labelekarte
						Gtk::Label* labelecard; ///< The labelecard

						Gtk::Label* labelName;  ///< Name of the label
						Gtk::Label* labelNameValue; ///< The label name value
						Gtk::Label* labelGivenNames;	///< List of names of the label givens
						Gtk::Label* labelGivenNamesValue;   ///< The label given names value

						Gtk::Label* labelTypedeCarte;   ///< The label typede carte
						Gtk::Label* labelAttestation;   ///< The label attestation
						Gtk::Label* lableSex;   ///< The lable sex
						Gtk::Label* labelCardNo;	///< The label card no
						Gtk::Label* labelCardNoValue;   ///< The label card no value

						Gtk::Label* labelValide;	///< The label valide
						Gtk::Label* labelValideValue;   ///< The label valide value
						Gtk::Label* lableSignatureTitulare; ///< The lable signature titulare
						Gtk::Label* labelHolderSignature;   ///< The label holder signature

						/**
						 * @fn	void BeidWidget::ClearWidget();
						 *
						 * @brief	Clears the widget.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void ClearWidget();

						/**
						 * @fn	void BeidWidget::UpdateWidgetInfo(Smartmatic::SAES::EID::CitizenInfo citizenInfo,
						 * 		Gtk::Image picture);
						 *
						 * @brief	Updates the widget information.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	citizenInfo	Information describing the citizen.
						 * @param	picture	   	The picture.
						 */

						void UpdateWidgetInfo(Smartmatic::SAES::EID::CitizenInfo citizenInfo, Gtk::Image picture);

						/**
						 * @fn	Smartmatic::GUI::Configuration::LabelConfiguration BeidWidget::GetLabelHeaderConfiguration();
						 *
						 * @brief	Gets the label header configuration.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	The label header configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetLabelHeaderConfiguration();

						/**
						 * @fn	Smartmatic::GUI::Configuration::LabelConfiguration BeidWidget::GetLabelHeaderValueConfiguration();
						 *
						 * @brief	Gets the label header value configuration.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	The label header value configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetLabelHeaderValueConfiguration();

						/**
						 * @fn	Smartmatic::GUI::Configuration::LabelConfiguration BeidWidget::GetLabelContentValueConfiguration();
						 *
						 * @brief	Gets the label content value configuration.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	The label content value configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetLabelContentValueConfiguration();

						/**
						 * @fn	Smartmatic::GUI::Configuration::LabelConfiguration BeidWidget::GetLabelContentBoldValueConfiguration();
						 *
						 * @brief	Gets the label content bold value configuration.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	The label content bold value configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetLabelContentBoldValueConfiguration();
				};
			}
		}
	}
}

#endif /* BEIDWIDGET_H_ */
