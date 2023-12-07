#include <graphics.h>
#include "Button.h"
void InitializeMenu() {
    DrawStaticRectangle(0, 0, getmaxx(), 30, COLOR(35, 35, 35));
    DrawStaticRectangle(1080, 30, getmaxx(), getmaxy(), COLOR(20, 20, 20));
    DrawStaticRectangle(getmaxx() - 200, 30, getmaxx(),getmaxy(), COLOR(20, 20, 20));
    DrawStaticRectangle(0, 100, 40, getmaxy() - 100, COLOR(20, 20, 20));
    
    Button newFile(0, 0, 100, 30);
    //DrawStaticRectangle(newFile.Xs, newFile.Ys, newFile.Xd, newFile.Yd, RED);
    WriteText(5, 5, "New File", 2);
    for(int i=0; i<=100; ++i) {
        for(int j=0; j<=30; ++j) {
            GB.MAPPED_BUTTONS[i][j] = 1;
        }
    }
}