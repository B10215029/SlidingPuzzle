// General ACO
#pragma once

#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

#define FOR(i,n) for(int i=0;i<n;++i)

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
	void start(T from, bool mc=true); // default MONTE_CARLO is true
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
	T evaluate(T from); // depends on social_influence
	virtual vector<T> toStates(T from) = 0; // combine to evaluate (expand tree)
	float visibility(T from, T to) { return 1; } // depends on application, default is 1
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

	converge_epsilon = e;
}

template<typename T>
void ACO<T>::start(T from, bool mc) {
	MONTE_CARLO = mc;
	float current_min_path = 9999;
	int mini;
	cout << "start aco" << endl;
	while(current_iteration++ < max_iteration && !converge(current_min_path)) {
		cout << "iter: " << current_iteration << endl;

		last_min_path = current_min_path;

		vector< vector<PathInfo> > all_ants_walks;
		FOR(i, number_of_ants) {
			cout << "ant: " << i << endl;
			T *current = new T;
			*current = from;
			cout << "original state: " << from << endl;
			cout << "current state: " << *current << endl;
			cout << "equal? " << ((*from) == (**current)) << endl;
			vector<PathInfo> walk;
			while(!isComplete(walk.size() == 0 ? NULL : walk.back().to)) { // equal to 'best'
				T best = evaluate(*current);
				PathInfo path = {
					.pheromone = pheromone_left_per_ant,
					.visibility = visibility(*current, best),
					.from = *current,
					.to = best
				};
				walk.push_back(path);
			}
			all_ants_walks.push_back(walk);

			if (current_min_path > walk.size()) {
				current_min_path = walk.size();
				mini = i;
			}
		}
		updatePheromone(all_ants_walks);
		shortest_path = all_ants_walks[mini];
	}
}

template<typename T>
bool ACO<T>::converge(float current_min_path) {
	return fabs(last_min_path - current_min_path) <= converge_epsilon;
}

template<typename T>
T ACO<T>::evaluate(T from) {
	cout << "evaluate" << endl;
	vector<T> to = toStates(from);
	printf("expand %d states\n", to.size());
	vector<float> weights;
	float sum = 0, max = 0;
	int maxi;
	FOR(i, to.size()) {
		for(const auto & sipath: social_influence) {
			if (from == sipath.from && to[i] == sipath.to) {
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
	}
	srand(time(NULL));
	if (sum == 0)
		return to[rand() % to.size()];
	else if (MONTE_CARLO) {
		float r = (float) (rand() / (RAND_MAX / sum));
		FOR(i, weights.size()) {
			r -= weights[i];
			if (r < 0)
				return to[i];
		}
	}
	return to[maxi];
}

template<typename T>
void ACO<T>::updatePheromone(vector< vector<PathInfo> > & all_ants_walks) {
	for(auto & sipath: social_influence)
		sipath.pheromone *= pheromone_left_ratio;

	for(const auto & walk: all_ants_walks) {
		for(const auto & path: walk) {
			for(auto & sipath: social_influence) {
				if (sipath.from == path.from && sipath.to == path.to) {
					sipath.pheromone += path.pheromone;
					goto mk;
				}
			}
			social_influence.push_back(path);
			mk:
			continue;
		}
	}
}
