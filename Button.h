#ifndef INC_3D_EDITOR_V2_BUTTON_H
#define INC_3D_EDITOR_V2_BUTTON_H

#include <utility>
#include <vector>
#include <functional>
#include <cstdio>
#include <string>
#include "myGraphics.h"

class Button {
public:
    std::string name;
    int x1, y1, x2, y2;
    explicit Button(std::string name, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) {
        this->name = std::move(name);
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
    std::function<void()> drawButton;
    std::function<void()> onClick;
};
//TODO transforma din vector STL in vector dinamic si muta in GB?
std::vector<Button> buttons;

static void InitializeButtons() {
    //New file button
    Button newFileButton = *new Button("New file", 0, 0, 90, 30);
    newFileButton.drawButton = []() {
        writeText(10, 25, "New file", COLOR(182, 182, 182), 1);
        drawLine(90, 0, 90, 30, COLOR(118, 118, 118), 1);
    };
    newFileButton.onClick = []() {
        //TODO new file implementation
        printf("New file!\n");
    };
    newFileButton.drawButton();
    buttons.push_back(newFileButton);
    //Open file button
    Button openFileButton = *new Button("Open file", 90, 0, 180, 30);
    openFileButton.drawButton = []() {
        writeText(100, 25, "Open file", COLOR(182, 182, 182), 1);
        drawLine(180, 0, 180, 30, COLOR(118, 118, 118), 1);
    };
    openFileButton.onClick = []() {
        //TODO open file implementation
        printf("Open file!\n");
    };
    openFileButton.drawButton();
    buttons.push_back(openFileButton);
}

void checkIfButtonClicked(int x, int y) {
    for(auto & button : buttons)
        if(x >= button.x1 && x <= button.x2 && y >= button.y1 && y <= button.y2)
            button.onClick();
}
#endif //INC_3D_EDITOR_V2_BUTTON_H
