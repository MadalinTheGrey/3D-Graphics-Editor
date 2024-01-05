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
            readFromFile(path.c_str());
        else
            printf("No file selected!\n");
        };
    openFileButton.drawButton();
    buttons.push_back(openFileButton);

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
            last_clicked_button = 2;
        };
    draw_line.drawButton();
    buttons.push_back(draw_line);

    //Draw square button
    Button draw_square = *new Button("Draw square", 0, 150, 40, 190);
    draw_square.drawButton = []()
        {
            drawLine(0, 150, 40, 150, COLOR(118, 118, 118), 1);
            drawLine(0, 190, 40, 190, COLOR(118, 118, 118), 1);
            drawEmptyRectangle(10, 160, 30, 180);
        };
    draw_square.onClick = []()
        {
            last_clicked_button = 3;
        };
    draw_square.drawButton();
    buttons.push_back(draw_square);

    //Draw circle button
    Button draw_circle = *new Button("Draw circle", 0, 200, 40, 240);
    draw_circle.drawButton = []()
        {
            drawLine(0, 200, 40, 200, COLOR(118, 118, 118), 1);
            drawLine(0, 240, 40, 240, COLOR(118, 118, 118), 1);
            drawCircle(10, 210, 30, 230);
        };
    draw_circle.onClick = []()
        {
            last_clicked_button = 4;
        };
    draw_circle.drawButton();
    buttons.push_back(draw_circle);

    //Rotation angle buttons
    writeText(1130, 381, "Rotation angle:", COLOR(182, 182, 182), 1); //x = 1120 -> 1230, y = 355 -> 385
    
    Button angle_minus = *new Button("Angle minus", 1120, 390, 1170, 420);
    angle_minus.drawButton = []()
        {
            writeText(1125, 416, "Angle-", COLOR(182, 182, 182), 1);
            drawEmptyRectangle(1120, 390, 1170, 420, COLOR(118, 118, 118), 1);
        };
    angle_minus.onClick = []()
        {
            default_angle -= 0.001;
        };
    angle_minus.drawButton();
    buttons.push_back(angle_minus);

    Button angle_plus = *new Button("Angle plus", 1180, 390, 1230, 420);
    angle_plus.drawButton = []()
        {
            writeText(1185, 416, "Angle+", COLOR(182, 182, 182), 1);
            drawEmptyRectangle(1180, 390, 1230, 420, COLOR(118, 118, 118), 1);
        };
    angle_plus.onClick = []()
        {
            default_angle += 0.001;
        };
    angle_plus.drawButton();
    buttons.push_back(angle_plus);

    //Draw Precision buttons
    writeText(1130, 451, "Draw precision:", COLOR(182, 182, 182), 1); //x = 1120 -> 1230, y = 425 -> 455
    
    Button dp1 = *new Button("dp1", 1120, 460, 1154, 490);
    dp1.drawButton = []()
        {
            writeText(1129, 486, "1p", COLOR(182, 182, 182), 1);
            drawEmptyRectangle(1120, 460, 1154, 490, COLOR(118, 118, 118), 1);
        };
    dp1.onClick = []()
        {
            draw_precision = 1;
        };
    dp1.drawButton();
    buttons.push_back(dp1);

    Button dp5 = *new Button("dp5", 1158, 460, 1192, 490);
    dp5.drawButton = []()
        {
            writeText(1167, 486, "5p", COLOR(182, 182, 182), 1);
            drawEmptyRectangle(1158, 460, 1192, 490, COLOR(118, 118, 118), 1);
        };
    dp5.onClick = []()
        {
            draw_precision = 5;
        };
    dp5.drawButton();
    buttons.push_back(dp5);

    Button dp10 = *new Button("dp10", 1196, 460, 1230, 490);
    dp10.drawButton = []()
        {
            writeText(1201, 486, "10p", COLOR(182, 182, 182), 1);
            drawEmptyRectangle(1196, 460, 1230, 490, COLOR(118, 118, 118), 1);
        };
    dp10.onClick = []()
        {
            draw_precision = 10;
        };
    dp10.drawButton();
    buttons.push_back(dp10);

    //Apply changes button
    Button apply_changes = *new Button("Apply changes", 1120, 505, 1230, 535);
    apply_changes.drawButton = []()
        {
            writeText(1131, 531, "Apply changes", COLOR(182, 182, 182), 1);
            drawEmptyRectangle(1120, 505, 1230, 535, COLOR(118, 118, 118), 1);
        };
    apply_changes.onClick = []()
        {
            if (S.corpuri_selectate.size() == 1) S.ApplyChanges();
        };
    apply_changes.drawButton();
    buttons.push_back(apply_changes);

    //New 3D Form button
    Button new_3D_form = *new Button("New object", 1120, 540, 1230, 570);
    new_3D_form.drawButton = []()
        {
            writeText(1140, 566, "New object", COLOR(182, 182, 182), 1);
            drawEmptyRectangle(1120, 540, 1230, 570, COLOR(118, 118, 118), 1);
        };
    new_3D_form.onClick = []()
        {
            S.AdaugareCorp();
        };
    new_3D_form.drawButton();
    buttons.push_back(new_3D_form);

    //Delete object button
    Button delete_object = *new Button("Delete object", 1120, 575, 1230, 605);
    delete_object.drawButton = []()
        {
            writeText(1135, 601, "Delete object", COLOR(182, 182, 182), 1);
            drawEmptyRectangle(1120, 575, 1230, 605, COLOR(118, 118, 118), 1);
        };
    delete_object.onClick = []()
        {
            if (S.corpuri_selectate.size() == 1) S.EliminaCorp(S.corpuri_selectate[0]);
        };
    delete_object.drawButton();
    buttons.push_back(delete_object);

    //Reset object
    Button reset_object = *new Button("Reset object", 1120, 610, 1230, 640);
    reset_object.drawButton = []()
        {
            drawEmptyRectangle(1120, 610, 1230, 640, COLOR(118, 118, 118), 1);
            writeText(1138, 636, "Reset object", COLOR(182, 182, 182), 1);
        };
    reset_object.onClick = []()
        {
            if(S.corpuri_selectate.size() == 1) S.ResetObject(S.corpuri_selectate[0]);
        };
    reset_object.drawButton();
    buttons.push_back(reset_object);
    //Reset scene
    Button reset_scene = *new Button("Reset scene", 1120, 645, 1230, 675);
    reset_scene.drawButton = []()
        {
            drawEmptyRectangle(1120, 645, 1230, 675, COLOR(118, 118, 118), 1);
            writeText(1140, 671, "Reset scene", COLOR(182, 182, 182), 1);
        };
    reset_scene.onClick = []()
        {
            S.ResetScene();
        };
    reset_scene.drawButton();
    buttons.push_back(reset_scene);
}

void checkMouseClick(int x, int y) {
    cout << x << " " << y << "\n";
    bool is_button = false;
    //pasul la care este user-ul in desenarea unei forme simple (0 = neapelat/terminat, 1 = pozitionat primul punct)
    static int form_draw_step = 0;
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
            int i = S.corpuri_selectate[0];
            int z_pos = 100; //pozitia pe z pe care o are sectiunea pe care desenam (ar trebui preluata de undeva)
            S.UserDrawLine(x, y, form_draw_step, z_pos, i);
            form_draw_step = 1 - form_draw_step;
        }
        else
        {
            S.ChangeSelected(x, y);
        }
        if(form_draw_step == 0) last_clicked_button = 0;
    }
}


#endif //INC_3D_EDITOR_V2_BUTTON_H
