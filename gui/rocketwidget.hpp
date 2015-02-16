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

public
slots:
	void setRocket(const Rocket& rocket);

protected:
	virtual void paintEvent(QPaintEvent* evt) override;

private:
	struct GraphicalParameters
	{
		double ratio;
		int margin_width;
		int margin_height;
	};

	boost::optional<std::reference_wrapper<const Rocket>> m_rocket;
	GraphicalParameters m_graphical_parameter;

	void updateGraphicalParameters();

	/**
	 * @brief drawFairings
	 * @param painter
	 * @precondition m_rocket is valid
	 */
	void drawFairings(QPainter& painter) const;

	/**
	 * @brief drawStage
	 * @param painter
	 * @param stage
	 * @param offset
	 * @precondition m_rocket is valid
	 */
	void drawStage(QPainter& painter, const Stage& stage, double offset) const;

	static void changePainterColor(QPainter& painter, QColor color, double width = .1);
};

#endif // ROCKETWIDGET_HPP
