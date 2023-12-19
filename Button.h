#ifndef INC_3D_EDITOR_V2_BUTTON_H
#define INC_3D_EDITOR_V2_BUTTON_H

#include <utility>
#include <vector>
#include <functional>
#include <cstdio>
#include <string>
#include "myGraphics.h"
#include "Corp.h"

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
    
    //New 3D Form button
    Button new_3D_form = *new Button("New form", 180, 0, 275, 30);
    new_3D_form.drawButton = []() 
        {
            writeText(190, 25, "New form", COLOR(182, 182, 182), 1);
            drawLine(275, 0, 275, 30, COLOR(118, 118, 118), 1);
        };
    new_3D_form.onClick = []()
        {
            printf("New form added!\n");
            S.AdaugareCorp();
        };
    new_3D_form.drawButton();
    buttons.push_back(new_3D_form);

    //Draw Line button
    Button draw_line = *new Button("Draw Line", 0, 100, 40, 140);
    draw_line.drawButton = []()
        {
            drawLine(0, 100, 40, 100, COLOR(118, 118, 118), 1);
            drawLine(0, 140, 40, 140, COLOR(118, 118, 118), 1);
            drawLine(30, 110, 10, 130);
        };
    draw_line.onClick = []()
        {
            last_clicked_button = 3;
        };
    draw_line.drawButton();
    buttons.push_back(draw_line);
}

void checkMouseClick(int x, int y) {
    bool is_button = false;
    for (auto& button : buttons)
        if (x >= button.x1 && x <= button.x2 && y >= button.y1 && y <= button.y2)
        {
            is_button = true;
            button.onClick();
        }
    if (!is_button)
    {
        if (buttons[last_clicked_button].name == "Draw Line" && S.corpuri_selectate.size() == 1)
        {
            S.corpuri_selectate[0].UserDrawLine();
        }
        else
        {
            S.ChangeSelected(x, y);
        }
    }

}
#endif //INC_3D_EDITOR_V2_BUTTON_H
