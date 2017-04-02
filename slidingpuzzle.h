#ifndef SLIDINGPUZZLE_H
#define SLIDINGPUZZLE_H


class SlidingPuzzle
{
public:
	SlidingPuzzle(int row = 4);
	void reset();
	void shuffle(int step);
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	const int *getIndexData();
	int getSize();

	int totalStep;

private:
	int XY2Index(int x, int y);
	void Index2XY(int i, int *x, int *y);
	int rowSize;
	int *indexData;
	int zeroPositionX;
	int zeroPositionY;
};

#endif // SLIDINGPUZZLE_H
