/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	party-contest-widget.h
 *
 * @brief	Declares the party contest widget class.
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PARTY_CONTEST_WIDGET_H_
#define _PARTY_CONTEST_WIDGET_H_

#include <gtkmm.h>


namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{								
				/**
				 * @class	PartyContestWidget
				 *
				 * @brief	Party contest widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class PartyContestWidget: public Gtk::Frame
				{
				public:
						enum ImageType 
						{
						  ImageType_Selected=1,
						  ImageType_Unselected=2,
						  ImageType_NotApplicable=3
						};
										 
						//CONSTRUCTOR

						/**
						 * @fn	PartyContestWidget::PartyContestWidget(bool isVisibleImage,std::string labeltext,
						 * 		bool isVisibleLabel,std::string party,std::string contest,ImageType imageType,
						 * 		bool isImagenTextoR,bool isHorizontalR);
						 *
						 * @brief	Constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	isVisibleImage	true if is visible image.
						 * @param	labeltext	  	The labeltext.
						 * @param	isVisibleLabel	true if is visible label.
						 * @param	party		  	The party.
						 * @param	contest		  	The contest.
						 * @param	imageType	  	Type of the image.
						 * @param	isImagenTextoR	true if is imagen texto r.
						 * @param	isHorizontalR 	true if is horizontal r.
						 */

						PartyContestWidget(bool isVisibleImage,std::string labeltext, bool isVisibleLabel,std::string party,std::string contest,ImageType imageType,bool isImagenTextoR,bool isHorizontalR);
						//DESTRUCTOR

						/**
						 * @fn	PartyContestWidget::~PartyContestWidget();
						 *
						 * @brief	Finaliser.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						~PartyContestWidget();

						/**
						 * @fn	void PartyContestWidget::setIsVisibleImage(bool isVisibleImageR);
						 *
						 * @brief	method to set visibility of the image.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	isVisibleImageR	true if is visible image r.
						 */

						void setIsVisibleImage(bool isVisibleImageR);

						/**
						 * @fn	void PartyContestWidget::setIsVisibleLabel(bool isVisibleLabelR);
						 *
						 * @brief	method to set visibility of the label.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	isVisibleLabelR	true if is visible label r.
						 */

						void setIsVisibleLabel(bool isVisibleLabelR);

						/**
						 * @fn	void PartyContestWidget::setLabelText(std::string labeltextR);
						 *
						 * @brief	method to set the labeltext.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	labeltextR	The labeltext r.
						 */

						void setLabelText(std::string labeltextR);	

						/**
						 * @fn	void PartyContestWidget::setIsHorizontalR(bool isHorizontal);
						 *
						 * @brief	Sets the is horizontal r.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	isHorizontal	true if is horizontal.
						 */

						void setIsHorizontalR(bool isHorizontal);

						/**
						 * @fn	void PartyContestWidget::setIsImagenTextoR(bool isImagenText);
						 *
						 * @brief	Sets the is imagen texto r.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	isImagenText	true if is imagen text.
						 */

						void setIsImagenTextoR(bool isImagenText);

						/**
						 * @fn	void PartyContestWidget::setColorEventBox(Gdk::Color selectedColor);
						 *
						 * @brief	Sets a color event box.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	selectedColor	The selected color.
						 */

						void setColorEventBox(Gdk::Color selectedColor);

						/**
						 * @fn	void PartyContestWidget::setSizeWidget(int width,int height);
						 *
						 * @brief	Sets a size widget.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	width 	The width.
						 * @param	height	The height.
						 */

						void setSizeWidget(int width,int height);

						/**
						 * @fn	void PartyContestWidget::Initialize();
						 *
						 * @brief	Initializes this object.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void Initialize();

						/**
						 * @fn	void PartyContestWidget::Dispose();
						 *
						 * @brief	Dispose of this object, cleaning up any resources it uses.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void Dispose();
						
						sigc::signal<void, std::string, std::string> signalEmitted; ///< The signal emitted
				protected:
						bool isImageTexto;  ///< true if is image texto
						bool isHorizontal;  ///< true if is horizontal

						/**
						 * @fn	bool PartyContestWidget::on_zone_clicked(GdkEventButton* event );
						 *
						 * @brief	Executes the zone clicked action.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param [in,out]	event	If non-null, the event.
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool  on_zone_clicked(GdkEventButton* event );

						std::string party;  ///< The party
						std::string contest;	///< The contest
																	 
						Gtk::EventBox event;	///< The event
						Gtk::VBox vboxEvents;   ///< The vbox events
						Gtk::HBox hboxEvents;   ///< The hbox events
						Gtk::Label labelTitle;  ///< The label title
						Gtk::Image imageTitle;  ///< The image title
						Gtk::Alignment Align;   ///< The align
						Gtk::Alignment alignImage;  ///< The align image
						Gdk::Color colorEventBox;   ///< The color event box


				private:
					
							
				};

			}
		}
	}
}

#endif // _PARTY_CONTEST_WIDGET_H_


