#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "slidingpuzzle.h"
#include "ACO/SlidingPuzzleACO.h"

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
	void on_puzzle_position_click(int i);

	void on_pushButton_2_clicked();

private:
	Ui::MainWindow *ui;
	SlidingPuzzle *puzzle;
    SlidingPuzzleACO *aco;
};

#endif // MAINWINDOW_H
