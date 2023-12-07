#include <graphics.h>
#include <winbgim.h>
#include "GlobalVariables.h"

static void CreateStartWindow(int width, int height, char name[] = "Window", int bg_color = BLACK, int startPosX = 0, int startPozY = 0) {
    int gdriver=0, gmode, errorcode;
    detectgraph(&gdriver, &gmode);
    initgraph(&gdriver, &gmode, "");
    errorcode = graphresult();
    //error
     if (errorcode != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        exit(1);
   }
   closegraph();
   initwindow(width, height, name, startPosX, startPozY);
   setbkcolor(bg_color);
   cleardevice();
   for(int i=0; i<=height; ++i) {
      for(int j=0; j<=width; ++j) {
         GB.MAPPED_COLORS[i][j] = bg_color;
      }
   }
}
void DrawStaticRectangle(int x1, int y1, int x2, int y2, int color = WHITE) {
   setfillstyle(SOLID_FILL, color);
   bar(x1, y1, x2, y2);
   for(int i=x1; i<=x2; ++i) {
      for(int j=y1; j<=y2; ++j) {
            GB.MAPPED_COLORS[i][j] = color;
      }
   }
}
void WriteText(int x, int y, char *text, int size = 1) {
    //TODO new implementation
   settextstyle(8,HORIZ_DIR, size);
   outtextxy(x, y, text);
}
