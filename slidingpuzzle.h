#ifndef SLIDINGPUZZLE_H
#define SLIDINGPUZZLE_H

#include <vector>

class SlidingPuzzle
{
public:
	SlidingPuzzle(int row = 4);
	SlidingPuzzle(const SlidingPuzzle &oldPuzzle);
	SlidingPuzzle(const char* fileName);
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
	void RecordStep(char action);
	bool Undo();
	bool Redo();
	bool SaveToFile(const char* fileName);

	int totalStep;

private:
	int XY2Index(int x, int y);
	void Index2XY(int i, int *x, int *y);
	int rowSize;
	int *indexData;
	int zeroPositionX;
	int zeroPositionY;
	bool isRecordStep;
	std::vector<char> step;
};

#endif // SLIDINGPUZZLE_H
