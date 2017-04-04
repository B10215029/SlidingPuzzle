//#pragma once

#include "ACO.h"

template< typename T >
ACO< T >::ACO(int n, float a, float b, float r, float q, int m, float e) {
    number_of_ants = n;
    alpha = a;
    beta = b;
    pheromone_left_ratio = r;
    pheromone_left_per_ant = q;
    max_iteration = m;

    converge_epsilon = e;
}

template< typename T >
ACO< T >::ACO() {
    number_of_ants = 4;
    alpha = 2;
    beta = 2;
    pheromone_left_ratio = 0.5f;
    pheromone_left_per_ant = 5;
    max_iteration = 100;

    converge_epsilon = 0.01f;
}

template< typename T >
void ACO< T >::start(T from, bool mc) {
    MONTE_CARLO = mc;
    float current_min_path = 9999;
    int mini;
    while(current_iteration++ < max_iteration && !converge(current_min_path)) {

        last_min_path = current_min_path;

        vector< vector<PathInfo> > all_ants_walks;
        FOR(i, number_of_ants) {
            T current = from;
            vector<PathInfo> walk;
            while(!isComplete(walk.back().to)) { // equal to 'best'
                T best = evaluate(current);
                PathInfo path = {
                    .pheromone = pheromone_left_per_ant,
                    .visibility = visibility(current, best),
                    .from =current,
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

template< typename T >
bool ACO< T >::converge(float current_min_path) {
    return fabs(last_min_path - current_min_path) <= converge_epsilon;
}

template< typename T >
T ACO< T >::evaluate(T from) {
    vector< T > to = toStates(from);
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

template< typename T >
void ACO< T >::updatePheromone(vector< vector<PathInfo> > & all_ants_walks) {
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
