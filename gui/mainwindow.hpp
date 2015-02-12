#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent_ = 0);
	virtual ~MainWindow() = default;

signals:

public
slots:
};

#endif // MAINWINDOW_HPP
