#ifndef PUZZLEVIEW_H
#define PUZZLEVIEW_H

#include <QWidget>

class PuzzleView : public QWidget
{
	Q_OBJECT
public:
	explicit PuzzleView(QWidget *parent = 0);
	void SetSize(int row, int col);
	void SetIndex(int *index);
protected:
	void paintEvent(QPaintEvent * event);
private:
	int rowSize;
	int colSize;
	int *index;
signals:

public slots:
};

#endif // PUZZLEVIEW_H
