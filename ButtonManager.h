#pragma once
#include <utility>
#include <vector>
#include <functional>
#include <cstdio>
#include <string>
#include <iostream>
#include "myGraphics.h"
#include "Corp.h"
#include "FilesManager.h"
#include "OpenFileWindow.h"
#include "GlobalVariables.h"
#include "Button.h"
#include "SaveFileWindow.h"
#include "EditObject.h"
#include "NewFileWindow.h"
vector<Button> buttons;

static void InitializeButtons() {
    //New file button
    Button newFileButton = *new Button("New file", 0, 0, 90, 30); //button 0
    newFileButton.drawButton = []() {
        writeText(20, 25, "New file", COLOR(182, 182, 182), 1, COLOR(35, 35, 35));
        drawLine(90, 0, 90, 30, COLOR(118, 118, 118), 1);
        };
    newFileButton.onClick = []() {
        //TODO new file implementation
        printf("New file!\n");
        NewFile();
        //Create a new window with graphics.h and ask for the name of the file
        };
    newFileButton.drawButton();
    buttons.push_back(newFileButton);

    //Open file button
    Button openFileButton = *new Button("Open file", 90, 0, 180, 30); //button 1
    openFileButton.drawButton = []() {
        writeText(105, 25, "Open file", COLOR(182, 182, 182), 1, COLOR(35,35,35));
        drawLine(180, 0, 180, 30, COLOR(118, 118, 118), 1);
        };
    openFileButton.onClick = []() {
        string path = receivePathToFile();
        cout << path << '\n';
        setcurrentwindow(FIRST_WINDOW);
        setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
        if (path != "null")
            readFromFile(path.c_str()), renderSceneAgain = true;
        else
            printf("No file selected!\n");
        };
    openFileButton.drawButton();
    buttons.push_back(openFileButton);
    //Draw Line button
    Button draw_line = *new Button("Draw Line", 0, 100, 40, 140); //button 2
    draw_line.drawButton = [&draw_line]()
        {
            drawLine(0, 100, 40, 100, COLOR(118, 118, 118), 1);
            drawLine(0, 140, 40, 140, COLOR(118, 118, 118), 1);
            drawLine(30, 110, 10, 130);
        };
    draw_line.onClick = []()
        {
            setviewport(0, 0, getmaxx(), getmaxy(), 0);
            drawLine(0, 100, 40, 100, BLUE, 1);
            drawLine(0, 140, 40, 140, BLUE, 1);
            setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
            last_clicked_button = 2;
        };
    draw_line.drawButton();
    buttons.push_back(draw_line);

    //Draw rectangle button
    Button draw_rectangle = *new Button("Draw rectangle", 0, 150, 40, 190); //button 3
    draw_rectangle.drawButton = []()
        {
            drawLine(0, 150, 40, 150, COLOR(118, 118, 118), 1);
            drawLine(0, 190, 40, 190, COLOR(118, 118, 118), 1);
            drawEmptyRectangle(10, 160, 30, 180);
        };
    draw_rectangle.onClick = []()
        {
            setviewport(0, 0, getmaxx(), getmaxy(), 0);
            drawLine(0, 150, 40, 150, BLUE, 1);
            drawLine(0, 190, 40, 190, BLUE, 1);
            setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
            last_clicked_button = 3;
        };
    draw_rectangle.drawButton();
    buttons.push_back(draw_rectangle);

    //Draw circle button
    Button draw_circle = *new Button("Draw circle", 0, 200, 40, 240); //button 4
    draw_circle.drawButton = []()
        {
            drawLine(0, 200, 40, 200, COLOR(118, 118, 118), 1);
            drawLine(0, 240, 40, 240, COLOR(118, 118, 118), 1);
            drawEmptyCircle(20, 220, 12);
        };
    draw_circle.onClick = []()
        {
            setviewport(0, 0, getmaxx(), getmaxy(), 0);
            drawLine(0, 200, 40, 200, BLUE, 1);
            drawLine(0, 240, 40, 240, BLUE, 1);
            setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
            last_clicked_button = 4;
        };
    draw_circle.drawButton();
    buttons.push_back(draw_circle);

    //Add point button
    Button add_point = *new Button("Add point", 0, 250, 40, 290); //button 5
    add_point.drawButton = []()
        {
            drawLine(0, 250, 40, 250, COLOR(118, 118, 118), 1);
            drawLine(0, 290, 40, 290, COLOR(118, 118, 118), 1);
            drawEmptyCircle(20, 270, 2, WHITE, 3);
        };
    add_point.onClick = []()
        {
            setviewport(0, 0, getmaxx(), getmaxy(), 0);
            drawLine(0, 250, 40, 250, BLUE, 1);
            drawLine(0, 290, 40, 290, BLUE, 1);
            setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
            last_clicked_button = 5;
        };
    add_point.drawButton();
    buttons.push_back(add_point);

    //Link points button
    Button link_points = *new Button("Link points", 0, 300, 40, 340); //button 6
    link_points.drawButton = []()
        {
            drawLine(0, 300, 40, 300, COLOR(118, 118, 118), 1);
            drawLine(0, 340, 40, 340, COLOR(118, 118, 118), 1);
            drawLine(10, 320, 30, 320);
            drawEmptyCircle(10, 320, 2, WHITE, 3);
            drawEmptyCircle(30, 320, 2, WHITE, 3);
        };
    link_points.onClick = []()
        {
            setviewport(0, 0, getmaxx(), getmaxy(), 0);
            drawLine(0, 300, 40, 300, BLUE, 1);
            drawLine(0, 340, 40, 340, BLUE, 1);
            setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
            last_clicked_button = 6;
            if (S.corpuri_selectate.size() == 1)
            {
                int i = S.corpuri_selectate[0];
                for (auto& P : S.corpuri[i].puncte)
                {
                    Punct P1 = Punct::Punct3Dto2D(P);
                    drawEmptyCircle(P1.x, P1.y, 2, BLUE, 3);
                }
            }
        };
    link_points.drawButton();
    buttons.push_back(link_points);

    //Rotation angle buttons
    writeText(1130, 381, "Rotation angle:", COLOR(182, 182, 182), 1, COLOR(20,20,20)); //x = 1120 -> 1230, y = 355 -> 385

    Button angle_minus = *new Button("Angle minus", 1120, 390, 1170, 420); //button 7
    angle_minus.drawButton = []()
        {
            writeText(1125, 416, "Angle-", COLOR(182, 182, 182), 1, COLOR(20, 20, 20));
            drawEmptyRectangle(1120, 390, 1170, 420, COLOR(118, 118, 118), 1);
        };
    angle_minus.onClick = []()
        {
            default_angle -= 0.001;
        };
    angle_minus.drawButton();
    buttons.push_back(angle_minus);

    Button angle_plus = *new Button("Angle plus", 1180, 390, 1230, 420); //button 8
    angle_plus.drawButton = []()
        {
            writeText(1185, 416, "Angle+", COLOR(182, 182, 182), 1, COLOR(20, 20, 20));
            drawEmptyRectangle(1180, 390, 1230, 420, COLOR(118, 118, 118), 1);
        };
    angle_plus.onClick = []()
        {
            default_angle += 0.001;
        };
    angle_plus.drawButton();
    buttons.push_back(angle_plus);

    //Draw Precision buttons
    writeText(1130, 451, "Draw precision:", COLOR(182, 182, 182), 1, COLOR(20, 20, 20)); //x = 1120 -> 1230, y = 425 -> 455

    Button dp1 = *new Button("dp1", 1120, 460, 1154, 490); //button 9
    dp1.drawButton = []()
        {
            writeText(1129, 486, "1p", COLOR(182, 182, 182), 1, COLOR(20, 20, 20));
            drawEmptyRectangle(1120, 460, 1154, 490, BLUE, 1);
        };
    dp1.onClick = []()
        {
            draw_precision = 1;
            setviewport(0, 0, getmaxx(), getmaxy(), 0);
            drawEmptyRectangle(1120, 460, 1154, 490, BLUE, 1);
            if (getpixel(buttons[10].x1, buttons[10].y1) == BLUE)
                drawEmptyRectangle(buttons[10].x1, buttons[10].y1, buttons[10].x2, buttons[10].y2, COLOR(118, 118, 118), 1);
            else if(getpixel(buttons[11].x1, buttons[11].y1) == BLUE)
                drawEmptyRectangle(buttons[11].x1, buttons[11].y1, buttons[11].x2, buttons[11].y2, COLOR(118, 118, 118), 1);
            setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
        };
    dp1.drawButton();
    buttons.push_back(dp1);

    Button dp5 = *new Button("dp5", 1158, 460, 1192, 490); //button 10
    dp5.drawButton = []()
        {
            writeText(1167, 486, "5p", COLOR(182, 182, 182), 1, COLOR(20, 20, 20));
            drawEmptyRectangle(1158, 460, 1192, 490, COLOR(118, 118, 118), 1);
        };
    dp5.onClick = []()
        {
            draw_precision = 5;
            setviewport(0, 0, getmaxx(), getmaxy(), 0);
            drawEmptyRectangle(1158, 460, 1192, 490, BLUE, 1);
            if (getpixel(buttons[9].x1, buttons[9].y1) == BLUE)
                drawEmptyRectangle(buttons[9].x1, buttons[9].y1, buttons[9].x2, buttons[9].y2, COLOR(118, 118, 118), 1);
            else if (getpixel(buttons[11].x1, buttons[11].y1) == BLUE)
                drawEmptyRectangle(buttons[11].x1, buttons[11].y1, buttons[11].x2, buttons[11].y2, COLOR(118, 118, 118), 1);
            setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
        };
    dp5.drawButton();
    buttons.push_back(dp5);

    Button dp10 = *new Button("dp10", 1196, 460, 1230, 490); //button 11
    dp10.drawButton = []()
        {
            writeText(1201, 486, "10p", COLOR(182, 182, 182), 1, COLOR(20, 20, 20));
            drawEmptyRectangle(1196, 460, 1230, 490, COLOR(118, 118, 118), 1);
        };
    dp10.onClick = []()
        {
            draw_precision = 10;
            setviewport(0, 0, getmaxx(), getmaxy(), 0);
            drawEmptyRectangle(1196, 460, 1230, 490, BLUE, 1);
            if (getpixel(buttons[9].x1, buttons[9].y1) == BLUE)
                drawEmptyRectangle(buttons[9].x1, buttons[9].y1, buttons[9].x2, buttons[9].y2, COLOR(118, 118, 118), 1);
            else if (getpixel(buttons[10].x1, buttons[10].y1) == BLUE)
                drawEmptyRectangle(buttons[10].x1, buttons[10].y1, buttons[10].x2, buttons[10].y2, COLOR(118, 118, 118), 1);
            setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
        };
    dp10.drawButton();
    buttons.push_back(dp10);

    //Apply changes button
    Button apply_changes = *new Button("Apply changes", 1120, 505, 1230, 535); //button 12
    apply_changes.drawButton = []()
        {
            writeText(1131, 531, "Apply changes", COLOR(182, 182, 182), 1, COLOR(20, 20, 20));
            drawEmptyRectangle(1120, 505, 1230, 535, COLOR(118, 118, 118), 1);
        };
    apply_changes.onClick = []()
        {
            if (S.corpuri_selectate.size() == 1) S.ApplyChanges();
        };
    apply_changes.drawButton();
    buttons.push_back(apply_changes);

    //New 3D Form button
    Button new_3D_form = *new Button("New object", 1120, 540, 1230, 570); //button 13
    new_3D_form.drawButton = []()
        {
            writeText(1140, 566, "New object", COLOR(182, 182, 182), 1, COLOR(20, 20, 20));
            drawEmptyRectangle(1120, 540, 1230, 570, COLOR(118, 118, 118), 1);
        };
    new_3D_form.onClick = []()
        {
            S.AdaugareCorp();
        };
    new_3D_form.drawButton();
    buttons.push_back(new_3D_form);

    //Delete object button
    Button delete_object = *new Button("Delete object", 1120, 575, 1230, 605); //button 14
    delete_object.drawButton = []()
        {
            writeText(1135, 601, "Delete object", COLOR(182, 182, 182), 1, COLOR(20, 20, 20));
            drawEmptyRectangle(1120, 575, 1230, 605, COLOR(118, 118, 118), 1);
        };
    delete_object.onClick = []()
        {
            if (S.corpuri_selectate.size() == 1) S.EliminaCorp(S.corpuri_selectate[0]);
        };
    delete_object.drawButton();
    buttons.push_back(delete_object);

    //Reset object
    Button reset_object = *new Button("Reset object", 1120, 610, 1230, 640); //button 15
    reset_object.drawButton = []()
        {
            drawEmptyRectangle(1120, 610, 1230, 640, COLOR(118, 118, 118), 1);
            writeText(1138, 636, "Reset object", COLOR(182, 182, 182), 1, COLOR(20, 20, 20));
        };
    reset_object.onClick = []()
        {
            if (S.corpuri_selectate.size() == 1) S.ResetObject(S.corpuri_selectate[0]);
        };
    reset_object.drawButton();
    buttons.push_back(reset_object);
    //Reset scene
    Button reset_scene = *new Button("Reset scene", 1120, 645, 1230, 675); //button 16
    reset_scene.drawButton = []()
        {
            drawEmptyRectangle(1120, 645, 1230, 675, COLOR(118, 118, 118), 1);
            writeText(1140, 671, "Reset scene", COLOR(182, 182, 182), 1, COLOR(20, 20, 20));
        };
    reset_scene.onClick = []()
        {
            S.ResetScene();
        };
    reset_scene.drawButton();
    buttons.push_back(reset_scene);

    //Save file button
    Button saveFileButton = *new Button("Save file", 180, 0, 275, 30); //button 17
    saveFileButton.drawButton = []() {
        writeText(200, 25, "Save file", COLOR(182, 182, 182), 1, COLOR(35, 35, 35));
        drawLine(275, 0, 275, 30, COLOR(118, 118, 118), 1);
        };
    saveFileButton.onClick = []() {
        printf("Save file\n");
        SaveFile();

        };
    saveFileButton.drawButton();
    buttons.push_back(saveFileButton);

    //Edit button
    Button editButton = *new Button("Edit Corp", 1120, 60, 1230, 90); //button 18
    editButtonSelectable = false;
    editButton.drawButton = [editButton] {
        editButtonSelectable = true;
        drawFilledRectangle(editButton.x1, editButton.y1, editButton.x2, editButton.y2, COLOR(20,20,20));
        drawEmptyRectangle(editButton.x1, editButton.y1, editButton.x2, editButton.y2, WHITE);
        writeText(editButton.x1 + 25, editButton.y1 + 25, "Edit object", WHITE, 1, COLOR(20,20,20));
    };
    editButton.drawButtonDif = [editButton] {
        editButtonSelectable = false;
        drawEmptyRectangle(editButton.x1, editButton.y1, editButton.x2, editButton.y2, WHITE);
        writeText(editButton.x1 + 25, editButton.y1 + 25, "Edit object", WHITE, 1, COLOR(20, 20, 20));
        drawLine(editButton.x1, editButton.y1, editButton.x1 + 10, editButton.y2, WHITE);
        drawLine(editButton.x1 + 10, editButton.y1, editButton.x1 + 20, editButton.y2, WHITE);
        drawLine(editButton.x1 + 20, editButton.y1, editButton.x1 + 30, editButton.y2, WHITE);
        drawLine(editButton.x1 + 30, editButton.y1, editButton.x1 + 40, editButton.y2, WHITE);
        drawLine(editButton.x1 + 40, editButton.y1, editButton.x1 + 50, editButton.y2, WHITE);
        drawLine(editButton.x1 + 50, editButton.y1, editButton.x1 + 60, editButton.y2, WHITE);
        drawLine(editButton.x1 + 60, editButton.y1, editButton.x1 + 70, editButton.y2, WHITE);
        drawLine(editButton.x1 + 70, editButton.y1, editButton.x1 + 80, editButton.y2, WHITE);
        drawLine(editButton.x1 + 80, editButton.y1, editButton.x1 + 90, editButton.y2, WHITE);
        drawLine(editButton.x1 + 90, editButton.y1, editButton.x1 + 100, editButton.y2, WHITE);
        drawLine(editButton.x1 + 100, editButton.y1, editButton.x1 + 110, editButton.y2, WHITE);
    };
    editButton.onClick = [editButton] {
        if (editButtonSelectable && !editMode)
            EditObject();
        else if(!editMode)
            printf("Not selectable\n");
    };
    editButton.drawButtonDif();
    buttons.push_back(editButton);
}
