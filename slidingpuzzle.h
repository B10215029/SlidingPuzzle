#ifndef SLIDINGPUZZLE_H
#define SLIDINGPUZZLE_H

class SlidingPuzzle
{
public:
	SlidingPuzzle(int row = 4);
	SlidingPuzzle(const SlidingPuzzle &oldPuzzle);
	~SlidingPuzzle();
	SlidingPuzzle& operator=(const SlidingPuzzle &oldPuzzle);
	SlidingPuzzle* operator=(const SlidingPuzzle *oldPuzzle);
	bool operator==(SlidingPuzzle &oldPuzzle) const;
	void reset();
	void shuffle(int step);
	bool checkFinish();
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool moveByPos(int i);
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
