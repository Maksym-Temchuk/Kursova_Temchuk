#ifndef EDGE_H
#define EDGE_H

#include <tuple>

// Представляє ребро сітки Slitherlink.
// Ребро задане двома кінцевими точками (x1, y1) та (x2, y2).
struct Edge {
    int x1; // X-координата першої вершини
    int y1; // Y-координата першої вершини
    int x2; // X-координата другої вершини
    int y2; // Y-координата другої вершини

    // Порівняння ребер для зберігання в впорядкованих контейнерах.
    // Виконується лексикографічне порівняння координат.
    bool operator<(const Edge& e) const {
        return std::tie(x1, y1, x2, y2)
            < std::tie(e.x1, e.y1, e.x2, e.y2);
    }
};

#endif // EDGE_H

