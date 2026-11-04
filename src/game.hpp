#pragma once
#include <chrono>
#include <optional>

class Game {
private:
    using clock = std::chrono::steady_clock;

    static constexpr clock::duration max_dt_ = std::chrono::milliseconds(100);

    bool running_ = true;
    clock::duration frame_time_{};
    clock::time_point next_frame_{};
    clock::time_point prev_frame_{};
    clock::duration dt_{};

public:
    explicit Game(std::size_t);  // init
    ~Game();                     // cleanup
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    bool running() const {
        return running_;
    }
    void quit() {
        running_ = false;
    }

    void begin_frame();
    void end_frame();
    std::optional<int> poll_key();

    double delta_time() const {
        return std::chrono::duration<double>(dt_).count();
    }
};
