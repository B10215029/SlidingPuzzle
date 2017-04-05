//#pragma once

#include "SlidingPuzzleACO.h"

bool SlidingPuzzleACO::isComplete(SlidingPuzzle *to) {
	if (to) {
		if (to->checkFinish())
			cout << "reach complete state" << endl;
		else
			cout << "NOT reach complete state" << endl;
		return to->checkFinish();
	}
	cout << "puzzle is NULL" << endl;
	return false;
}

vector<SlidingPuzzle *> SlidingPuzzleACO::toStates(SlidingPuzzle *from) {
	vector<SlidingPuzzle *> states;
	if (from->moveDown()) {
		SlidingPuzzle p = *from;
		states.push_back(&p);
		from->moveUp();
		cout << "push state down" << endl;
	}
	if (from->moveLeft()) {
		SlidingPuzzle p = *from;
		states.push_back(&p);
		from->moveRight();
		cout << "push state left" << endl;
	}
	if (from->moveRight()) {
		SlidingPuzzle p = *from;
		states.push_back(&p);
		from->moveLeft();
		cout << "push state right" << endl;
	}
	if (from->moveUp()) {
		SlidingPuzzle p = *from;
		states.push_back(&p);
		from->moveDown();
		cout << "push state up" << endl;
	}
	return states;
}
