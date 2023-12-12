#ifndef MYGRAPHICS_H
#define MYGRAPHICS_H
#include <graphics.h>
#include "GlobalVariables.h"
static void InitializeWindow(int width = windowWidth, int height = windowHeight, char name[] = windowName, int bgColor = windowBgColor, int posX = windowPosX, int posY = windowPosY) {
    /**int gdriver=0, gmode, errorCode;
    detectgraph(&gdriver, &gmode);
    initgraph(&gdriver, &gmode, "");
    errorCode = graphresult();
    //error
    if (errorCode != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorCode));
        printf("Press any key to halt:");
        getch();
        exit(1);
    }
    closegraph();**/
    initwindow(width, height, name, posX, posY);
    setbkcolor(bgColor);
    cleardevice();
    for(int i = 0; i <= width; i++)
        for(int j = 0; j <= height; j++)
            colorsMapped[i][j] = bgColor;
    printf("Successfully initialized window...\n");
}
static void drawRectangle(int x1, int y1, int x2, int y2, int color = BLACK, int thickness = 1, int style = SOLID_LINE) {
    setcolor(color);
    setlinestyle(style, 0, thickness);
    rectangle(x1, y1, x2, y2);
}
static void drawFilledRectangle(int x1, int y1, int x2, int y2, int color = BLACK, int style = SOLID_FILL) {
    if(x1 < 0)
        x1 = 0;
    if(x2 > getmaxx())
        x2 = getmaxx();
    if(y1 < 0)
        y1 = 0;
    if(y2 > getmaxy())
        y2 = getmaxy();
    setfillstyle(SOLID_FILL, color);
    bar(x1, y1, x2, y2);
    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
            colorsMapped[i][j] = color;
}
void drawLine(int x1, int y1, int x2, int y2, int color = BLACK, int thickness = 1, int style = SOLID_LINE) {
    setcolor(color);
    setlinestyle(style, 0, thickness);
    line(x1, y1, x2, y2);
}
static void writeText(int x, int y, char text[], int color = BLACK, int size = 1, int vi = 0) {
    //TODO for string too
    setcolor(color);
    settextstyle(1, 0, 0);
    setusercharsize(1, 2, 1, 2);
    int x1 = x;
    int y1 = y - textheight(text);
    int x2 = x + textwidth(text);
    int y2 = y + textheight(text);
    if(vi == 0)
    {setviewport(x1, y1, x2, y2, 1);
        setbkcolor(colorsMapped[x][y]);}
    outtextxy(0, 0, text);
    setviewport(0, 0, getmaxx(), getmaxy(), 1);
}
#endif