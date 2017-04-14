#include "bestfirstsearch.h"
#include <iostream>
#include <algorithm>

BestFirstSearch::BestFirstSearch(SlidingPuzzle &puzzle, double hw, double gw) : hWeight(hw), gWeight(gw)
{
	puzzleQueue = std::priority_queue<SlidingPuzzle, std::vector<SlidingPuzzle>, std::function<bool(const SlidingPuzzle&, const SlidingPuzzle&)>>(std::bind(&BestFirstSearch::SlidingPuzzleCompare, *this, std::placeholders::_1, std::placeholders::_2));
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
		if (!(i++%1000)) {
			std::cout << SlidingPuzzleHeurestic(pastPuzzle.back()) << ", " << "state:" << i << std::endl;
		}
	}
	std::cout << SlidingPuzzleHeurestic(puzzle) << ", " << "state:" << i << std::endl;
}

bool BestFirstSearch::SlidingPuzzleCompare(const SlidingPuzzle& lhs, const SlidingPuzzle& rhs) const
{
	return SlidingPuzzleHeurestic(lhs) > SlidingPuzzleHeurestic(rhs);
}

double BestFirstSearch::SlidingPuzzleHeurestic(const SlidingPuzzle& puzzle) const
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
	return manhattanDistance * hWeight + puzzle.totalStep * gWeight;
}
