#include "slidingpuzzle.h"
#include <cstdlib>

SlidingPuzzle::SlidingPuzzle(int row)
{
	rowSize = row;
	indexData = new int[rowSize * rowSize];
	reset();
}

void SlidingPuzzle::reset()
{
	for (int i = 0; i < rowSize * rowSize - 1; i++) {
		indexData[i] = i + 1;
	}
	indexData[rowSize * rowSize - 1] = 0;
	zeroPositionX = zeroPositionY = rowSize - 1;
	totalStep = 0;
}

void SlidingPuzzle::shuffle(int step)
{
	bool moveSuccess = false;
	for (int i = 0; i < step; i += moveSuccess?1:0) {
		int randDir = std::rand() % 4;
		if (randDir == 0)
			moveSuccess = moveUp();
		else if (randDir == 1)
			moveSuccess = moveDown();
		else if (randDir == 2)
			moveSuccess = moveLeft();
		else if (randDir == 3)
			moveSuccess = moveRight();
	}
	totalStep = 0;
}

bool SlidingPuzzle::checkFinish()
{
	for (int i = 0; i < rowSize * rowSize - 1; i++) {
		if (indexData[i] != i + 1) {
			return false;
		}
	}
	return true;
}

bool SlidingPuzzle::moveUp()
{
	if (zeroPositionY == rowSize - 1) {
		return false;
	}
	else {
		indexData[XY2Index(zeroPositionX, zeroPositionY)] = indexData[XY2Index(zeroPositionX, zeroPositionY + 1)];
		indexData[XY2Index(zeroPositionX, zeroPositionY + 1)] = 0;
		zeroPositionY++;
		totalStep++;
		return true;
	}
}

bool SlidingPuzzle::moveDown()
{
	if (zeroPositionY == 0) {
		return false;
	}
	else {
		indexData[XY2Index(zeroPositionX, zeroPositionY)] = indexData[XY2Index(zeroPositionX, zeroPositionY - 1)];
		indexData[XY2Index(zeroPositionX, zeroPositionY - 1)] = 0;
		zeroPositionY--;
		totalStep++;
		return true;
	}
}

bool SlidingPuzzle::moveLeft()
{
	if (zeroPositionX == rowSize - 1) {
		return false;
	}
	else {
		indexData[XY2Index(zeroPositionX, zeroPositionY)] = indexData[XY2Index(zeroPositionX + 1, zeroPositionY)];
		indexData[XY2Index(zeroPositionX + 1, zeroPositionY)] = 0;
		zeroPositionX++;
		totalStep++;
		return true;
	}
}

bool SlidingPuzzle::moveRight()
{
	if (zeroPositionX == 0) {
		return false;
	}
	else {
		indexData[XY2Index(zeroPositionX, zeroPositionY)] = indexData[XY2Index(zeroPositionX - 1, zeroPositionY)];
		indexData[XY2Index(zeroPositionX - 1, zeroPositionY)] = 0;
		zeroPositionX--;
		totalStep++;
		return true;
	}
}

bool SlidingPuzzle::moveByPos(int i)
{
	if (i < 0 || i >= rowSize * rowSize) {
		return false;
	}
	else {
		int x, y;
		Index2XY(i, &x, &y);
		if ((abs(zeroPositionX - x) == 1 && (zeroPositionY == y)) || ((zeroPositionX == x) && abs(zeroPositionY - y) == 1)) {
			indexData[XY2Index(zeroPositionX, zeroPositionY)] = indexData[i];
			indexData[i] = 0;
			zeroPositionX = x;
			zeroPositionY = y;
			totalStep++;
			return true;
		}
		else {
			return false;
		}
	}
}

const int* SlidingPuzzle::getIndexData()
{
	return indexData;
}

int SlidingPuzzle::getSize()
{
	return rowSize;
}

int SlidingPuzzle::XY2Index(int x, int y)
{
	return x + y * rowSize;
}

void SlidingPuzzle::Index2XY(int i, int *x, int *y)
{
	*x = i % rowSize;
	*y = i / rowSize;
}
