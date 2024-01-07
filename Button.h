#pragma once
#include <functional>
class Button {
public:
    std::string name;
    int x1, y1, x2, y2;
    Button() {
        this->name = "";
        this->x1 = 0;
        this->x2 = 0;
        this->y1 = 0;
        this->y2 = 0;
    }
    Button(std::string name, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) {
        this->name = name;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
    std::function<void()> drawButton;
    std::function<void()> drawButtonDif;
    std::function<void()> onClick;
};