#ifndef SLIDINGPUZZLE_H
#define SLIDINGPUZZLE_H

class SlidingPuzzle
{
public:
	SlidingPuzzle(int row = 4);
	SlidingPuzzle(const SlidingPuzzle &oldPuzzle);
	~SlidingPuzzle();
	SlidingPuzzle& operator=(const SlidingPuzzle &oldPuzzle);
	bool operator==(const SlidingPuzzle &oldPuzzle) const;
	bool operator!=(const SlidingPuzzle &oldPuzzle) const;
	void reset();
	void shuffle(int step);
	bool checkFinish() const;
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool moveByPos(int i);
	const int *getIndexData() const;
	int getSize() const;

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
