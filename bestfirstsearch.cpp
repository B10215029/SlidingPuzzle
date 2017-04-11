#include "bestfirstsearch.h"
#include <iostream>

BestFirstSearch::BestFirstSearch(SlidingPuzzle &puzzle)
{
	puzzleQueue.push(puzzle);

	int i = 0;
	while (true) {
		if (puzzleQueue.empty()) {
			std::cout << "ERROR: No Answer" << std::endl;
			break;
		}
		else {
			pastPuzzle.push_back(puzzleQueue.top());
			puzzleQueue.pop();
		}
//		std::cout << pastPuzzle.back().getIndexData()[0] << pastPuzzle.back().getIndexData()[1] << pastPuzzle.back().getIndexData()[2] << pastPuzzle.back().getIndexData()[3] << std::endl;
		std::cout << SlidingPuzzleHeurestic(pastPuzzle.back()) << ": ";
		if (pastPuzzle.back().checkFinish()) {
			puzzle = pastPuzzle.back();
			break;
		}
		SlidingPuzzle puzzleUp(pastPuzzle.back());
		if(puzzleUp.moveUp() && std::find(pastPuzzle.begin(), pastPuzzle.end(), puzzleUp) == pastPuzzle.end()) {
			puzzleQueue.push(puzzleUp);
		}
		SlidingPuzzle puzzleDown(pastPuzzle.back());
		if(puzzleDown.moveDown() && std::find(pastPuzzle.begin(), pastPuzzle.end(), puzzleDown) == pastPuzzle.end()) {
			puzzleQueue.push(puzzleDown);
		}
		SlidingPuzzle puzzleLeft(pastPuzzle.back());
		if(puzzleLeft.moveLeft() && std::find(pastPuzzle.begin(), pastPuzzle.end(), puzzleLeft) == pastPuzzle.end()) {
			puzzleQueue.push(puzzleLeft);
		}
		SlidingPuzzle puzzleRight(pastPuzzle.back());
		if(puzzleRight.moveRight() && std::find(pastPuzzle.begin(), pastPuzzle.end(), puzzleRight) == pastPuzzle.end()) {
			puzzleQueue.push(puzzleRight);
		}
		std::cout << "find:" << i++ << std::endl;
	}
	std::cout << SlidingPuzzleHeurestic(puzzle) << std::endl;
}

int SlidingPuzzleHeurestic(const SlidingPuzzle& puzzle)
{
	const int* indexData = puzzle.getIndexData();
	int puzzleSize = puzzle.getSize();
	int manhattanDistance = 0;
	for (int y = 0; y < puzzleSize; y++) {
		for (int x = 0; x < puzzleSize; x++) {
			int puzzleValue = indexData[x + y * puzzleSize];
			if (puzzleValue == 0)
				continue;
			manhattanDistance += abs((puzzleValue - 1) % puzzleSize - x);
			manhattanDistance += abs((puzzleValue - 1) / puzzleSize - y);
		}
	}
	return manhattanDistance;
}
