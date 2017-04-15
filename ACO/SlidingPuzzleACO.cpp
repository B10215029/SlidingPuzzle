#include "SlidingPuzzleACO.h"
#include <algorithm>

bool SlidingPuzzleACO::isComplete(SlidingPuzzle to)
{
	if (to != NULL) {
		if (to.checkFinish())
			cout << "\t\treach complete state" << endl;
			cout.flush();
		return to.checkFinish();
	}
	cout << "\t\tpuzzle is NULL" << endl;
	cout.flush();
	return false;
}

vector<SlidingPuzzle> SlidingPuzzleACO::toStates(SlidingPuzzle from, vector<PathInfo> & walk)
{
	vector<SlidingPuzzle> past_state;
	for (const auto & path: walk)
		past_state.push_back(path.from);
	vector<SlidingPuzzle> states;

	SlidingPuzzle pd = from;
	if (pd.moveDown()) {
		if (walk.size() == 0 || find(past_state.begin(), past_state.end(), pd) == past_state.end())
			states.push_back(pd);
	}
	SlidingPuzzle pl = from;
	if (pl.moveLeft()) {
		if (walk.size() == 0 || find(past_state.begin(), past_state.end(), pl) == past_state.end())
			states.push_back(pl);
	}
	SlidingPuzzle pr = from;
	if (pr.moveRight()) {
		if (walk.size() == 0 || find(past_state.begin(), past_state.end(), pr) == past_state.end())
			states.push_back(pr);
	}
	SlidingPuzzle pu = from;
	if (pu.moveUp()) {
		if (walk.size() == 0 || find(past_state.begin(), past_state.end(), pu) == past_state.end())
			states.push_back(pu);
	}
	return states;
}

float SlidingPuzzleACO::visibility(SlidingPuzzle from, SlidingPuzzle to)
{
	return 10 * heurestic(from) / heurestic(to);
}

int SlidingPuzzleACO::heurestic(const SlidingPuzzle & puzzle)
{
	const int *indexData = puzzle.getIndexData();
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
	return manhattanDistance * 5 + puzzle.totalStep * 1;
}
