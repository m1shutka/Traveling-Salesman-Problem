#include "tsp.h"
using namespace std;
const double N = double(INFINITY);
const int H = 1000000;

double length(const Graph& g, const vector<int>& path)
{
    if (path.size() <= 1) {
        return N;
    }
    double result = 0;
    for (auto i = 0; i < path.size() - 1; ++i)
    {
        result += g.edge_weight(path[i], path[i + 1]);
    }
    result += g.edge_weight(path[0], path[path.size() - 1]);
    return result;
}

vector<int> MinPath(const Graph& g, const vector<int>& BestPath, const vector<int>& visited)
{
    double result1 = length(g, BestPath);
    double result2 = length(g, visited);
   
    if (result1 <= result2 and BestPath.size() == g.get_vertices().size()) {
        return BestPath;
    }
    else {
        return visited;
    }
}

double LowerBound(const Graph& g, vector<int> visited)
{
    double answer = 0;
    for (auto i = 0; i < g.get_vertices().size(); ++i)
    {
        auto u = g.get_adjacent_edges(i);
        vector <pair<int, double>> weights;
        
        for (auto j = 0; j < visited.size(); ++j)
        {
            for (auto k = 0; k < u.size(); ++k)
            {
                if (i == visited[j]) {
                    if (j == 0) {
                        if (visited[j + 1] == u[k].first) {
                            weights.push_back(u[k]);
                        }
                    }
                    else if (j < visited.size() - 1) {
                        if (visited[j + 1] == u[k].first or visited[j - 1] == u[k].first) {
                            weights.push_back(u[k]);
                        }
                    }
                    else if (j == visited.size() - 1) {
                        if (visited[j - 1] == u[k].first) {
                            weights.push_back(u[k]);
                        }
                    }
                }
            }
        }
        if (weights.size() >= 2) {
            sort(weights.begin(), weights.end(), [](const pair<int, double>& u1, const pair<int, double>& u2) {return u1.second < u2.second; });
            answer += weights[0].second + weights[1].second;
        }
        else {
            for (int j = 0; j < u.size(); ++j)
            {
                if (find(weights.begin(), weights.end(), u[j]) == weights.end()) {
                    weights.push_back(u[j]);
                }
            }
            sort(weights.begin(), weights.end(), [](const pair<int, double>& u1, const pair<int, double>& u2) {return u1.second < u2.second; });
            answer += weights[0].second + weights[1].second;
        }
    }
    return answer / 2;
}

vector<int> bnb(const Graph& g, vector<int>& visited, vector<int>& BestPath)
{
    if (visited.size() == g.get_vertices().size()) {
        return MinPath(g, BestPath, visited);
    }
    for (int i = 0; i < g.get_vertices().size(); ++i)
    {
        if (find(visited.begin(), visited.end(), i) == visited.end()) {
            vector<int> vnext = visited;
            vnext.push_back(i);
            if (BestPath.size() < g.get_vertices().size() or LowerBound(g, vnext) < length(g, BestPath)) {
                vector<int> path = bnb(g, vnext, BestPath);
                if(path.size() == g.get_vertices().size()){ 
                    BestPath = MinPath(g, BestPath, path);
                }
            }
        }
    }
    return BestPath;
}

