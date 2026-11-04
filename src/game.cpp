#include "game.hpp"

#include <ncurses.h>

#include <chrono>
#include <optional>
#include <stdexcept>
#include <thread>

Game::Game(const std::size_t fps) {
    if (fps == 0) throw std::invalid_argument("FPS must be > 0");

    frame_time_ = std::chrono::microseconds(1'000'000 / fps);

    if (!initscr()) throw std::runtime_error("initscr failed");

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    leaveok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
    }

    next_frame_ = prev_frame_ = clock::now();
    dt_ = frame_time_;
}

Game::~Game() {
    endwin();
}

std::optional<int> Game::poll_key() {
    int ch = getch();
    if (ch == ERR) return std::nullopt;
    return ch;
}

void Game::begin_frame() {
    erase();
}

void Game::end_frame() {
    wnoutrefresh(stdscr);
    doupdate();

    next_frame_ += frame_time_;

    if (clock::now() > next_frame_)
        next_frame_ = clock::now();  // we're late: don't burst to catch up
    std::this_thread::sleep_until(next_frame_);

    clock::time_point now = clock::now();
    clock::duration raw = now - prev_frame_;
    dt_ = raw > max_dt_ ? max_dt_ : raw;
    prev_frame_ = now;
}
