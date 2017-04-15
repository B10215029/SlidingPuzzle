// General ACO
#pragma once

#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

#define FOR(i, n) for (int i=0; i < (int)n; ++i)

template<typename T>
class ACO
{
public:
	~ACO();

	typedef struct PathInfo
	{
		float pheromone; // weight
		float visibility; // distance
		T from; // use int to represent state
		T to;
	} PathInfo;

	void init(int n, float a, float b, float r, float q, int m, float e=0.01f);
	virtual void start(T from, bool mc=true); // default MONTE_CARLO is true
	vector<PathInfo> shortestPath() { return shortest_path; }

protected:
	int number_of_ants = 4;
	float alpha = 2;
	float beta = 2;
	float pheromone_left_ratio = 0.5f;
	float pheromone_left_per_ant = 5;

	int max_iteration = 100;
	int current_iteration = 0;

	float last_min_path = 0;
	float converge_epsilon;

	bool MONTE_CARLO;

	vector<PathInfo> shortest_path;
	vector<PathInfo> social_influence;

	bool converge(float current_min_path); // min path is general usage (tree depth)
	virtual bool isComplete(T to) = 0; // compare with the complete status
	virtual T evaluate(T from, vector<PathInfo> & walk); // depends on social_influence
	virtual vector<T> toStates(T from, vector<PathInfo> & walk) = 0; // combine to evaluate (expand tree)
	virtual float visibility(T from, T to) { return 1; } // depends on application, default is 1
	void updatePheromone(vector< vector<PathInfo> > & all_ants_walks);
};

template<typename T>
void ACO<T>::init(int n, float a, float b, float r, float q, int m, float e) {
	number_of_ants = n;
	alpha = a;
	beta = b;
	pheromone_left_ratio = r;
	pheromone_left_per_ant = q;
	max_iteration = m;
	current_iteration = 0;
	converge_epsilon = e;
	last_min_path = 0;
	shortest_path.clear();
	social_influence.clear();
}

template<typename T>
void ACO<T>::start(T from, bool mc) {
	MONTE_CARLO = mc;
	float current_min_path = 9999;

	while(current_iteration++ < max_iteration && !converge(current_min_path)) {
		cout << "iter: " << current_iteration << endl;
		cout.flush();
		last_min_path = current_min_path;

		vector< vector<PathInfo> > all_ants_walks;
		#pragma omp parallel for
		FOR (i, number_of_ants) {
			bool bad_path = false;
			cout << "\tant: " << i + 1 << endl;
			cout.flush();
			T current = from;
			vector<PathInfo> walk;
			while (!isComplete(walk.size() == 0 ? from : walk.back().to)) {
				T best = evaluate(current, walk);
				if (best == NULL) {
					if (i == number_of_ants - 1) {
						cout << "\tredo: " << i + 1 << endl;
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
			cout << "\t[walk size] " << walk.size() << endl;
			cout.flush();
			if (walk.size() && !bad_path) {
				all_ants_walks.push_back(walk);
				if (current_min_path > walk.size()) {
					current_min_path = walk.size();
					shortest_path = walk;
				}
			}
		}
		updatePheromone(all_ants_walks);
	}
}

template<typename T>
bool ACO<T>::converge(float current_min_path) {
	return fabs(last_min_path - current_min_path) <= converge_epsilon;
}

template<typename T>
T ACO<T>::evaluate(T from, vector<PathInfo> & walk) {
	vector<T> to = toStates(from, walk);
	vector<float> weights;
	float sum = 0, max = -9999;

	FOR (i, to.size()) {
		bool find_social = false;
		for(const auto & sipath: social_influence) {
			if (from == sipath.from && to[i] == sipath.to) {
				find_social = true;
				float weight = pow(sipath.pheromone, alpha) * pow(sipath.visibility, beta);
				weights.push_back(weight);
				sum += weight;
				if (weight > max)
					max = weight;
				break;
			}
		}
		if (!find_social) {
			float weight = pow(visibility(from, to[i]), beta);
			weights.push_back(weight);
			sum += weight;
			if (weight > max)
				max = weight;
		}
	}

	if (to.size() == 0)
		return NULL;
	srand(time(NULL));
	if (MONTE_CARLO) {
		float r = (float)rand() / (float)(RAND_MAX / sum);
		FOR (i, weights.size()) {
			r -= weights[i];
			if (r < 0)
				return to[i];
		}
	}
	vector<T> to_max;
	FOR (i, weights.size())
		if (weights[i] == max)
			to_max.push_back(to[i]);
	return to_max[rand() % to_max.size()];
}

template<typename T>
void ACO<T>::updatePheromone(vector< vector<PathInfo> > & all_ants_walks) {
	FOR (i, social_influence.size())
		social_influence[i].pheromone *= pheromone_left_ratio;

	for (const auto & walk: all_ants_walks) {
		for (const auto & path: walk) {
			FOR (i, social_influence.size()) {
				if (social_influence[i].from == path.from && social_influence[i].to == path.to) {
					social_influence[i].pheromone += path.pheromone / walk.size();
					goto mk;
				}
			}
			social_influence.push_back(path);
			mk:
			continue;
		}
	}

	FOR (i, social_influence.size()) {
		if (social_influence[i].pheromone < 0 || social_influence[i].pheromone < converge_epsilon) {
			social_influence.erase(social_influence.begin() + i);
			++i;
		}
	}
}
