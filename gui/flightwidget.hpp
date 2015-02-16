#ifndef FLIGHTWIDGET_HPP
#define FLIGHTWIDGET_HPP

#include "launchparameters.hpp"

#include <memory>

#include <QWidget>

class Rocket;
class RocketWidget;

class FlightWidget : public QWidget
{
	Q_OBJECT
public:
	explicit FlightWidget(QWidget* parent_ = 0);
	virtual ~FlightWidget();

private:
	using rocket_up = std::unique_ptr<Rocket>;
	rocket_up m_rocket;
	RocketWidget* m_rocket_widget;

signals:

public
slots:
	void prepareLaunch(const LaunchParameters& parameters);
};

#endif // FLIGHTWIDGET_HPP
