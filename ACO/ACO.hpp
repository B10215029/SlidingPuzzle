// General ACO

#pragma once

#include <vector>
#include <cmath>
#include <ctime>
using namespace std;
#define FOR(i,n) for(int i=0;i<n;++i)

class ACO
{
public:
	ACO(int n, float a, float b, float r, float q, int m, float e=0.01f);
	~ACO();
	void start(int from, bool mc=true);
	vector<int> shortestPath() { return shortest_path; }

private:
	int number_of_ants;
	float alpha;
	float beta;
	float pheromone_left_ratio;
	float pheromone_left_per_ant;

	int max_iteration;
	int current_iteration = 0;

	float last_min_distance = 0;
	float converge_epsilon;

	vector<int> shortest_path;

	bool MONTE_CARLO;

	typedef struct PathInfo
	{
		float pheromone; // weight
		float visibility; // distance
		int from;
		int to;
	} PathInfo;

	vector<PathInfo> social_influence;

	bool converge(float current_min_distance);
	virtual bool isComplete(vector<PathInfo> walk) = 0; // compare with the complete status
	virtual int evaluate(int from); // depends on social_influence
	virtual vector<int> toStates(int from) = 0; // combine to evaluate
	virtual float visibility(int from, int to) = 0;
	virtual void updatePheromone(vector< vector<PathInfo> > & all_ants_walks);
	float minDistance(vector< vector<PathInfo> > all_ants_walks);
};

ACO::ACO(int n, float a, float b, float r, float q, int m, float e=0.01f) {
	number_of_ants = n;
	alpha = a;
	beta = b;
	pheromone_left_ratio = r;
	pheromone_left_per_ant = q;
	max_iteration = m;

	converge_epsilon = e;
}

void ACO::start(int from, bool mc=true) {
	MONTE_CARLO = mc;
	float current_min_distance = 9999;
	while(current_iteration++ < max_iteration && !converge(current_min_distance)) {
		vector< vector<PathInfo> > all_ants_walks;
		FOR(i, number_of_ants) {
			int current = from;
			vector<PathInfo> walk;
			while(!isComplete(walk)) {
				int best = evaluate(current);
				PathInfo path = {
					pheromone: pheromone_left_per_ant,
					visibility: visibility(current, best),
					from: current,
					to: best
				};
				walk.push_back(path);
			}
			all_ants_walks.push_back(walk);
		}
		updatePheromone(all_ants_walks);
		last_min_distance = current_min_distance;
		current_min_distance = minDistance(all_ants_walks);
	}
}

bool ACO::converge(float current_min_distance) {
	return fabs(last_min_distance - current_min_distance) <= converge_epsilon;
}

int ACO::evaluate(int from) {
	vector<int> to = toStates(from);
	vector<float> weights;
	float sum = 0, max = 0;
	int maxi = 0;
	FOR(i, to.size()) {
		FOR(j, social_influence.size()) {
			if (from == social_influence[j].from && to[i] == social_influence[j].to) {
				float weight = pow(social_influence[j].pheromone, alpha) * pow(social_influence[j].visibility, beta);
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
	if (MONTE_CARLO) {
		srand(time(NULL));
		if (sum == 0) {
			return rand() % to.size();
		}
		else {
			float r = (float) (rand() / (RAND_MAX / sum));
			FOR(i, weights.size()) {
				r -= weights[i];
				if (r < 0)
					return i;
			}
		}
	}
	return maxi;
}

void ACO::updatePheromone(vector< vector<PathInfo> > & all_ants_walks) {
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
		}
	}
}