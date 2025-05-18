#include "Grid.h"
#include <iostream>

// ����������� ����� Grid.
// r � ������� ����� � ����, c � ������� ��������.
// �������� ������� ������� ��������� -1 (������ ������).
Grid::Grid(int r, int c) : rows(r), cols(c) {
    clues.assign(rows, std::vector<int>(cols, -1));
}

// �������� �������� ���� ���� � �������.
// ����� ������������ �� ���������� ��� �������� �� ��������� �����
// �� ������ �����-������� �������� �����.
void Grid::draw() const {
    for (int i = 0; i <= rows; ++i) {
        // ������� ����� ��� �����
        for (int j = 0; j < cols; ++j) {
            std::cout << "+";
            if (path.count({ i, j, i, j + 1 }))
                std::cout << "---";  // � �����
            else
                std::cout << "   ";  // ���� �����
        }
        std::cout << "+\n";

        if (i == rows) break;

        // ������� ����� ��� �� ������� �������� �����
        for (int j = 0; j < cols; ++j) {
            if (path.count({ i, j, i + 1, j }))
                std::cout << "|";   // � �����
            else
                std::cout << " ";   // ���� �����

            if (clues[i][j] >= 0)
                std::cout << " " << clues[i][j] << " ";  // �����-�������
            else
                std::cout << "   ";                      // ������� ������
        }

        // ������� ����� ���� ���������� �������
        if (path.count({ i, cols, i + 1, cols }))
            std::cout << "|\n";
        else
            std::cout << " \n";
    }
}

// ������� ������ ��� �������� ����� ����:
// �������������� � ������������, ��� �������� ������� ������.
std::vector<Edge> Grid::allEdges() const {
    std::vector<Edge> edges;
    // ��������� �� ��� ����������� ������
    for (int i = 0; i <= rows; ++i) {
        for (int j = 0; j <= cols; ++j) {
            if (j < cols)
                edges.push_back({ i, j, i, j + 1 });  // ������������� �����
            if (i < rows)
                edges.push_back({ i, j, i + 1, j });  // ����������� �����
        }
    }
    return edges;
}

