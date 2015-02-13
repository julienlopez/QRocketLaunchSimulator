#include "rocketwidget.hpp"

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
}
