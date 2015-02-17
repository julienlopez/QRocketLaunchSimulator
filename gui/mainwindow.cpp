#include "mainwindow.hpp"
#include "parameterwidget.hpp"
#include "flightwidget.hpp"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent_) : QMainWindow(parent_)
{
	auto vl = new QVBoxLayout;

	auto* pw = new ParameterWidget;
	vl->addWidget(pw);

	auto* fw = new FlightWidget;
	vl->addWidget(fw);

	connect(pw, &ParameterWidget::prepareLaunch, fw, &FlightWidget::prepareLaunch);
	connect(fw, &FlightWidget::done, pw, &ParameterWidget::launchDone);

	auto* w = new QWidget;
	w->setLayout(vl);
	setCentralWidget(w);
}
