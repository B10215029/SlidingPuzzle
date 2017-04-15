#include "slidingpuzzle.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

SlidingPuzzle::SlidingPuzzle(int row) : rowSize(row), isRecordStep(true)
{
	indexData = new int[rowSize * rowSize];
	reset();
}

SlidingPuzzle::SlidingPuzzle(const SlidingPuzzle &oldPuzzle)
{
//	printf("%x constructor copy from %x\n", this, oldPuzzle);
	*this = oldPuzzle;
}

SlidingPuzzle::SlidingPuzzle(const char* fileName)
{
	std::ifstream file(fileName);
	if (!file) {
		*this = SlidingPuzzle(3);
	}
	file >> rowSize >> isRecordStep >> totalStep;
	file >> zeroPositionX >> zeroPositionY;
	indexData = new int[rowSize * rowSize];
	for (int i = 0; i < rowSize * rowSize; i++)
		file >> indexData[i];
	int stepSize, a;
	file >> stepSize;
	step.clear();
	for (int i = 0; i < stepSize; i++) {
		file >> a;
		step.push_back(a);
	}
	file.close();
}

SlidingPuzzle::~SlidingPuzzle()
{
	delete[] indexData;
}

SlidingPuzzle& SlidingPuzzle::operator=(const SlidingPuzzle &oldPuzzle)
{
//	printf("%x assign to %x\n", oldPuzzle, this);
	this->rowSize = oldPuzzle.rowSize;
	this->zeroPositionX = oldPuzzle.zeroPositionX;
	this->zeroPositionY = oldPuzzle.zeroPositionY;
	this->totalStep = oldPuzzle.totalStep;
	this->indexData = new int[rowSize * rowSize];
	for (int i = 0; i < rowSize * rowSize; i++) {
		this->indexData[i] = oldPuzzle.indexData[i];
	}
	this->isRecordStep = oldPuzzle.isRecordStep;
	this->step = oldPuzzle.step;
	return *this;
}

bool SlidingPuzzle::operator==(const SlidingPuzzle &oldPuzzle) const
{
//	printf("== overload\n");
	if (this->rowSize == oldPuzzle.rowSize &&
			this->zeroPositionX == oldPuzzle.zeroPositionX &&
			this->zeroPositionY == oldPuzzle.zeroPositionY) {
		for (int i = 0; i < rowSize * rowSize; i++)
			if (this->indexData[i] != oldPuzzle.indexData[i])
				return false;
	}
	else
		return false;
	return true;
}

bool SlidingPuzzle::operator!=(const SlidingPuzzle &oldPuzzle) const
{
	return !(*this == oldPuzzle);
}

void SlidingPuzzle::reset() // reset to complete state
{
	for (int i = 0; i < rowSize * rowSize - 1; i++) {
		indexData[i] = i + 1;
	}
	indexData[rowSize * rowSize - 1] = 0;
	zeroPositionX = zeroPositionY = rowSize - 1;
	totalStep = 0;
	step.clear();
}

void SlidingPuzzle::shuffle(int step)
{
	bool moveSuccess = false;
	bool isReco = isRecordStep;
	isRecordStep = false;
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
	isRecordStep = isReco;
	totalStep = 0;
	this->step.clear();
}

bool SlidingPuzzle::checkFinish() const
{
	if ((zeroPositionX != rowSize - 1) && (zeroPositionY != rowSize - 1))
		return false;
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
		RecordStep(0);
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
		RecordStep(1);
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
		RecordStep(2);
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
		RecordStep(3);
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
			int action = (zeroPositionX - x) * (zeroPositionX - x) * 2 + ((zeroPositionX - x) + 1) / 2 + ((zeroPositionY - y) + 1) / 2;
			std::cout << "action:" << action <<std::endl;
			zeroPositionX = x;
			zeroPositionY = y;
			totalStep++;
			RecordStep(action);
			return true;
		}
		else {
			return false;
		}
	}
}

const int* SlidingPuzzle::getIndexData() const
{
	return indexData;
}

int SlidingPuzzle::getSize() const
{
	return rowSize;
}

void SlidingPuzzle::RecordStep(char action)
{
	if (!isRecordStep)
		return;
	if (step.size() == totalStep - 1) {
		step.push_back(action);
	}
	else {
		step.erase(step.begin() + totalStep, step.end());
		step.push_back(action);
	}
}

bool SlidingPuzzle::Undo()
{
	if (!isRecordStep || totalStep == 0)
		return false;
	isRecordStep = false;
	if (step[totalStep - 1] == 0)
		moveDown();
	else if (step[totalStep - 1] == 1)
		moveUp();
	else if (step[totalStep - 1] == 2)
		moveRight();
	else if (step[totalStep - 1] == 3)
		moveLeft();
	isRecordStep = true;
	totalStep -= 2;
}

bool SlidingPuzzle::Redo()
{
	if (!isRecordStep || totalStep == step.size())
		return false;
	isRecordStep = false;
	if (step[totalStep] == 0)
		moveUp();
	else if (step[totalStep] == 1)
		moveDown();
	else if (step[totalStep] == 2)
		moveLeft();
	else if (step[totalStep] == 3)
		moveRight();
	isRecordStep = true;
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

bool SlidingPuzzle::SaveToFile(const char* fileName)
{
	std::ofstream file(fileName);
	if (!file) {
		return false;
	}
	file << rowSize << " " << isRecordStep << " " << totalStep << std::endl;
	file << zeroPositionX << " " << zeroPositionY << std::endl;
	for (int i = 0; i < rowSize * rowSize; i++)
		file << indexData[i] << " ";
	file << std::endl << step.size();
	for (int i = 0; i < step.size(); i++) {
		file << ' ' << (int)step[i];
	}
	file << std::endl;
	file.close();
}
