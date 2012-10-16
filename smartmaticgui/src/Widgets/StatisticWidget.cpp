/*
 * StatisticWidget.cpp
 *
 *  Created on: Sep 6, 2011
 *      Author: Juan Delgado
 */

#include "StatisticWidget.h"

using namespace Gtk;
using namespace std;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::GUI::Widgets;

StatisticWidget::StatisticWidget(std::map<std::string, std::map< std::string, std::string > > statisticMap)
{
	titleLabelList.clear();
	statsLabelList.clear();
	valuesMap.clear();
	this->statisticMap = statisticMap;

	for(std::map<string, std::map< string, string > >::iterator iter = statisticMap.begin();
			iter != statisticMap.end(); iter++)
	{
		Label* labelTitle = manage(new Label(iter->first));
		labelTitle->show();
		pack_start(*labelTitle, false, false);
		titleLabelList.push_back(labelTitle);

		VBox* insideVbox = manage(new VBox(true, 1));
		insideVbox->show();
		pack_start(*insideVbox);

		for(std::map<string, string>::iterator iter2 = iter->second.begin();
				iter2 != iter->second.end(); iter2++)
		{
			Frame* frame = manage(new Frame());
			frame->show();
			insideVbox->pack_start(*frame);

			HBox* insideHbox = manage(new HBox());
			insideHbox->show();
			frame->add(*insideHbox);

			Label* labelStat = manage(new Label(iter2->second));
			labelStat->show();
			labelStat->set_alignment(0.0, 0.5);
			insideHbox->pack_start(*labelStat);
			statsLabelList.push_back(labelStat);

			Label* labelValue = manage(new Label("0"));
			labelValue->show();
			insideHbox->pack_end(*labelValue, false, false);
			statsLabelList.push_back(labelValue);
			valuesMap[iter2->first] = labelValue;
		}
	}
	show();
}

StatisticWidget::~StatisticWidget()
{

}

void StatisticWidget::SetValue(std::string codeStat, std::string value)
{
	if(valuesMap.find(codeStat) != valuesMap.end())
	{
		valuesMap[codeStat]->set_text(value);
	}
}

void StatisticWidget::SetStatsLabelConfiguration(LabelConfiguration& labelconfiguration)
{
	for(list <Gtk::Label* >::iterator iter = statsLabelList.begin();
			iter != statsLabelList.end(); iter++)
	{
		LabelConfiguration::SetLabelConfigurationWithoutAlignment((*iter), labelconfiguration);
	}
}

void StatisticWidget::SetTitlesLabelConfiguration(LabelConfiguration& labelconfiguration)
{
	for(list <Gtk::Label* >::iterator iter = titleLabelList.begin();
			iter != titleLabelList.end(); iter++)
	{
		LabelConfiguration::SetLabelConfiguration((*iter), labelconfiguration);
	}
}

void StatisticWidget::SetTitlesSizeRequest(int width, int height)
{
	for(list <Gtk::Label* >::iterator iter = titleLabelList.begin();
			iter != titleLabelList.end(); iter++)
	{
		(*iter)->set_size_request(width, height);
		(*iter)->set_line_wrap(true);
	}
}

void StatisticWidget::SetValuesWidth(int width)
{
	for(std::map < std::string, Gtk::Label* >::iterator iter = valuesMap.begin();
			iter != valuesMap.end(); iter++)
	{
		iter->second->set_size_request(width, -1);
	}
}

std::string StatisticWidget::GetValue(std::string codeStat)
{
	return valuesMap[codeStat]->get_text();
}
