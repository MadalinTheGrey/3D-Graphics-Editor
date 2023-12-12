#include "myGraphics.h"
#include "Button.h"

static void InitializeMenu() {
    drawFilledRectangle(0, 0, getmaxx(), 30, COLOR(35, 35, 35));
    drawFilledRectangle(1080, 30, getmaxx(), getmaxy(), COLOR(20, 20, 20));
    drawFilledRectangle(0, 100, 40, getmaxy() - 100, COLOR(20, 20, 20));
}
static void InitializeInterface() {
    InitializeMenu();
    InitializeButtons();
}