#include "telemetrywidget.hpp"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLCDNumber>
#include <QLabel>

TelemetryWidget::TelemetryWidget(QWidget* parent_) : QWidget(parent_)
{
	setMinimumSize(200, 800);

	auto* vl = new QVBoxLayout;

	m_start_stop_button = new QPushButton(tr("Start"));
	connect(m_start_stop_button, &QPushButton::clicked, this,
			&TelemetryWidget::onStartStopButtonClicked);
	vl->addWidget(m_start_stop_button);

	vl->addWidget(createGroupBoxFlightValues());

	vl->addStretch();
	setLayout(vl);

	disable();
}

QGroupBox* TelemetryWidget::createGroupBoxFlightValues()
{
	auto* gb = new QGroupBox(tr("Flight Values"));
	auto* vl = new QVBoxLayout;

	vl->addWidget(new QLabel(tr("Altitude (m) :")));
	m_altitude_lcd = new QLCDNumber(8);
	vl->addWidget(m_altitude_lcd);

	vl->addWidget(new QLabel(tr("Speed (m/s) :")));
	m_speed_lcd = new QLCDNumber(8);
	vl->addWidget(m_speed_lcd);

    vl->addWidget(new QLabel(tr("Acceleration (m/s²) :")));
    m_acceleration_lcd = new QLCDNumber(8);
    vl->addWidget(m_acceleration_lcd);

	vl->addWidget(new QLabel(tr("Time of Flight (s) :")));
	m_time_lcd = new QLCDNumber(8);
	vl->addWidget(m_time_lcd);

	gb->setLayout(vl);
	return gb;
}

void TelemetryWidget::setEngine(const Engine& engine)
{
	m_engine = engine;
	updateWidgets();
	enable();
}

void TelemetryWidget::updateWidgets()
{
	Q_ASSERT(m_engine);
	m_altitude_lcd->display(m_engine->get().altitude());
	m_speed_lcd->display(m_engine->get().state().velocity.norm());
    m_acceleration_lcd->display(m_engine->get().currentAcceleration().norm());
	m_time_lcd->display(m_engine->get().currentTime());
}

void TelemetryWidget::disable()
{
	m_start_stop_button->setEnabled(false);
	m_altitude_lcd->setEnabled(false);
	m_speed_lcd->setEnabled(false);
    m_acceleration_lcd->setEnabled(false);
	m_time_lcd->setEnabled(false);
}

void TelemetryWidget::enable()
{
	m_start_stop_button->setEnabled(true);
	m_altitude_lcd->setEnabled(true);
	m_speed_lcd->setEnabled(true);
    m_acceleration_lcd->setEnabled(true);
	m_time_lcd->setEnabled(true);
}

void TelemetryWidget::onStartStopButtonClicked()
{
	if(m_start_stop_button->text() == tr("Start"))
	{
		m_start_stop_button->setText(tr("Stop"));
		emit start();
	}
	else
	{
		m_start_stop_button->setText(tr("Start"));
		emit stop();
	}
}
