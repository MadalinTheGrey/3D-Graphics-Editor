#ifndef INC_3D_EDITOR_V2_RENDER3D_H
#define INC_3D_EDITOR_V2_RENDER3D_H

#include <iostream>
#include <vector>
#include "Corp.h"
#include "FilesManager.h"

int renderAgain = 0;
int currentWindow = 1;

void render3D() {
    setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
    setbkcolor(BLACK);
    clearviewport();
    //renderAdditionallyLines(0, 0, getmaxx(), getmaxy(), offsetX, offsetY, zoom);
    S.IncarcaScena();
    while(true) {
        if(GetAsyncKeyState(VK_ESCAPE) != 0)
            break;
        else if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)
            || GetAsyncKeyState(0x57) || GetAsyncKeyState(0x53) || GetAsyncKeyState(0x41) || GetAsyncKeyState(0x44) ||
            GetAsyncKeyState(0x5A) || GetAsyncKeyState(0x58) || GetAsyncKeyState(0x46) || GetAsyncKeyState(0x47)
            || GetAsyncKeyState(0x31) || GetAsyncKeyState(0x32) || GetAsyncKeyState(0x33) || GetAsyncKeyState(0x34)
            || GetAsyncKeyState(0x35) || GetAsyncKeyState(0x36) || renderAgain) && currentWindow) {
            if(GetAsyncKeyState(VK_LEFT)) {
                for(auto& C : S.corpuri)
                    for(auto &P : C.puncte)
                        P.x -= 10;
            } if(GetAsyncKeyState(VK_RIGHT)) {
                for(auto& C : S.corpuri)
                    for(auto& P : C.puncte)
                        P.x += 10;
            } if(GetAsyncKeyState(VK_UP)) {
                for(auto& C : S.corpuri)
                    for(auto& P : C.puncte)
                        P.y -= 10;
            } if(GetAsyncKeyState(VK_DOWN)) {
                for(auto& C : S.corpuri)
                    for(auto& P : C.puncte)
                        P.y += 10;
            } if(GetAsyncKeyState(0x57)) { //W
                offsetY+=10;
            } if(GetAsyncKeyState(	0x53)) { //S
                offsetY-=10;
            } if(GetAsyncKeyState(	0x41)) { //A
                offsetX+=10;
            } if(GetAsyncKeyState(0x44)) { //D
                offsetX-=10;
            } if(GetAsyncKeyState(0x5A)) {
                for(auto& C : S.corpuri)
                    for(auto& P : C.puncte)
                        P.z -= 10;
            } if(GetAsyncKeyState(0x58)) {
                for (auto& C : S.corpuri)
                    for(auto& P : C.puncte)
                        P.z += 10;
            } if(GetAsyncKeyState(0x46)) { //F
                zoom+=0.01;
            } if(GetAsyncKeyState(0x47)) { //G
                zoom-=0.01;
            } if(GetAsyncKeyState(0x31)) { //1
                for(auto &i : S.corpuri_selectate)
                    S.corpuri[i].RotesteXPoz();
            } if(GetAsyncKeyState(0x32)) { //2
                for(auto &i : S.corpuri_selectate)
                    S.corpuri[i].RotesteXNeg();
            } if(GetAsyncKeyState(0x33)) { //3
                for (auto& i : S.corpuri_selectate)
                    S.corpuri[i].RotesteYPoz();
            } if(GetAsyncKeyState(0x34)) { //4
                for (auto& i : S.corpuri_selectate)
                    S.corpuri[i].RotesteYNeg();
            } if(GetAsyncKeyState(0x35)) { //5
                for (auto& i : S.corpuri_selectate)
                    S.corpuri[i].RotesteZPoz();
            } if(GetAsyncKeyState(0x36)) { //6
                for (auto& i : S.corpuri_selectate)
                    S.corpuri[i].RotesteZNeg();
            }
            clearviewport();
            //renderAdditionallyLines(0, 0, getmaxx(), getmaxy(), offsetX, offsetY, zoom);
            S.IncarcaScena();
            if (renderAgain)
                renderAgain = 0;
        }
        delay(1);
    }
}

#endif //INC_3D_EDITOR_V2_RENDER3D_H
