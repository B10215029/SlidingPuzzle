#pragma once

#include "ACO.hpp"
#include "slidingpuzzle.h"

class SlidingPuzzleACO: public ACO<SlidingPuzzle>
{
public:
	~SlidingPuzzleACO();

protected:
	bool isComplete(SlidingPuzzle to) override;
	vector<SlidingPuzzle> toStates(SlidingPuzzle from, vector<PathInfo> & walk) override; // expand all possible states
	float visibility(SlidingPuzzle from, SlidingPuzzle to) override;
	int heurestic(const SlidingPuzzle & puzzle);
};
