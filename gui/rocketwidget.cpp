#include "rocketwidget.hpp"

#include <QPainter>

RocketWidget::RocketWidget(QWidget* parent_) : QWidget(parent_)
{
	auto p = palette();
	p.setBrush(QPalette::Window, Qt::white);
	setPalette(p);
	setAutoFillBackground(true);
	setMinimumSize(200, 800);
}

void RocketWidget::setRocket(const Rocket& rocket)
{
	m_rocket = rocket;
	update();
}

void RocketWidget::paintEvent(QPaintEvent* evt)
{
	QWidget::paintEvent(evt);

	if(!m_rocket)
		return;

	const auto& rocket = m_rocket->get();

	updateGraphicalParameters();

	QPainter painter(this);
	painter.translate(m_graphical_parameter.margin_width, m_graphical_parameter.margin_height);
	painter.scale(m_graphical_parameter.ratio, m_graphical_parameter.ratio);

	drawFairings(painter);
	double offset = rocket.fairings.length;
	std::for_each(rocket.stages().rbegin(), rocket.stages().rend(),
				  [this, &painter, &offset](const Stage& stage)
	{
		drawStage(painter, stage, offset);
		offset += stage.model.length;
	});
}

void RocketWidget::updateGraphicalParameters()
{
	if(!m_rocket)
		return;
	const auto& rocket = m_rocket->get();

	double total_height = rocket.totalLength();
	double max_diameter = rocket.maximumDiameter();
	QSize max_size(max_diameter, total_height);
	const auto ratio = std::min((double)width() * .9 / max_size.width(),
								(double)height() * .9 / max_size.height());

	m_graphical_parameter.ratio = ratio;
	m_graphical_parameter.margin_width = (width() - ratio * max_size.width()) / 2;
	m_graphical_parameter.margin_height = (height() - ratio * max_size.height()) / 2;
}

void RocketWidget::drawFairings(QPainter& painter) const
{
	assert(m_rocket);
	const auto& rocket = m_rocket->get();
	const double diameter = rocket.fairings.diameter;
	const double left_point = (rocket.maximumDiameter() - diameter) / 2;
	const double right_point = left_point + diameter;

	changePainterColor(painter, Qt::black);

	QPainterPath pathLeft;
	pathLeft.moveTo(left_point, rocket.fairings.length);
	pathLeft.cubicTo(QPointF(left_point, 0), QPointF(left_point, rocket.fairings.length / 6),
					 QPointF((right_point + left_point) / 2, 0));
	painter.drawPath(pathLeft);

	QPainterPath pathRight;
	pathRight.moveTo(right_point, rocket.fairings.length);
	pathRight.cubicTo(QPointF(right_point, 0), QPointF(right_point, rocket.fairings.length / 6),
					  QPointF((right_point + left_point) / 2, 0));
	painter.drawPath(pathRight);
}

void RocketWidget::drawStage(QPainter& painter, const Stage& stage, double offset) const
{
	assert(m_rocket);
	const auto& rocket = m_rocket->get();

	const QSizeF box(stage.model.diameter, stage.model.length);
	const double x_point = ((double)rocket.maximumDiameter() - stage.model.diameter) / 2;

	const QRectF fullRect(QPointF(x_point, offset), box);
    double percentage = stage.fillingRate();
	auto filledRect = fullRect;
	filledRect.setTop(offset + box.height() * (1 - percentage));
	painter.save();
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::cyan);
	painter.drawRect(filledRect);
	painter.restore();

	changePainterColor(painter, Qt::black);
	painter.drawRect(fullRect);
}

void RocketWidget::changePainterColor(QPainter& painter, QColor color, double width)
{
	auto pen = painter.pen();
	pen.setColor(color);
	pen.setWidthF(width);
	painter.setPen(pen);
}
