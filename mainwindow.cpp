#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include "eventlog.h"
#include <fstream>
#include "bestfirstsearch.h"

//static EventLog mlog;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	qApp->installEventFilter(this);
	puzzle = NULL;
	connect(ui->widget, SIGNAL(PositionClick(int)), this, SLOT(on_puzzle_position_click(int)));
	aco = new SlidingPuzzleACO();

//	mlog.write("MainWindow::MainWindow()");
//	mlog.print();
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
		else if (keyEvent->key() == Qt::Key_Z) {
			puzzle->Undo();
		}
		else if (keyEvent->key() == Qt::Key_X) {
			puzzle->Redo();
		}
		else {
			return QObject::eventFilter(obj, event);
		}
		updatePuzzleInfo();
		return true;
	}
	return QObject::eventFilter(obj, event);
}

void MainWindow::updatePuzzleInfo()
{
	ui->label->setText(QString("使用步數: %1").arg(puzzle->totalStep));
	ui->widget->SetIndex(puzzle->getIndexData());
	ui->widget->update();
	if (puzzle->checkFinish())
		ui->statusBar->showMessage(QString("You use %1 step win the game, you are stupid!").arg(puzzle->totalStep));
}

void MainWindow::on_pushButton_clicked()
{
	bool ok;
	if (ui->lineEdit->text().toInt(&ok) <= 1 || !ok) {
		ui->statusBar->showMessage("Why do not you input a number?", 5000);
		return;
	}
	puzzle = new SlidingPuzzle(ui->lineEdit->text().toInt());
	puzzle->shuffle(1000);
	ui->widget->SetSize(puzzle->getSize(), puzzle->getSize());
	updatePuzzleInfo();

//	aco->init(2, 2, 2, 0.5f, 2, 100);
//	aco->start(*puzzle, false);
//	vector<ACO<SlidingPuzzle>::PathInfo> path = aco->shortestPath();
//	printf("sp size: %d\n", path.size());
//	if (path.size())
//		ui->widget->SetIndex(path.back().to.getIndexData());
//	ui->widget->update();
//	if (path.size() && path.back().to.checkFinish())
//		ui->statusBar->showMessage(QString("You use %1 step win the game, you are stupid!").arg(path.back().to.totalStep));
}

void MainWindow::on_puzzle_position_click(int i)
{
	if (puzzle) {
		puzzle->moveByPos(i);
		updatePuzzleInfo();
	}
}

void MainWindow::on_pushButton_2_clicked()
{
	if (puzzle) {
		puzzle->shuffle(ui->lineEdit_2->text().toInt());
		updatePuzzleInfo();
	}
}

void MainWindow::on_pushButton_3_clicked()
{
	if (puzzle) {
		BestFirstSearch bfs(*puzzle);
		updatePuzzleInfo();
	}
}

void MainWindow::on_pushButton_5_clicked()
{
	if (puzzle) {
		puzzle->Undo();
		updatePuzzleInfo();
	}
}

void MainWindow::on_pushButton_4_clicked()
{
	if (puzzle) {
		puzzle->Redo();
		updatePuzzleInfo();
	}
}
