#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include "eventlog.h"
#include <fstream>
#include "bestfirstsearch.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	qApp->installEventFilter(this);
	puzzle = NULL;
	connect(ui->widget, SIGNAL(PositionClick(int)), this, SLOT(on_puzzle_position_click(int)));
	aco = new SlidingPuzzleACO();
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
		ui->statusBar->showMessage(QString("You use %1 step win the game, you are stupid!").arg(puzzle->totalStep), 5000);
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
	ui->statusBar->showMessage("New game~", 5000);
	updatePuzzleInfo();
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
		aco->init(6, 2, 3, 0.5f, 3, 100);
		aco->start(*puzzle, false);
		vector<ACO<SlidingPuzzle>::PathInfo> path = aco->shortestPath();
		cout << "sp size: " << path.size() << endl;
		cout.flush();
		if (path.size())
			*puzzle = path.back().to;
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

void MainWindow::on_pushButton_6_clicked()
{
	if (puzzle) {
		bool ok;
		if (ui->lineEdit_3->text().toInt(&ok) < 0 || !ok) {
			ui->statusBar->showMessage("Why do not you input a number?", 5000);
			return;
		}
		BestFirstSearch bfs(*puzzle, ui->lineEdit->text().toInt());
		updatePuzzleInfo();
	}
}

void MainWindow::on_actionSave_Puzzle_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save Puzzle");
	if (puzzle) {
		puzzle->SaveToFile(fileName.toLatin1());
	}
}

void MainWindow::on_actionOpen_Puzzle_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open Puzzle");
	puzzle = new SlidingPuzzle((const char*)fileName.toLatin1());
	ui->widget->SetSize(puzzle->getSize(), puzzle->getSize());
	updatePuzzleInfo();
}
