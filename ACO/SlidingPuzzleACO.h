#pragma once

#include "ACO.hpp"
#include "slidingpuzzle.h"

class SlidingPuzzleACO: public ACO<SlidingPuzzle *>
{
public:
	~SlidingPuzzleACO();

protected:
	bool isComplete(SlidingPuzzle *to) override;
	vector<SlidingPuzzle *> toStates(SlidingPuzzle *from) override; // expand all possible states
};
