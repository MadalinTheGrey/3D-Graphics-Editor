#ifndef INC_3D_EDITOR_V2_RENDER3D_H
#define INC_3D_EDITOR_V2_RENDER3D_H

#include <iostream>
#include <vector>
#include "Corp.h"
#include "FilesManager.h"

void render3D() {
    setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
    setbkcolor(BLACK);
    clearviewport();
    //renderAdditionallyLines(0, 0, getmaxx(), getmaxy(), offsetX, offsetY, zoom);
    Corp corp = S.corpuri[0];
    corp.AfisareCorp();
    while(true) {
        if(GetAsyncKeyState(VK_ESCAPE) != 0)
            break;
        else if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)
                || GetAsyncKeyState(0x57) || GetAsyncKeyState(0x53) || GetAsyncKeyState(	0x41) || GetAsyncKeyState(0x44) ||
                GetAsyncKeyState(0x5A) || GetAsyncKeyState(0x58) || GetAsyncKeyState(0x46) || GetAsyncKeyState(0x47)
                || GetAsyncKeyState(0x31) || GetAsyncKeyState(0x32) || GetAsyncKeyState(0x33) || GetAsyncKeyState(0x34)
                || GetAsyncKeyState(0x35) || GetAsyncKeyState(0x36)) {
            if(GetAsyncKeyState(VK_LEFT)) {
                for(auto &P : corp.puncte)
                    P.x -= 10;
            } if(GetAsyncKeyState(VK_RIGHT)) {
                for(auto& P : corp.puncte)
                    P.x += 10;
            } if(GetAsyncKeyState(VK_UP)) {
                for(auto& P : corp.puncte)
                    P.y -= 10;
            } if(GetAsyncKeyState(VK_DOWN)) {
                for(auto& P : corp.puncte)
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
                for(auto& P : corp.puncte)
                    P.z -= 10;
            } if(GetAsyncKeyState(0x58)) {
                for(auto& P : corp.puncte)
                    P.z += 10;
            } if(GetAsyncKeyState(0x46)) { //F
                zoom+=0.01;
            } if(GetAsyncKeyState(0x47)) { //G
                zoom-=0.01;
            } if(GetAsyncKeyState(0x31)) { //1
                corp.RotesteXPoz();
            } if(GetAsyncKeyState(0x32)) { //2
                corp.RotesteXNeg();
            } if(GetAsyncKeyState(0x33)) { //3
                corp.RotesteYPoz();
            } if(GetAsyncKeyState(0x34)) { //4
                corp.RotesteYNeg();
            } if(GetAsyncKeyState(0x35)) { //5
                corp.RotesteZPoz();
            } if(GetAsyncKeyState(0x36)) { //6
                corp.RotesteZNeg();
            }
            clearviewport();
            //renderAdditionallyLines(0, 0, getmaxx(), getmaxy(), offsetX, offsetY, zoom);
            corp.DeterminaCentru();
            corp.AfisareCorp();
        }
        delay(1);
    }
}

void LoadFromFile()
{
    std::vector<Corp> corpuri;
    Corp corp;
    corp = readFromFile("D:\\Andrei\\Desktop\\My Projects\\3D Editor V2\\SavedObjects\\Corp1.txt");
    corpuri.push_back(corp);
    Scena Scene(corpuri);
    S = Scene;
    render3D();
}

#endif //INC_3D_EDITOR_V2_RENDER3D_H
