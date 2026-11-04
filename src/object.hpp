#pragma once

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void draw() const = 0;
    virtual void handle_input(int key) = 0;
    virtual void update(double dt) = 0;
};
