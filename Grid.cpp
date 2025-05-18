#include "Grid.h"
#include <iostream>

// Конструктор класу Grid.
// r — кількість рядків у сітці, c — кількість стовпців.
// Ініціалізує матрицю підказок значенням -1 (порожні клітини).
Grid::Grid(int r, int c) : rows(r), cols(c) {
    clues.assign(rows, std::vector<int>(cols, -1));
}

// Виводить поточний стан сітки у консоль.
// Малює горизонтальні та вертикальні межі відповідно до поточного шляху
// та показує числа-підказки всередині клітин.
void Grid::draw() const {
    for (int i = 0; i <= rows; ++i) {
        // Малюємо верхні межі клітин
        for (int j = 0; j < cols; ++j) {
            std::cout << "+";
            if (path.count({ i, j, i, j + 1 }))
                std::cout << "---";  // є ребро
            else
                std::cout << "   ";  // немає ребра
        }
        std::cout << "+\n";

        if (i == rows) break;

        // Малюємо бокові межі та підказки всередині клітин
        for (int j = 0; j < cols; ++j) {
            if (path.count({ i, j, i + 1, j }))
                std::cout << "|";   // є ребро
            else
                std::cout << " ";   // немає ребра

            if (clues[i][j] >= 0)
                std::cout << " " << clues[i][j] << " ";  // число-підказка
            else
                std::cout << "   ";                      // порожня клітина
        }

        // Малюємо праву межу останнього стовпця
        if (path.count({ i, cols, i + 1, cols }))
            std::cout << "|\n";
        else
            std::cout << " \n";
    }
}

// Повертає вектор усіх можливих ребер сітки:
// горизонтальних і вертикальних, для подальшої обробки рішення.
std::vector<Edge> Grid::allEdges() const {
    std::vector<Edge> edges;
    // Проходимо по всіх координатах вершин
    for (int i = 0; i <= rows; ++i) {
        for (int j = 0; j <= cols; ++j) {
            if (j < cols)
                edges.push_back({ i, j, i, j + 1 });  // горизонтальне ребро
            if (i < rows)
                edges.push_back({ i, j, i + 1, j });  // вертикальне ребро
        }
    }
    return edges;
}

