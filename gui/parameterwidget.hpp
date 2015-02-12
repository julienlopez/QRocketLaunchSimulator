#ifndef PARAMETERWIDGET_HPP
#define PARAMETERWIDGET_HPP

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
	QComboBox* m_cb_rocket_model;
	QDoubleSpinBox* m_dsb_start_gravity_turn;
	QDoubleSpinBox* m_dsb_end_gravity_turn;
	QDoubleSpinBox* m_dsb_angle;
	QPushButton* m_launch_button;

	static QStringList loadRocketModels();

signals:

private
slots:
	void launch();
	void launchDone();
};

#endif // PARAMETERWIDGET_HPP
