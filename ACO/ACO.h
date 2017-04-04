// General ACO
//#pragma once

#ifndef ACO_H
#define ACO_H

#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

#define FOR(i,n) for(int i=0;i<n;++i)

template<typename T>
class ACO
{
public:
    ACO(int n, float a, float b, float r, float q, int m, float e=0.01f);
    ACO();
    ~ACO();

    typedef struct PathInfo
    {
        float pheromone; // weight
        float visibility; // distance
        T from; // use int to represent state
        T to;
    } PathInfo;

    virtual void start(T from, bool mc=true); // default MONTE_CARLO is true
    virtual vector<PathInfo> shortestPath() { return shortest_path; }

protected:
    int number_of_ants;
    float alpha;
    float beta;
    float pheromone_left_ratio;
    float pheromone_left_per_ant;

    int max_iteration;
    int current_iteration = 0;

    float last_min_path = 0;
    float converge_epsilon;

    bool MONTE_CARLO;

    vector<PathInfo> shortest_path;
    vector<PathInfo> social_influence;

    virtual bool converge(float current_min_path); // min path is general usage (tree depth)
    virtual bool isComplete(T to) = 0; // compare with the complete status
    virtual T evaluate(T from); // depends on social_influence
    virtual vector<T> toStates(T from) = 0; // combine to evaluate (expand tree)
    virtual float visibility(T from, T to) { return 1; } // depends on application, default is 1
    virtual void updatePheromone(vector< vector<PathInfo> > & all_ants_walks);
};

#endif
