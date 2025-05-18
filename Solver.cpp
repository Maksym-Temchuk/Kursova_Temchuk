#include "Solver.h"
#include <iostream>
#include <utility>

// �����������, ���� ������ ��������� �� ����
Solver::Solver(Grid& g) : grid(g) {}

// ���� ������� ����� ������� ������� (i, j), �� � �������� �����
int Solver::countEdges(int i, int j) const {
    int cnt = 0;
    for (auto& e : grid.allEdges()) {
        // ����������, �� ����� � ����� �� 4 �������� ������� �������
        if ((e.x1 == i && e.y1 == j && e.x2 == i && e.y2 == j + 1) ||
            (e.x1 == i && e.y1 == j + 1 && e.x2 == i + 1 && e.y2 == j + 1) ||
            (e.x1 == i + 1 && e.y1 == j && e.x2 == i + 1 && e.y2 == j + 1) ||
            (e.x1 == i && e.y1 == j && e.x2 == i + 1 && e.y2 == j)) {
            if (grid.path.count(e)) cnt++; // ���� ����� � � ����� � ������ ����
        }
    }
    return cnt;
}

// ��������, �� �� ������� ���������
bool Solver::satisfies() const {
    for (int i = 0; i < grid.rows; ++i)
        for (int j = 0; j < grid.cols; ++j)
            if (grid.clues[i][j] >= 0 && countEdges(i, j) != grid.clues[i][j])
                return false; // ������� �� ��������
    return true;
}

// ������� ������ ��� ��������� ����� � ����� �����
bool Solver::dfs(std::pair<int, int> u, std::pair<int, int> p,
    std::set<std::pair<int, int>>& vis) const {
    vis.insert(u);
    for (auto& v : graph.at(u)) {
        if (v == p) continue;          // ���������� ���������� �������
        if (vis.count(v) || dfs(v, u, vis)) return true; // �������� ����
    }
    return false;
}

// ��������, �� ������� ����� �������� ����, �� ������� �� �����
bool Solver::isCycle() const {
    graph.clear();
    for (auto& e : grid.path) {
        auto a = std::make_pair(e.x1, e.y1);
        auto b = std::make_pair(e.x2, e.y2);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::set<std::pair<int, int>> vis;
    auto start = graph.begin()->first;
    if (!dfs(start, { -1,-1 }, vis)) return false; // ���� ���� �����
    return vis.size() == graph.size();             // ��������, �� �������� �� �������
}

// ������� ����������� ������ ����������� � ���������� �����
bool Solver::solveAuto() {
    auto edges = grid.allEdges();
    std::cout << "Step-by-step solution:\n";
    return backtrack(edges, 0);
}

// ����������� ������ ��� �������� ��������� �����
bool Solver::backtrack(const std::vector<Edge>& edges, int idx) {
    if (idx == (int)edges.size()) {
        // ���� ��������� ���� � ����������, �� ������ ���������
        return satisfies() && isCycle();
    }

    // ������ �������� ����� �� �����
    grid.path.insert(edges[idx]);
    std::cout << "Including edge: ("
        << edges[idx].x1 << "," << edges[idx].y1
        << ")-(" << edges[idx].x2 << "," << edges[idx].y2 << ")\n";
    grid.draw();
    if (backtrack(edges, idx + 1)) return true;

    // ��������� ����� � ����������� ������
    grid.path.erase(edges[idx]);
    return backtrack(edges, idx + 1);
}


