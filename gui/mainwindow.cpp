#include "mainwindow.hpp"
#include "parameterwidget.hpp"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent_) : QMainWindow(parent_)
{
	auto vl = new QVBoxLayout;

	auto* pw = new ParameterWidget;
	vl->addWidget(pw);

	auto* w = new QWidget;
	w->setLayout(vl);
	setCentralWidget(w);
}
