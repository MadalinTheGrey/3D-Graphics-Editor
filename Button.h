#pragma once
#include <functional>
#include <string>
class Button {
public:
    std::string name;
    int x1, y1, x2, y2;
    Button();
    Button(std::string name, int x1, int y1, int x2, int y2);
    std::function<void()> drawButton;
    std::function<void()> drawButtonDif;
    std::function<void()> onClick;
};