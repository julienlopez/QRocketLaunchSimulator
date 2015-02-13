#ifndef ROCKETWIDGET_HPP
#define ROCKETWIDGET_HPP

#include "rocket.hpp"

#include <boost/optional.hpp>

#include <QWidget>

class RocketWidget : public QWidget
{
	Q_OBJECT
public:
	explicit RocketWidget(QWidget* parent_ = 0);

	void setRocket(const Rocket& rocket);

private:
    boost::optional<std::reference_wrapper<const Rocket>> m_rocket;
};

#endif // ROCKETWIDGET_HPP
