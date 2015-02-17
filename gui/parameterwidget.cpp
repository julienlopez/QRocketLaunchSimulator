#include "parameterwidget.hpp"

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
	loadRocketModels();
	const int c_spacing = 30;

	auto* hl = new QHBoxLayout;

	hl->addWidget(new QLabel(tr("Rocket Model: ")));
	m_cb_rocket_model = new QComboBox;
	m_cb_rocket_model->addItems(modelsNames());
	hl->addWidget(m_cb_rocket_model);

	hl->addSpacing(c_spacing);

	hl->addWidget(new QLabel(tr("Payload Mass (kg): ")));
	m_dsb_payload_mass = new QDoubleSpinBox;
	m_dsb_payload_mass->setMinimum(0);
	m_dsb_payload_mass->setMaximum(5000);
	m_dsb_payload_mass->setValue(1000);
	hl->addWidget(m_dsb_payload_mass);

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

void ParameterWidget::loadRocketModels()
{
	const auto models_path = QApplication::applicationDirPath() + "/rocket_models";
	const QDir directory = models_path;
	Q_ASSERT(directory.exists());
	auto files = directory.entryList({"*.json"});
	for(const auto& str : files)
	{
		Q_ASSERT(str.endsWith(".json"));
		std::ifstream file(directory.absoluteFilePath(str).toStdString());
		Q_ASSERT(file);
		m_models.push_back(RocketModel::fromJson(file));
	}
}

QStringList ParameterWidget::modelsNames() const
{
	QStringList res;
	for(const auto& model : m_models)
	{
		res.push_back(QString::fromStdString(model.name));
	}
	return res;
}

#include <QDebug>

void ParameterWidget::launch()
{
	qDebug() << "ParameterWidget::launch()";
	qDebug() << "Rocket Model : " << m_cb_rocket_model->currentText();
	qDebug() << "Payload Mass : " << m_dsb_payload_mass->value();
	qDebug() << "Start of Gravity Turn : " << m_dsb_start_gravity_turn->value();
	qDebug() << "End of Gravity Turn : " << m_dsb_end_gravity_turn->value();
	qDebug() << "Angle : " << m_dsb_angle->value();

	m_cb_rocket_model->setEnabled(false);
	m_dsb_payload_mass->setEnabled(false);
	m_dsb_start_gravity_turn->setEnabled(false);
	m_dsb_end_gravity_turn->setEnabled(false);
	m_dsb_angle->setEnabled(false);
	m_launch_button->setEnabled(false);

	const auto it
		= std::find_if(m_models.cbegin(), m_models.cend(), [this](const RocketModel& model)
	{ return model.name == m_cb_rocket_model->currentText().toStdString(); });
	Q_ASSERT(it != m_models.cend());
	emit prepareLaunch(
		LaunchParameters{*it,								m_dsb_payload_mass->value(),
						 m_dsb_start_gravity_turn->value(), m_dsb_end_gravity_turn->value(),
						 m_dsb_angle->value()});
}

void ParameterWidget::launchDone()
{
	qDebug() << "ParameterWidget::launchDone()";

	m_cb_rocket_model->setEnabled(true);
	m_dsb_payload_mass->setEnabled(true);
	m_dsb_start_gravity_turn->setEnabled(true);
	m_dsb_end_gravity_turn->setEnabled(true);
	m_dsb_angle->setEnabled(true);
	m_launch_button->setEnabled(true);
}
