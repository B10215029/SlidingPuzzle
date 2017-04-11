#ifndef BESTFIRSTSEARCH_H
#define BESTFIRSTSEARCH_H

#include <queue>
#include <vector>
#include <functional>
#include "slidingpuzzle.h"

int SlidingPuzzleHeurestic(const SlidingPuzzle& puzzle);
struct SlidingPuzzleCompare {
	bool operator ()(const SlidingPuzzle& lhs, const SlidingPuzzle& rhs) {return SlidingPuzzleHeurestic(lhs) > SlidingPuzzleHeurestic(rhs);}
};

class BestFirstSearch
{
public:
	BestFirstSearch(SlidingPuzzle& puzzle);

	std::priority_queue<SlidingPuzzle, std::vector<SlidingPuzzle>, SlidingPuzzleCompare> puzzleQueue;
	std::vector<SlidingPuzzle> pastPuzzle;
};

#endif // BESTFIRSTSEARCH_H
