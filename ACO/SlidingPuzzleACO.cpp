//#pragma once

#include "SlidingPuzzleACO.h"

SlidingPuzzleACO::SlidingPuzzleACO(SlidingPuzzle *p,
                                   int n, float a, float b, float r, float q, int m, float e)
    :puzzle(p), ACO< vector<int> >(n, a, b, r, q, m, e) {}

SlidingPuzzleACO::SlidingPuzzleACO(SlidingPuzzle *p)
    :puzzle(p), ACO< vector<int> >() {}

bool SlidingPuzzleACO::isComplete(vector<int> to) {
    return true;
//    return puzzle->checkFinish();
}

vector< vector<int> > SlidingPuzzleACO::toStates(vector<int> from) {
    return vector< vector<int> >();
}
