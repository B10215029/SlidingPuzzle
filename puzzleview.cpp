#include "puzzleview.h"
#include <QPainter>

PuzzleView::PuzzleView(QWidget *parent) : QWidget(parent)
{
	rowSize = colSize = 0;
	index = NULL;
	// test
//	SetSize(4, 4);
//	int a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
//	SetIndex(a);
}

void PuzzleView::SetSize(int row, int col)
{
	rowSize = row;
	colSize = col;
	if (index) {
		delete[] index;
	}
	index = new int[row * col];
}

void PuzzleView::SetIndex(const int *index)
{
	for (int i = 0; i < rowSize * colSize; i++) {
		this->index[i] = index[i];
	}
}

void PuzzleView::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.setPen(Qt::blue);
	painter.setFont(QFont("Arial", 30));
	if (rowSize == 0 || colSize == 0) {
		painter.setBrush(Qt::BrushStyle::Dense4Pattern);
		painter.drawRect(QRect(0, 0, width() - 2, height() - 2));
		painter.drawText(rect(), Qt::AlignCenter, "Sliding Puzzle");
	}
	else {
		int elementWidth = width() / colSize;
		int elementHeight = height() / rowSize;
		QRect r;
		for (int i = 0; i < rowSize * colSize; i++) {
			if (index[i]) {
				r.setRect(elementWidth * (i % colSize), elementHeight * (i / colSize), elementWidth - 2, elementHeight - 2);
				painter.setBrush(Qt::BrushStyle::Dense4Pattern);
				painter.drawRect(r);
				painter.drawText(r, Qt::AlignCenter, QString::number(index[i]));
			}
		}
	}
}
