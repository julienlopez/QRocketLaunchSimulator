#include "flightwidget.hpp"
#include "rocketwidget.hpp"

#include "rocket.hpp"

#include <etl/utils/make_unique.hpp>

#include <QHBoxLayout>

FlightWidget::FlightWidget(QWidget* parent_) : QWidget(parent_)
{
	auto* hl = new QHBoxLayout;
	m_rocket_widget = new RocketWidget;
	hl->addWidget(m_rocket_widget);
	hl->addStretch();
	setLayout(hl);
}

FlightWidget::~FlightWidget()
{
}

void FlightWidget::prepareLaunch(const LaunchParameters& parameters)
{
	m_rocket = utils::make_unique<Rocket>(parameters.rocket_model, parameters.payload_mass);
	m_rocket_widget->setRocket(*m_rocket);
}
