#ifndef PARAMETERWIDGET_HPP
#define PARAMETERWIDGET_HPP

#include "launchparameters.hpp"

#include <QWidget>

class QComboBox;
class QDoubleSpinBox;
class QPushButton;

class ParameterWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ParameterWidget(QWidget* parent_ = 0);

private:
	std::vector<RocketModel> m_models;
	QComboBox* m_cb_rocket_model;
	QDoubleSpinBox* m_dsb_payload_mass;
	QDoubleSpinBox* m_dsb_start_gravity_turn;
	QDoubleSpinBox* m_dsb_end_gravity_turn;
	QDoubleSpinBox* m_dsb_angle;
	QPushButton* m_launch_button;

	void loadRocketModels();
	QStringList modelsNames() const;

signals:
	void prepareLaunch(LaunchParameters parameters);

private
slots:
	void launch();

public
slots:
	void launchDone();
};

#endif // PARAMETERWIDGET_HPP
