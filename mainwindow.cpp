#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	qApp->installEventFilter(this);
	puzzle = NULL;
}

MainWindow::~MainWindow()
{
	delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (puzzle && event->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if (keyEvent->key() == Qt::Key_Up) {
			puzzle->moveUp();
		}
		else if (keyEvent->key() == Qt::Key_Down) {
			puzzle->moveDown();
		}
		else if (keyEvent->key() == Qt::Key_Left) {
			puzzle->moveLeft();
		}
		else if (keyEvent->key() == Qt::Key_Right) {
			puzzle->moveRight();
		}
		else {
			return QObject::eventFilter(obj, event);
		}
		ui->label->setText(QString("使用步數: %1").arg(puzzle->totalStep));
		ui->widget->SetIndex(puzzle->getIndexData());
		ui->widget->update();
		return true;
	}
	return QObject::eventFilter(obj, event);
}

void MainWindow::on_pushButton_clicked()
{
	puzzle = new SlidingPuzzle(ui->lineEdit->text().toInt());
	puzzle->shuffle(100);
	ui->label->setText(QString("使用步數: %1").arg(puzzle->totalStep));
	ui->widget->SetSize(puzzle->getSize(), puzzle->getSize());
	ui->widget->SetIndex(puzzle->getIndexData());
	ui->widget->update();
}
