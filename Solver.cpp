#include "Solver.h"
#include <iostream>
#include <utility>

// Конструктор, який приймає посилання на сітку
Solver::Solver(Grid& g) : grid(g) {}

// Рахує кількість ребер навколо клітинки (i, j), які є частиною шляху
int Solver::countEdges(int i, int j) const {
    int cnt = 0;
    for (auto& e : grid.allEdges()) {
        // Перевіряємо, чи ребро є одним із 4 можливих навколо клітинки
        if ((e.x1 == i && e.y1 == j && e.x2 == i && e.y2 == j + 1) ||
            (e.x1 == i && e.y1 == j + 1 && e.x2 == i + 1 && e.y2 == j + 1) ||
            (e.x1 == i + 1 && e.y1 == j && e.x2 == i + 1 && e.y2 == j + 1) ||
            (e.x1 == i && e.y1 == j && e.x2 == i + 1 && e.y2 == j)) {
            if (grid.path.count(e)) cnt++; // якщо ребро є в шляху — рахуємо його
        }
    }
    return cnt;
}

// Перевіряє, чи всі підказки задоволені
bool Solver::satisfies() const {
    for (int i = 0; i < grid.rows; ++i)
        for (int j = 0; j < grid.cols; ++j)
            if (grid.clues[i][j] >= 0 && countEdges(i, j) != grid.clues[i][j])
                return false; // підказка не виконана
    return true;
}

// Глибина пошуку для виявлення циклів у графі ребер
bool Solver::dfs(std::pair<int, int> u, std::pair<int, int> p,
    std::set<std::pair<int, int>>& vis) const {
    vis.insert(u);
    for (auto& v : graph.at(u)) {
        if (v == p) continue;          // пропускаємо батьківську вершину
        if (vis.count(v) || dfs(v, u, vis)) return true; // знайдено цикл
    }
    return false;
}

// Перевіряє, чи утворені ребра формують цикл, що охоплює всі точки
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
    if (!dfs(start, { -1,-1 }, vis)) return false; // якщо немає циклу
    return vis.size() == graph.size();             // перевірка, що охоплено всі вершини
}

// Запускає автоматичне рішення головоломки з виведенням кроків
bool Solver::solveAuto() {
    auto edges = grid.allEdges();
    std::cout << "Step-by-step solution:\n";
    return backtrack(edges, 0);
}

// Рекурсивний перебір всіх можливих комбінацій ребер
bool Solver::backtrack(const std::vector<Edge>& edges, int idx) {
    if (idx == (int)edges.size()) {
        // якщо досягнуто кінця — перевіряємо, чи рішення правильне
        return satisfies() && isCycle();
    }

    // Спроба включити ребро до шляху
    grid.path.insert(edges[idx]);
    std::cout << "Including edge: ("
        << edges[idx].x1 << "," << edges[idx].y1
        << ")-(" << edges[idx].x2 << "," << edges[idx].y2 << ")\n";
    grid.draw();
    if (backtrack(edges, idx + 1)) return true;

    // Вилучення ребра і продовження пошуку
    grid.path.erase(edges[idx]);
    return backtrack(edges, idx + 1);
}


