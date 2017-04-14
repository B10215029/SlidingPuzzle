#include "SlidingPuzzleACO.h"
#include <algorithm>

void SlidingPuzzleACO::start(SlidingPuzzle from, bool mc)
{
	MONTE_CARLO = mc;
	float current_min_path = 9999;

	while(current_iteration++ < max_iteration && !converge(current_min_path)) {
		cout << "iter: " << current_iteration << endl;
		cout.flush();
		last_min_path = current_min_path;

		vector< vector<PathInfo> > all_ants_walks;
//		#pragma omp parallel for
		FOR (i, number_of_ants) {
			bool bad_path = false;
			cout << "\tant: " << i + 1 << ",";
			cout.flush();
			SlidingPuzzle current = from;
			vector<PathInfo> walk;
			while (!isComplete(walk.size() == 0 ? from : walk.back().to)) {
				SlidingPuzzle best = evaluate(current, walk);
				if (best == NULL) {
					if (i == number_of_ants - 1) {
						cout << "\tredo: " << i + 1 << "\t";
						cout.flush();

						bad_path = false;
						current = from;
						walk.clear();
						continue;
					}
					bad_path = true;
					break;
				}
				PathInfo path = {
					pheromone_left_per_ant,
					visibility(current, best),
					current,
					best
				};
				current = best;
				walk.push_back(path);
			}
			cout << "\t[walk size]" << walk.size() << endl;
			cout.flush();
			if (walk.size()) {
				if (bad_path) {
//					FOR (k, walk.size()) {
//						walk[k].pheromone = - walk[k].pheromone / 2;
//					}
//					all_ants_walks.push_back(walk);
				}
				else
					all_ants_walks.push_back(walk);
			}
//			printf("\t\tall_ants_walks size: %d\n", (int)all_ants_walks.size());

			if (current_min_path > walk.size() && !bad_path) {
				current_min_path = walk.size();
				shortest_path = walk;
			}
		}
		updatePheromone(all_ants_walks);
	}
}

bool SlidingPuzzleACO::isComplete(SlidingPuzzle to)
{
	if (to != NULL) {
		if (to.checkFinish())
			cout << "\t\treach complete state" << endl;
			cout.flush();
//		else
//			cout << "\t\tNOT reach complete state" << endl;
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

SlidingPuzzle SlidingPuzzleACO::evaluate(SlidingPuzzle from, vector<PathInfo> & walk)
{
	vector<SlidingPuzzle> to = toStates(from, walk);
	vector<float> weights;
	float sum = 0, max = -9999;
	int maxi;
	FOR (i, to.size()) {
		bool find_social = false;
		for(const auto & sipath: social_influence) {
			if (from == sipath.from && to[i] == sipath.to) {
				find_social = true;
				float weight = pow(sipath.pheromone, alpha) * pow(sipath.visibility, beta);
				weights.push_back(weight);
				sum += weight;
				if (weight > max) {
					max = weight;
					maxi = i;
				}
				break;
			}
		}
		if (!find_social) {
			float weight = pow(visibility(from, to[i]), beta);
			weights.push_back(weight);
			sum += weight;
			if (weight > max) {
				max = weight;
				maxi = i;
			}
		}
	}
	if (to.size() == 0)
		return NULL;
	srand(time(NULL));
	if (sum == 0)
		return to[rand() % to.size()];
	else if (MONTE_CARLO) {
		float r = (float) (rand() / (RAND_MAX / sum));
		FOR (i, weights.size()) {
			r -= weights[i];
			if (r < 0)
				return to[i];
		}
	}
	vector<SlidingPuzzle> to_max;
	FOR (i, weights.size()) {
		if (weights[i] == max)
			to_max.push_back(to[i]);
	}
	return to_max[rand() % to_max.size()];
//	return to[maxi];
}

float SlidingPuzzleACO::visibility(SlidingPuzzle from, SlidingPuzzle to)
{
	return heurestic(from) / heurestic(to);
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
	return manhattanDistance * 10 + puzzle.totalStep * 1;
}
