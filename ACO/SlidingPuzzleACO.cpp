//#pragma once

#include "SlidingPuzzleACO.h"

bool SlidingPuzzleACO::isComplete(SlidingPuzzle to) {
	if (&to) {
		if (to.checkFinish())
			cout << "\t\treach complete state" << endl;
		else
			cout << "\t\tNOT reach complete state" << endl;
		return to.checkFinish();
	}
	cout << "\t\tpuzzle is NULL" << endl;
	return false;
}

vector<SlidingPuzzle> SlidingPuzzleACO::toStates(SlidingPuzzle from, vector<PathInfo> walk) {
	vector<SlidingPuzzle> states;
	if (from.moveDown()) {
		if (walk.size()) {
			bool same = false;
			for(const auto & path: walk) {
				if (from == path.from || from == path.to) {
					same = true;
					break;
				}
			}
			if (!same) {
				SlidingPuzzle p = from;
				states.push_back(p);
				cout << "\t\t\tpush state down" << endl;
			}
		}
		else {
			SlidingPuzzle p = from;
			states.push_back(p);
			cout << "\t\t\tpush state down" << endl;
		}
		from.moveUp();
	}
	if (from.moveLeft()) {
		if (walk.size()) {
			bool same = false;
			for(const auto & path: walk) {
				if (from == path.from || from == path.to) {
					same = true;
					break;
				}
			}
			if (!same) {
				SlidingPuzzle p = from;
				states.push_back(p);
				cout << "\t\t\tpush state left" << endl;
			}
		}
		else {
			SlidingPuzzle p = from;
			states.push_back(p);
			cout << "\t\t\tpush state left" << endl;
		}
		from.moveRight();
	}
	if (from.moveRight()) {
		if (walk.size()) {
			bool same = false;
			for(const auto & path: walk) {
				if (from == path.from || from == path.to) {
					same = true;
					break;
				}
			}
			if (!same) {
				SlidingPuzzle p = from;
				states.push_back(p);
				cout << "\t\t\tpush state right" << endl;
			}
		}
		else {
			SlidingPuzzle p = from;
			states.push_back(p);
			cout << "\t\t\tpush state right" << endl;
		}
		from.moveLeft();
	}
	if (from.moveUp()) {
		if (walk.size()) {
			bool same = false;
			for(const auto & path: walk) {
				if (from == path.from || from == path.to) {
					same = true;
					break;
				}
			}
			if (!same) {
				SlidingPuzzle p = from;
				states.push_back(p);
				cout << "\t\t\tpush state up" << endl;
			}
		}
		else {
			SlidingPuzzle p = from;
			states.push_back(p);
			cout << "\t\t\tpush state up" << endl;
		}
		from.moveDown();
	}
	return states;
}
