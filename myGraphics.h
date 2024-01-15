#ifndef INC_3D_EDITOR_V2_MYGRAPHICS_H
#define INC_3D_EDITOR_V2_MYGRAPHICS_H
#define _USE_MATH_DEFINES
#include "graphics.h"
#include "GlobalVariables.h"
static void InitializeWindow(int width = windowWidth, int height = windowHeight, char name[] = windowName, int bgColor = windowBgColor, int posX = windowPosX, int posY = windowPosY) {
    int gdriver = 0, gmode = 0, errorCode;
    detectgraph(&gdriver, &gmode);
    initgraph(&gdriver, &gmode, "");
    errorCode = graphresult();
    //error
    if (errorCode != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorCode));
    }
    closegraph();
    initwindow(width, height, name, posX, posY);
    setbkcolor(bgColor);
    cleardevice();
}
static void drawFilledRectangle(int x1, int y1, int x2, int y2, int color = BLACK, int style = SOLID_FILL) {
    if (x1 < 0)
        x1 = 0;
    if (x2 > getmaxx())
        x2 = getmaxx();
    if (y1 < 0)
        y1 = 0;
    if (y2 > getmaxy())
        y2 = getmaxy();
    setfillstyle(SOLID_FILL, color);
    bar(x1, y1, x2, y2);
}
static void drawLine(int x1, int y1, int x2, int y2, int color = WHITE, int thickness = 1, int style = SOLID_LINE) {
    setcolor(color);
    setlinestyle(style, 0, thickness);
    line(x1, y1, x2, y2);
}
static void drawEmptyRectangle(int x1, int y1, int x2, int y2, int color = WHITE, int thickness = 1, int style = SOLID_LINE)
{
    /*struct viewporttype vinfo;
    getviewsettings(&vinfo);
    if (x1 < vinfo.left)
        x1 = vinfo.left;
    if (x2 > vinfo.right)
        x2 = vinfo.right;
    if (y1 < vinfo.top)
        y1 = vinfo.top;
    if (y2 > vinfo.bottom)
        y2 = vinfo.bottom;*/
    drawLine(x1, y1, x2, y1, color, thickness, style);
    drawLine(x1, y1, x1, y2, color, thickness, style);
    drawLine(x1, y2, x2, y2, color, thickness, style);
    drawLine(x2, y1, x2, y2, color, thickness, style);
}

static void drawEmptyCircle(int x, int y, int raza, int color = WHITE, int thickness = 1, int style = SOLID_LINE)
{
    setcolor(color);
    setlinestyle(style, 0, thickness);
    circle(x, y, raza);
}
static void writeText(int x, int y, char text[], int color = BLACK, int size = 1, int bgcolor = BLACK) {
    struct viewporttype oldV;
    getviewsettings(&oldV);
    setcolor(color);
    settextstyle(1, 0, 0);
    setusercharsize(1, 2, 1, 2); //multx / divx, multy / divy
    int x1 = x;
    int y1 = y - textheight(text);
    int x2 = x + textwidth(text);
    int y2 = y + textheight(text);
    if (x1 < oldV.left)
        x1 = oldV.left;
    if (x2 > oldV.right)
        x2 = oldV.right;
    if (y1 < oldV.top)
        y1 = oldV.top;
    if (y2 > oldV.bottom)
        y2 = oldV.bottom;
    setviewport(x1, y1, x2, y2, 1);
    setbkcolor(bgcolor);
    outtextxy(0, 0, text);
    setviewport(oldV.left, oldV.top, oldV.right, oldV.bottom, 1);
}
#endif //INC_3D_EDITOR_V2_MYGRAPHICS_H
