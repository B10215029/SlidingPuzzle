//#pragma once

#ifndef SPACO_H
#define SPACO_H

#include "ACO.h"
#include "slidingpuzzle.h"

class SlidingPuzzleACO: public ACO< vector<int> >
{
public:
    SlidingPuzzleACO(SlidingPuzzle *p, int n, float a, float b, float r, float q, int m, float e=0.01f);
    SlidingPuzzleACO(SlidingPuzzle *p);
    ~SlidingPuzzleACO();

private:
    SlidingPuzzle *puzzle;

protected:
    bool isComplete(vector<int> to) override;
    vector< vector<int> > toStates(vector<int> from) override; // expand all possible states
};

#endif
