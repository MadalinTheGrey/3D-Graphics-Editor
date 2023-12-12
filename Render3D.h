//
// Created by andre on 12/11/2023.
//

#ifndef INC_3D_EDITOR_RENDER3D_H
#define INC_3D_EDITOR_RENDER3D_H
#include "FilesManager.h"
#include "myGraphics.h"
void renderAdditionallyLines(int x1, int y1, int x2, int y2, int offset){
    for(int i=100-offset; i<=x2; i+=100) {
        drawLine(i, y1, i, y2, COLOR(50, 50, 50), 1, DOTTED_LINE);
        //writeText(i,y1, "i", COLOR(50, 50, 50), 1, 1);
    }
    for(int i=100; i<=y2; i+=100)
        drawLine(x1, i, x2, i, COLOR(50,50,50), 1, DOTTED_LINE);
}

void render3D() {
    int offset = 0;
    int zoom = 100;
    setviewport(0, 30, 1080, 720, 1);
    setbkcolor(BLACK);
    clearviewport();
    Scena scena = readFromFile();
    renderAdditionallyLines(0, 0, getmaxx(), getmaxy(), 0);
    for(auto corp : scena.corpuri)
        corp.AfisareCorp();
    while(GetAsyncKeyState(VK_ESCAPE) == 0) {
        printf("Waiting for input...\n");
        //delay(100);
        char c = (char) getch();
        if(c != 0) {
            printf("Pressed %c\n", c);
            if(c == 'a')
                offset+=20;
            else if(c == 'd')
                offset-=20;
            else if(c == 'x')
                zoom+=100;
            else if(c == 'z')
                zoom-=100;
            clearviewport();
            renderAdditionallyLines(0,0, getmaxx(), getmaxy(), offset);
            for(auto corp : scena.corpuri) {
                corp.AfisareCorp(offset, zoom);
            }
        }
        else {
            c = (char) getch();
            if(c == KEY_UP) {
                for(auto & corp : scena.corpuri)
                    for(auto & punct : corp.puncte3D)
                        punct.y-=7;
            }else if(c == KEY_DOWN) {
                for(auto & corp : scena.corpuri)
                    for(auto & punct : corp.puncte3D)
                        punct.y+=7;
            }else if(c == KEY_LEFT) {
                for(auto & corp : scena.corpuri)
                    for(auto & punct : corp.puncte3D)
                        punct.x-=7;
            }else if(c == KEY_RIGHT) {
                for(auto & corp : scena.corpuri)
                    for(auto & punct : corp.puncte3D)
                        punct.x+=7;
            }
            clearviewport();
            for(auto corp : scena.corpuri)
                corp.AfisareCorp(offset, zoom);
            renderAdditionallyLines(0,0, getmaxx(), getmaxy(), offset);
            c=0;
        }
    }
}

#endif //INC_3D_EDITOR_RENDER3D_H
