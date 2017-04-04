#pragma once

#include "SlidingPuzzleACO.h"

SlidingPuzzleACO::SlidingPuzzleACO(SlidingPuzzle *p):puzzle(p) {
}

bool SlidingPuzzleACO::isComplete(vector<int> to) {
    return true;
//    return puzzle->checkFinish();
}

vector< vector<int> > SlidingPuzzleACO::toStates(vector<int> from) {
    return vector< vector<int> >();
}
