// General ACO
#pragma once

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
