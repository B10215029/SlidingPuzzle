#pragma once

#include "ACO.hpp"
#include "slidingpuzzle.h"

class SlidingPuzzleACO: public ACO<SlidingPuzzle>
{
public:
	~SlidingPuzzleACO();

	void start(SlidingPuzzle from, bool mc=true) override; // default MONTE_CARLO is true

protected:
	bool isComplete(SlidingPuzzle to) override;
	vector<SlidingPuzzle> toStates(SlidingPuzzle from, vector<PathInfo> & walk) override; // expand all possible states
	SlidingPuzzle evaluate(SlidingPuzzle from, vector<PathInfo> & walk) override; // depends on social_influence
	float visibility(SlidingPuzzle from, SlidingPuzzle to) override;
	int heurestic(const SlidingPuzzle & puzzle);
};