vector<int> tsp_bnb(const Graph& g, int start_vertex) 
{
    if (g.get_vertices().size() <= 1) {
        return{};
    }
    vector<int> BestPath;
    vector<int> visited;
    visited.push_back(start_vertex);   
    auto result = bnb(g, visited, BestPath);   
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> full_enumeration(const Graph& g, vector<int>& visited, vector<int>& BestPath)
{
    if (visited.size() == g.get_vertices().size()) {
        return MinPath(g, BestPath, visited);
    }
    for (int i = 0; i < g.get_vertices().size(); ++i)
    {
        if (find(visited.begin(), visited.end(), i) == visited.end())
        {
            vector<int> vnext = visited;
            vnext.push_back(i);
            vector<int> path = full_enumeration(g, vnext, BestPath);
            if (path.size() == g.get_vertices().size()) {
                BestPath = MinPath(g, BestPath, path);
            }
        }
    }
    return BestPath;
}

vector<int> tsp_full_enumeration(const Graph& g, int start_vertex)
{
    if (g.get_vertices().size() <= 1) {
        return {};
    }
    vector<int> BestPath;
    vector<int> visited;
    visited.push_back(start_vertex);
    auto result = full_enumeration(g, visited, BestPath);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> tsp_greedy(const Graph& g, int start_vertex)
{
    auto test = g.get_vertices();
    if (g.get_vertices().size() <= 1) {
        return {};
    }
    vector<int> path;
    int current = start_vertex;
    path.push_back(current);
    while (path.size() != g.get_vertices().size())
    {
        auto u = g.get_adjacent_vertices(current);
        if (u.size() != 0) {
            double min = N;
            int next = H;
            for (auto i = 0; i < u.size(); ++i)
            {
                if (find(path.begin(), path.end(), u[i]) == path.end() and g.edge_weight(current, u[i]) < min) {
                    next = u[i];
                    min = g.edge_weight(current, u[i]);
                }
            }

            if (next == H) {
                return{};
            }

            path.push_back(next);
            current = next;
        }
        else {
            break;
        }
    }

    if (!g.has_edge(path[0], path[path.size() - 1])) {
        return{};
    }

    return path;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> RandomPath(const Graph& g, int start_vertex)
{
    vector<int> result;
    result.push_back(start_vertex);
    while (result.size() < g.get_vertices().size())
    {
        auto u = g.get_adjacent_vertices(result[result.size() - 1]);
        int current_vertex = rand() % u.size();
        if (find(result.begin(), result.end(), u[current_vertex]) == result.end()){
            result.push_back(u[current_vertex]);
        }
    }
    return result;
}

vector<int> Transform(const vector<int>& path, const int& a, const int& b, const int& c, const int& d) 
{
    vector<int> result;
    result.push_back(path[a]);
    for (int i = c; i != b; --i) 
    {
        result.push_back(path[i]);
    }
    result.push_back(path[b]);
    for (int i = d; i < path.size(); ++i) 
    {
        result.push_back(path[i]);
    }
    for (int i = 0; i < a; ++i) 
    {
        result.push_back(path[i]);
    }
    return result;
}

vector<int> TwoOptImprove(const Graph& graph, const vector<int>& path) 
{
    if (path.size() <= 3) {
        return path;
    }

    for (int i = 0; i < path.size() - 3; ++i) 
    {
        for (int j = i + 2; j < path.size() - 1; ++j) 
        {
            int oldWeight = graph.edge_weight(path[i], path[i + 1]) + graph.edge_weight(path[j], path[j + 1]);
            int newWeight = graph.edge_weight(path[i], path[j]) + graph.edge_weight(path[i + 1], path[j + 1]);
            if (newWeight < oldWeight) {
                return Transform(path, i, i + 1, j, j + 1);
            }
        }
    }

    return path;
}

vector<int> tsp_ls(const Graph& g, int start_vertex) {
    
    vector<int> best_path = g.get_vertices();;
    vector<int> currentPath;

    if (g.get_vertices().size() < 2) {
        return vector<int> {};
    }

    for (int i = 0; i < 10; ++i) {
        currentPath = RandomPath(g, start_vertex);
        if (currentPath.empty()) {
            return vector<int> {};
        }
        while (true) 
        {
            vector<int> imrovedPath = TwoOptImprove(g, currentPath);
            if (length(g, imrovedPath) < length(g, currentPath)) {
                currentPath = imrovedPath;
            }
            else {
                break;
            }
        }
        if (length(g, currentPath) < length(g, best_path)) {
            best_path = currentPath;
        }
    }
    return best_path;
}