#ifndef GRID_H
#define GRID_H

#include "Edge.h"
#include <vector>
#include <set>
#include <iostream>

// Клас Grid відповідає за збереження та відображення ігрового поля.
// Містить розміри сітки, матрицю чисел-підказок та поточний шлях (ребра).
class Grid {
public:
    // Конструктор створює сітку розміром rows×cols
    Grid(int rows, int cols);

    // Виводить сітку в консоль з урахуванням поточного шляху та підказок
    void draw() const;

    // Формує та повертає список усіх можливих ребер сітки
    std::vector<Edge> allEdges() const;

    int rows;    // кількість рядків у сітці
    int cols;    // кількість стовпців у сітці
    std::vector<std::vector<int>> clues;  // матриця підказок (-1 = без підказки)
    std::set<Edge> path;                  // множина ребер, що належать поточному шляху
};

#endif // GRID_H

