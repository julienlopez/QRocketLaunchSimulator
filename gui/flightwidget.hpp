#ifndef FLIGHTWIDGET_HPP
#define FLIGHTWIDGET_HPP

#include "launchparameters.hpp"

#include <memory>

#include <QWidget>

class Engine;
class Rocket;

class RocketWidget;
class TelemetryWidget;

class FlightWidget : public QWidget
{
	Q_OBJECT
public:
	explicit FlightWidget(QWidget* parent_ = 0);
	virtual ~FlightWidget();

private:
	using rocket_up = std::unique_ptr<Rocket>;
	using engine_up = std::unique_ptr<Engine>;

	rocket_up m_rocket;
	engine_up m_engine;

	RocketWidget* m_rocket_widget;
	TelemetryWidget* m_telemetry_widget;

	QTimer* m_update_timer;

	static constexpr double s_dt = .1;

public
slots:
	void prepareLaunch(const LaunchParameters& parameters);

	void launch();

    void pause();

signals:
	void done();

private
slots:
	/**
	 * @brief onTimerClick
	 * @preconditions m_engine is valid
	 */
	void onTimerClick();
};

#endif // FLIGHTWIDGET_HPP
