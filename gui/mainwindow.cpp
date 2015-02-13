#include "mainwindow.hpp"
#include "parameterwidget.hpp"
#include "rocketwidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent_) : QMainWindow(parent_)
{
	auto vl = new QVBoxLayout;

	auto* pw = new ParameterWidget;
	vl->addWidget(pw);

    auto* hl = new QHBoxLayout;
    hl->addWidget(new RocketWidget);
    hl->addStretch();
    vl->addLayout(hl);

	auto* w = new QWidget;
	w->setLayout(vl);
	setCentralWidget(w);
}
