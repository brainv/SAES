/**
 * @file BallotOptionTableWidget.cxx
 * @brief Body class ballot option button widget
 * @date 13/03/2012
 * @author Yadickson Soto
 */

#include "BallotOptionTableWidget.hxx"
#include "FillTableWidget.hxx"

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::Election;

BallotOptionTableWidget::BallotOptionTableWidget(FillTableWidget * fillTableWidget)
: Gtk::Frame()
{
	this->fillTableWidget = fillTableWidget;

	this->set_shadow_type(Gtk::SHADOW_IN);
	this->add(*fillTableWidget);
	this->show_all_children();
	this->show();
}

BallotOptionTableWidget::~BallotOptionTableWidget()
{
	this->remove();

	if (fillTableWidget)
	{
		delete fillTableWidget;
		fillTableWidget = NULL;
	}
}

void BallotOptionTableWidget::addPrincipal(BallotOptionWidget * widget)
{
	fillTableWidget->addPrincipal(widget);
}

void BallotOptionTableWidget::addStandIn(BallotOptionWidget * widget)
{
	fillTableWidget->addStandIn(widget);
}

void BallotOptionTableWidget::fill(Contest & contest, int totalW, int totalH)
{
	fillTableWidget->fill(contest, totalW, totalH);
}

void BallotOptionTableWidget::clear()
{
	fillTableWidget->clear();
}

void BallotOptionTableWidget::update()
{
	fillTableWidget->update();
}

std::list <BallotOptionWidget * > & BallotOptionTableWidget::getPrincipalList()
{
	return fillTableWidget->getPrincipalList();
}

std::list <BallotOptionWidget * > & BallotOptionTableWidget::getStandInList()
{
	return fillTableWidget->getStandInList();
}
