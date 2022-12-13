#pragma once
#include "graph.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> tsp_full_enumeration(const Graph& g, int start_vertex);
vector<int> tsp_greedy(const Graph& g, int start_vertex);
vector<int> tsp_bnb(const Graph& g, int start_vertex);
double length(const Graph& g, const vector<int>& path);
vector<int> tsp(const Graph& graph, int start_vertex);
