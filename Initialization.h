#pragma once
#include "myGraphics.h"
#include "ButtonManager.h"

static void InitializeMenu() {
    drawFilledRectangle(0, 0, getmaxx(), 30, COLOR(35, 35, 35));
    drawFilledRectangle(1080, 30, getmaxx(), getmaxy(), COLOR(20, 20, 20));
    drawFilledRectangle(0, 30, 40, getmaxy(), COLOR(20, 20, 20));
}
static void InitializeInterface() {
    setactivepage(0);
    InitializeMenu();

    setactivepage(1);
    InitializeMenu();
    setactivepage(0);

    InitializeButtons();
}