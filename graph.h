#pragma once
#include <map>
#include <vector>
#include <tuple>
#include <initializer_list>

class Graph {
public:
    Graph() {}
    Graph(std::initializer_list<std::tuple<int, int, double>> edges);

    /// ���������� ������� � ����.
    void add_vertex(int vertex);

    /// ���������� ����� � ����. 
    void add_edge(int start_vertex, int end_vertex, double weight = 1.0);

    /// ���������� ��� ������� �����.
    std::vector<int> get_vertices() const;

    /// ���������� ��� ������� ������� ��� ������ �������.
    std::vector<int> get_adjacent_vertices(int src_vertex) const;

    /// ���������� ������� ����� ��� ������� ��� ������ (�������� �������, ��� �����).
    std::vector<std::pair<int, double>> get_adjacent_edges(int src_vertex) const;

    /// ��������� ������� �������.
    bool has_vertex(int vertex) const;

    /// �������� ������� ����� ����� ���������.
    bool has_edge(int start_vertex, int end_vertex) const;

    /// ���������� ��� ����� ����� ���������.
    double edge_weight(int start_vertex, int end_vertex) const;

    /// �������� ������� � ��������� � ��� �����.
    void remove_vertex(int vertex);

    /// �������� ����� ����� ���������.
    void remove_edge(int start_vertex, int end_vertex);

private:
    /// ���� ������������� �� ���� ����� ������� ���������
    std::map<int, std::map<int, double>> vertices;
};