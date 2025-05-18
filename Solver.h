#ifndef SOLVER_H
#define SOLVER_H

#include "Grid.h"
#include <map>
#include <vector>
#include <set>

// ���� ��� ������������� ����'������ ����������� Slitherlink
class Solver {
public:
    // �����������, �� ������ ��������� �� ��'��� ����
    explicit Solver(Grid& g);

    // ������� ������ ������������� ����'������
    bool solveAuto();

private:
    // ��������, �� �� ������� �� ��� �������
    bool satisfies() const;

    // �������� ������� ��� ������ � ������� � �������� �������� �����
    bool dfs(std::pair<int, int> u, std::pair<int, int> p,
        std::set<std::pair<int, int>>& vis) const;

    // ��������, �� �� ����� �������� ������ ����
    bool isCycle() const;

    // ����������� ������ ��� �������� ������� ��������� �����
    bool backtrack(const std::vector<Edge>& edges, int idx);

    // ϳ������� ������� �����, �� �������� �������
    int countEdges(int i, int j) const;

    Grid& grid; // ��������� �� ����, � ���� ������ ����'������

    // ����, �� ��������������� ��� �������� �����
    mutable std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> graph;
};

#endif // SOLVER_H

