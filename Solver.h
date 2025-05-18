#ifndef SOLVER_H
#define SOLVER_H

#include "Grid.h"
#include <map>
#include <vector>
#include <set>

// Клас для автоматичного розв'язання головоломки Slitherlink
class Solver {
public:
    // Конструктор, що приймає посилання на об'єкт сітки
    explicit Solver(Grid& g);

    // Запускає процес автоматичного розв'язання
    bool solveAuto();

private:
    // Перевіряє, чи всі підказки на полі виконані
    bool satisfies() const;

    // Допоміжна функція для пошуку в глибину — перевірка наявності циклу
    bool dfs(std::pair<int, int> u, std::pair<int, int> p,
        std::set<std::pair<int, int>>& vis) const;

    // Перевіряє, чи всі ребра формують єдиний цикл
    bool isCycle() const;

    // Рекурсивний перебір усіх можливих варіантів включення ребер
    bool backtrack(const std::vector<Edge>& edges, int idx);

    // Підраховує кількість ребер, що оточують клітинку
    int countEdges(int i, int j) const;

    Grid& grid; // Посилання на сітку, з якою працює розв'язувач

    // Граф, що використовується для перевірки циклу
    mutable std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> graph;
};

#endif // SOLVER_H

