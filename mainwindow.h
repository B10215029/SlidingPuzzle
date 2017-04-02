#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "slidingpuzzle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	bool eventFilter(QObject *obj, QEvent *event);

private slots:
	void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;
	SlidingPuzzle *puzzle;
};

#endif // MAINWINDOW_H
