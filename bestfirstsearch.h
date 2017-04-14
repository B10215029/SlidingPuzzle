#ifndef BESTFIRSTSEARCH_H
#define BESTFIRSTSEARCH_H

#include <queue>
#include <vector>
#include <functional>
#include "slidingpuzzle.h"

class BestFirstSearch
{
public:
	BestFirstSearch(SlidingPuzzle& puzzle, double hw = 10, double gw = 1);

	std::priority_queue<SlidingPuzzle, std::vector<SlidingPuzzle>, std::function<bool(const SlidingPuzzle&, const SlidingPuzzle&)>> puzzleQueue;
	std::vector<SlidingPuzzle> pastPuzzle;
	double hWeight;
	double gWeight;
	bool SlidingPuzzleCompare(const SlidingPuzzle& lhs, const SlidingPuzzle& rhs) const;
	double SlidingPuzzleHeurestic(const SlidingPuzzle& puzzle) const;
};

#endif // BESTFIRSTSEARCH_H
