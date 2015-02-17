#ifndef TELEMETRYWIDGET_HPP
#define TELEMETRYWIDGET_HPP

#include "engine.hpp"

#include <boost/optional.hpp>

#include <QWidget>

class QGroupBox;
class QPushButton;
class QLCDNumber;

class TelemetryWidget : public QWidget
{
	Q_OBJECT
public:
	explicit TelemetryWidget(QWidget* parent_ = 0);

private:
	boost::optional<std::reference_wrapper<const Engine>> m_engine;

	QPushButton* m_start_stop_button;
	QLCDNumber* m_altitude_lcd;
	QLCDNumber* m_speed_lcd;
	QLCDNumber* m_time_lcd;

	QGroupBox* createGroupBoxFlightValues();

public
slots:
	void setEngine(const Engine& engine);

	/**
	 * @brief updateWidgets
	 * @preconditions m_engine is valid
	 */
	void updateWidgets();

	void disable();
	void enable();

signals:
	void start();
	void stop();

private
slots:
	void onStartStopButtonClicked();
};

#endif // TELEMETRYWIDGET_HPP
