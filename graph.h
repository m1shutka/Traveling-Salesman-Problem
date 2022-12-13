#pragma once
#include <map>
#include <vector>
#include <tuple>
#include <initializer_list>

class Graph {
public:
    Graph() {}
    Graph(std::initializer_list<std::tuple<int, int, double>> edges);

    /// Добавление вершины в граф.
    void add_vertex(int vertex);

    /// Добавдение ребра в граф. 
    void add_edge(int start_vertex, int end_vertex, double weight = 1.0);

    /// Возвращает все вершины графа.
    std::vector<int> get_vertices() const;

    /// Возвращает все смежные вершины для данной вершины.
    std::vector<int> get_adjacent_vertices(int src_vertex) const;

    /// Возврашает смежные ребра для вершины как вектор (конечная вершина, вес ребра).
    std::vector<std::pair<int, double>> get_adjacent_edges(int src_vertex) const;

    /// Провернка наличия вершины.
    bool has_vertex(int vertex) const;

    /// Проверка наличия ребра между вершинами.
    bool has_edge(int start_vertex, int end_vertex) const;

    /// Возвращает вес ребра между мершинами.
    double edge_weight(int start_vertex, int end_vertex) const;

    /// Удаление вершины и связанных с ней ребер.
    void remove_vertex(int vertex);

    /// Удаление ребра между вершинами.
    void remove_edge(int start_vertex, int end_vertex);

private:
    /// Граф предсттавляет из себя некую таблицу смежности
    std::map<int, std::map<int, double>> vertices;
};