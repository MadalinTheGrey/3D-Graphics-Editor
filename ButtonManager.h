#pragma once
#ifndef INC_3D_EDITOR_V2_BUTTON_H
#define INC_3D_EDITOR_V2_BUTTON_H
#include <utility>
#include <vector>
#include <functional>
#include <cstdio>
#include <string>
#include <iostream>
#include "myGraphics.h"
#include "Corp.h"
#include "FilesManager.h"
#include "Render3D.h"
#include "OpenFileWindow.h"
#include "GlobalVariables.h"
#include "SaveFileWindow.h"
#include "Button.h"

using namespace std;


std::vector<Button> buttons;
std::vector<Button> chooseCorpToEdit;


void InitializeRightMenu() {
    int ystart = 0, cellSize = 40;
    chooseCorpToEdit.clear();
    setviewport(1080, 30, getmaxx(), getmaxy(), 1);
    clearviewport();
    drawFilledRectangle(0, 0, getmaxx(), getmaxy(), COLOR(20, 20, 20));
    for (int i = 0; i < S.corpuri.size(); ++i) {
        Button bt = *new Button(S.corpuri[i].name, 1080, ystart + 30, 1280, ystart + cellSize + 30);
        chooseCorpToEdit.push_back(bt);
        printf("Index is: %d\n", i);
        chooseCorpToEdit[i].onClick = [i]() {
            printf("%s\n", chooseCorpToEdit[i].name.c_str());
            };
        ystart += cellSize;
        drawEmptyRectangle(0, ystart - cellSize, getmaxx() - 10, ystart, COLOR(182, 182, 182));
        writeText(1080 + 20, ystart + 23, (char*)S.corpuri[i].name.c_str(), COLOR(182, 182, 182), 1, 0, COLOR(20, 20, 20));

    }
    setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
    renderAgain = 1;
}

void checkMouseClick(int x, int y) {
    bool is_top_menu_button = false;
    for (auto& button : buttons)
        if (x >= button.x1 && x <= button.x2 && y >= button.y1 && y <= button.y2)
        {
            is_top_menu_button = true;
            button.onClick();
        }
    for (auto& button : chooseCorpToEdit)
        if (x >= button.x1 && x <= button.x2 && y >= button.y1 && y <= button.y2)
        {
            is_top_menu_button = true;
            button.onClick();
        }
    if (!is_top_menu_button)
    {
        if (buttons[last_clicked_button].name == "Draw Line" && S.corpuri_selectate.size() == 1)
        {
            for (auto& i : S.corpuri_selectate)
            {
                S.corpuri[i].UserDrawLine();
                break;
            }
        }
        else
        {
            S.ChangeSelected(x, y);
        }
        last_clicked_button = 0;
    }

}
void InitializeButtons() {
    //New file button
    Button newFileButton = *new Button("New file", 0, 0, 90, 30);
    newFileButton.drawButton = []() {
        writeText(10, 25, "New file", COLOR(182, 182, 182), 1);
        drawLine(90, 0, 90, 30, COLOR(118, 118, 118), 1);
        };
    newFileButton.onClick = []() {
        //TODO new file implementation
        printf("New file!\n");
        //Create a new window with graphics.h and ask for the name of the file
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
        string path = receivePathToFile();
        cout << path << '\n';
        setcurrentwindow(FIRST_WINDOW);
        setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
        if (path != "null")
            readFromFile(path.c_str()), InitializeRightMenu();
        else
            printf("No file selected!\n");
        };
    openFileButton.drawButton();
    buttons.push_back(openFileButton);
    //Save file button
    Button saveFileButton = *new Button("Save file", 180, 0, 275, 30);
    saveFileButton.drawButton = []() {
        writeText(190, 25, "Save file", COLOR(182, 182, 182), 1);
        drawLine(275, 0, 275, 30, COLOR(118, 118, 118), 1);
        };
    saveFileButton.onClick = []() {
        StopRender = 1;
        SaveFile();
        setcurrentwindow(1);
        StopRender = 0;
        };
    saveFileButton.drawButton();
    buttons.push_back(saveFileButton);
    //New 3D Form button
    Button new_3D_form = *new Button("New form", 270, 0, 360, 30);
    new_3D_form.drawButton = []()
        {
            writeText(280, 25, "New form", COLOR(182, 182, 182), 1);
            drawLine(370, 0, 370, 30, COLOR(118, 118, 118), 1);
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

#endif //INC_3D_EDITOR_V2_BUTTON_H
