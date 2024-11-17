#pragma once
#define _USE_MATH_DEFINES
#include "graphics.h"
#include "GlobalVariables.h"
void InitializeWindow(int width = windowWidth, int height = windowHeight, char name[] = windowName, int bgColor = windowBgColor, int posX = windowPosX, int posY = windowPosY);
void drawFilledRectangle(int x1, int y1, int x2, int y2, int color = BLACK, int style = SOLID_FILL);
void drawLine(int x1, int y1, int x2, int y2, int color = WHITE, int thickness = 1, int style = SOLID_LINE);
void drawEmptyRectangle(int x1, int y1, int x2, int y2, int color = WHITE, int thickness = 1, int style = SOLID_LINE);

void drawEmptyCircle(int x, int y, int raza, int color = WHITE, int thickness = 1, int style = SOLID_LINE);
void writeText(int x, int y, char text[], int color = BLACK, int size = 1, int bgcolor = BLACK);