#pragma once

#include <ncurses.h>

#include <cstdlib>

namespace gfx {
inline void put_char(int x, int y, char c) {
    if (y < 0 || y >= LINES || x < 0 || x >= COLS) return;  // keep status bar free
    mvaddch(y, x, c);
}

inline void line(int x0, int y0, int x1, int y1, char c) {
    int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    while (true) {
        put_char(x0, y0, c);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}
}  // namespace gfx
