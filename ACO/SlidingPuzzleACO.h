#pragma once

#include "ACO.h"
#include "slidingpuzzle.h"

class SlidingPuzzleACO: public ACO< vector<int> >
{
public:
    SlidingPuzzleACO(SlidingPuzzle *p);
    ~SlidingPuzzleACO();

private:
    SlidingPuzzle *puzzle;

protected:
    bool isComplete(vector<int> to) override;
    vector< vector<int> > toStates(vector<int> from) override; // expand all possible states
};
