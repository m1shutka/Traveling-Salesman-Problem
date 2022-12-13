#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "tsp.h"
#include <chrono>
#include <random>
#include <numeric>

Graph random_graph(int size, int& x)
{
	Graph g;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(30, 80);
	int vertex = 0;
	while (vertex < size - 1)
	{
		g.add_edge(vertex, vertex + 1, distribution(generator));
		vertex++;
	}
	g.add_edge(0, size - 1, distribution(generator));
	vertex = 0;
	while (vertex < size)
	{
		while (g.get_adjacent_vertices(vertex).size() < size - 1)
		{
			int rand_vert = rand() % (size);
			if (vertex != rand_vert and rand_vert < size) {
				g.add_edge(vertex, rand_vert, distribution(generator));
			}
		}
		vertex++;
	}
	x = rand() % (size - 1);
	return g;
}

void view(const vector<int>& result)
{
	for (int i = 0; i < result.size(); ++i)
	{
		cout << result[i];
	}
	cout << endl;
}

double full_enumeration_time(const Graph& g, int x, vector<int>& result)
{
	auto t1 = std::chrono::high_resolution_clock::now();
	result = tsp_full_enumeration(g, x);
	auto t2 = std::chrono::high_resolution_clock::now();
	double time = std::chrono::duration<double>(t2 - t1).count();
	return time;
}

double bnb_time(const Graph& g, int x, vector<int>& result)
{
	auto t1 = std::chrono::high_resolution_clock::now();
	result = tsp_bnb(g, x);
	auto t2 = std::chrono::high_resolution_clock::now();
	double time = std::chrono::duration<double>(t2 - t1).count();
	return time;
}

double greedy_time(const Graph& g, int x, vector<int>& result)
{
	auto t1 = std::chrono::high_resolution_clock::now();
	result = tsp_greedy(g, x);
	auto t2 = std::chrono::high_resolution_clock::now();
	double time = std::chrono::duration<double>(t2 - t1).count();
	return time;
}

double tsp_time(const Graph& g, int x, vector<int>& result)
{
	auto t1 = std::chrono::high_resolution_clock::now();
	result = tsp_ls(g, x);
	auto t2 = std::chrono::high_resolution_clock::now();
	double time = std::chrono::duration<double>(t2 - t1).count();
	return time;
}


void time(int size)
{
	int x;
	Graph g = random_graph(size, x);
	vector<int> result;
	//double time = full_enumeration_time(g, x, result);
	//cout << "enum time = " << time << ", result length = " << length(g, result) << endl;;
	//view(result);
	auto time = bnb_time(g, x, result);
	cout << "bnb time = " << time << ", result length = " << length(g, result) << endl;
	//view(result);
	time = greedy_time(g, x, result);
	cout << "greedy time = " << time << ", result length = " << length(g, result) << endl;
	//view(result);
	time = tsp_time(g, x, result);
	cout << "tsp time = " << time << ", result length = " << length(g, result) << endl;
	//view(result);
}

int main(int argc, char* argv[]) 
{
    setlocale(LC_ALL, "ru");
	time(12);
    int result4 = Catch::Session().run(argc, argv);
    return result4;
}