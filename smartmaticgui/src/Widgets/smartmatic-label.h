/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * custom-label
 * Copyright (C)  2011 <>
 * 
 * custom-label is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * custom-label is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SMARTMATIC_LABEL_H_

/**
 * @brief	Gets the smartmatic label h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _SMARTMATIC_LABEL_H_

#include <gtkmm.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class SmartmaticLabel: public Gtk::Label 
			{
			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				SmartmaticLabel();

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	label   	The label.
				 * @param	mnemonic	true to mnemonic.
				 */

				SmartmaticLabel(const Glib::ustring& label, bool mnemonic=false);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	label   	The label.
				 * @param	xalign  	The xalign.
				 * @param	yalign  	The yalign.
				 * @param	mnemonic	true to mnemonic.
				 */

				SmartmaticLabel(const Glib::ustring& label, float xalign, float yalign, bool mnemonic=false);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	label   	The label.
				 * @param	xalign  	The xalign.
				 * @param	yalign  	The yalign.
				 * @param	mnemonic	true to mnemonic.
				 */

				SmartmaticLabel(const Glib::ustring& label, Gtk::AlignmentEnum xalign, Gtk::AlignmentEnum yalign=Gtk::ALIGN_CENTER, bool mnemonic=false);

				SmartmaticLabel(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder=Gtk::Builder::create());

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				virtual ~SmartmaticLabel();

				void SetCustomWrapMode();

				void SetSize(int size);

				void SetBold(bool bold);

				/**
				 * @brief	Sets automatically wrap for a label
				 *
				 * @author	Juan.Delgado
				 * @date	02/08/2011
				 *
				 * @param [in,out]	label	The label.
				 * @param 			width	The width of the label.
				 * @param 			height	The height of the label.
				 */
				static void SetAutoWrap(Label &label, int width, int height);


			protected:
				//Overrides:

				/**
				 * @brief	Handles size allocate signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	allocation	The allocation.
				 */

				virtual void on_size_allocate(Gtk::Allocation& allocation);

				void Initialize();

			private:
				bool customWrapMode;
				bool isRecursive;



			};
		}
	}
}

#endif // _SMARTMATIC_LABEL_H_
