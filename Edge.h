#ifndef EDGE_H
#define EDGE_H

#include <tuple>

// ����������� ����� ���� Slitherlink.
// ����� ������ ����� �������� ������� (x1, y1) �� (x2, y2).
struct Edge {
    int x1; // X-���������� ����� �������
    int y1; // Y-���������� ����� �������
    int x2; // X-���������� ����� �������
    int y2; // Y-���������� ����� �������

    // ��������� ����� ��� ��������� � ������������� �����������.
    // ���������� ��������������� ��������� ���������.
    bool operator<(const Edge& e) const {
        return std::tie(x1, y1, x2, y2)
            < std::tie(e.x1, e.y1, e.x2, e.y2);
    }
};

#endif // EDGE_H

