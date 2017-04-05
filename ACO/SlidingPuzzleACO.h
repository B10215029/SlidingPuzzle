#pragma once

#include "ACO.hpp"
#include "slidingpuzzle.h"

class SlidingPuzzleACO: public ACO<SlidingPuzzle>
{
public:
	~SlidingPuzzleACO();

protected:
	bool isComplete(SlidingPuzzle to) override;
	// expand all possible states
	vector<SlidingPuzzle> toStates(SlidingPuzzle from, vector<PathInfo> walk) override;
};
