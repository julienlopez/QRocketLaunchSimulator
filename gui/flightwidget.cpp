#include "flightwidget.hpp"
#include "rocketwidget.hpp"
#include "telemetrywidget.hpp"

#include "body.hpp"
#include "rocket.hpp"

#include <etl/utils/make_unique.hpp>

#include <QHBoxLayout>
#include <QTimer>

constexpr double FlightWidget::s_dt;

FlightWidget::FlightWidget(QWidget* parent_) : QWidget(parent_)
{
	auto* hl = new QHBoxLayout;
	m_rocket_widget = new RocketWidget;
	hl->addWidget(m_rocket_widget);
	m_telemetry_widget = new TelemetryWidget;
	connect(m_telemetry_widget, &TelemetryWidget::stop, this, &FlightWidget::pause);
	connect(m_telemetry_widget, &TelemetryWidget::start, this, &FlightWidget::launch);
	hl->addWidget(m_telemetry_widget);
	hl->addStretch();
	setLayout(hl);

	m_update_timer = new QTimer(this);
	m_update_timer->setInterval(s_dt * 1000);
	connect(m_update_timer, &QTimer::timeout, this, &FlightWidget::onTimerClick);
}

FlightWidget::~FlightWidget()
{
}

void FlightWidget::prepareLaunch(const LaunchParameters& parameters)
{
	m_rocket = etl::utils::make_unique<Rocket>(parameters.rocket_model, parameters.payload_mass);
	m_engine = etl::utils::make_unique
		<Engine>(*m_rocket, Body(5.97219E24 * boost::units::si::kilograms,
								 6378000 * boost::units::si::meters));

	m_rocket_widget->setRocket(*m_rocket);
	m_telemetry_widget->setEngine(*m_engine);
}

void FlightWidget::launch()
{
	m_rocket->fire();
	m_update_timer->start();
}

void FlightWidget::pause()
{
	m_update_timer->stop();
}

void FlightWidget::onTimerClick()
{
	Q_ASSERT(m_engine);

	m_engine->tick(s_dt * boost::units::si::seconds);

	m_rocket_widget->update();
	m_telemetry_widget->updateWidgets();
}
