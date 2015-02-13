#include "parameterwidget.hpp"

#include "rocketmodel.hpp"

#include <fstream>

#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

ParameterWidget::ParameterWidget(QWidget* parent_) : QWidget(parent_)
{
	const int c_spacing = 30;

	auto* hl = new QHBoxLayout;

	hl->addWidget(new QLabel(tr("Rocket Model: ")));
	m_cb_rocket_model = new QComboBox;
	m_cb_rocket_model->addItems(loadRocketModels());
	hl->addWidget(m_cb_rocket_model);

	hl->addSpacing(c_spacing);

	hl->addWidget(new QLabel(tr("Start of gravity turn (km): ")));
	m_dsb_start_gravity_turn = new QDoubleSpinBox;
	m_dsb_start_gravity_turn->setMinimum(0);
	m_dsb_start_gravity_turn->setMaximum(200);
	m_dsb_start_gravity_turn->setValue(10);
	hl->addWidget(m_dsb_start_gravity_turn);

	hl->addSpacing(c_spacing);

	hl->addWidget(new QLabel(tr("End of gravity turn (km): ")));
	m_dsb_end_gravity_turn = new QDoubleSpinBox;
	m_dsb_end_gravity_turn->setMinimum(5);
	m_dsb_end_gravity_turn->setMaximum(500);
    m_dsb_end_gravity_turn->setValue(100);
	hl->addWidget(m_dsb_end_gravity_turn);

	hl->addSpacing(c_spacing);

	hl->addWidget(new QLabel(tr("Angle of thrust (°): ")));
	m_dsb_angle = new QDoubleSpinBox;
	m_dsb_angle->setMinimum(0.1);
	m_dsb_angle->setMaximum(50);
	m_dsb_angle->setValue(1);
	hl->addWidget(m_dsb_angle);

	hl->addSpacing(c_spacing);

	m_launch_button = new QPushButton(tr("Launch"));
	connect(m_launch_button, &QPushButton::clicked, this, &ParameterWidget::launch);
	hl->addWidget(m_launch_button);

	hl->addStretch();

	setLayout(hl);
	setMinimumWidth(800);
}

QStringList ParameterWidget::loadRocketModels()
{
    const auto models_path = QApplication::applicationDirPath() + "/rocket_models";
    const QDir directory = models_path;
    Q_ASSERT(directory.exists());
    auto files = directory.entryList({"*.json"});
    std::transform(files.begin(), files.end(), files.begin(), [&directory](const QString& str)
    {
        Q_ASSERT(str.endsWith(".json"));
        std::ifstream file(directory.absoluteFilePath(str).toStdString());
        Q_ASSERT(file);
        const auto model = RocketModel::fromJson(file);
        return QString::fromStdString(model.name);
    });
    return files;
}

#include <QDebug>
#include <QTimer>

void ParameterWidget::launch()
{
	qDebug() << "ParameterWidget::launch()";
	qDebug() << "Rocket Model : " << m_cb_rocket_model->currentText();
	qDebug() << "Start of Gravity Turn : " << m_dsb_start_gravity_turn;
	qDebug() << "End of Gravity Turn : " << m_dsb_end_gravity_turn;
	qDebug() << "Angle : " << m_dsb_angle;

	m_cb_rocket_model->setEnabled(false);
	m_dsb_start_gravity_turn->setEnabled(false);
	m_dsb_end_gravity_turn->setEnabled(false);
	m_dsb_angle->setEnabled(false);
	m_launch_button->setEnabled(false);

	auto* timer = new QTimer;
	timer->setSingleShot(true);
	connect(timer, &QTimer::timeout, this, &ParameterWidget::launchDone);
	timer->start(1000);
}

void ParameterWidget::launchDone()
{
	qDebug() << "ParameterWidget::launchDone()";

	m_cb_rocket_model->setEnabled(true);
	m_dsb_start_gravity_turn->setEnabled(true);
	m_dsb_end_gravity_turn->setEnabled(true);
	m_dsb_angle->setEnabled(true);
	m_launch_button->setEnabled(true);

	sender()->deleteLater();
}
