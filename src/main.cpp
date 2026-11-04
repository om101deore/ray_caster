#include <memory>
#include <vector>

#include "game.hpp"
#include "object.hpp"
#include "wall.hpp"

int main() {
    Game game(30);

    // define game objects
    std::vector<std::unique_ptr<GameObject>> objects;

    objects.push_back(std::make_unique<Wall>());

    while (game.running()) {
        while (auto key = game.poll_key()) {
            if (*key == 'q')
                game.quit();
            else {
                for (auto& obj : objects) {
                    obj->handle_input(*key);
                }
            }
        }

        game.begin_frame();
        const double dt = game.delta_time();

        for (auto& obj : objects) {
            obj->update(dt);
        }

        for (auto& obj : objects) {
            obj->draw();
        }

        game.end_frame();
    }

    return 0;
}
