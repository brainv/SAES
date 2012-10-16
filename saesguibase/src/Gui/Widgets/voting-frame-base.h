/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
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
/**
 * @file ballot-option-selection-widget.h
 * @brief ballot option selection container in voting experience
 */

#ifndef _VOTING_FRAME_BASE_H
#define _VOTING_FRAME_BASE_H

#include <Widgets/StepWidget.hxx>
#include <Configuration/label-configuration.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	VotingFrameBase
				 *
				 * @brief	Header class VotingFrameBase.
				 *
				 * @author	Juan delgado &lt;juan.delgado@smartmatic.com&gt;
				 * @date	4/29/2011
				 */

				class VotingFrameBase: public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					
					virtual void RefreshLabels() = 0;

					virtual void ShowBackButton();

					virtual void SetBackButton(bool show);
					/**
					 * @brief virtual method getter label config
					 * @return title label config
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					virtual Smartmatic::GUI::Configuration::LabelConfiguration getTitleLabelConfig() = 0;
					/**
					 * @brief virtual method getter label config
					 * @return bottom label config
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					virtual Smartmatic::GUI::Configuration::LabelConfiguration getBottomLabelConfig() = 0;

					virtual void SetWidgetEnabled(bool enabled = true) = 0;
				};
			}
		}
	}
}

#endif // _VOTING_FRAME_BASE_H
