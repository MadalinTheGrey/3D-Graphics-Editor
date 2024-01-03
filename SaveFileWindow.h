#pragma once
#include "graphics.h"
#include "Button.h"
#include "Render3D.h"
#include "ButtonManager.h"
Button saveButton("Save", 0, 60, 400, 100);
int closeWindow = 0; char c;
void CLW() {
	c = 0;
	closeWindow = 1;
	return;
}
void SaveFile() {
	closeWindow = 0;
	string path = current_file;
	path = path.substr(0, path.length() - 4);
	initwindow(400, 100, "Save File", 500, 300);
	drawFilledRectangle(0, 0, 400, 60, COLOR(20,20,20));
	saveButton.drawButton =[] {
		writeText(getmaxx()/2 - textwidth("Save"), textheight("Save") + 65, "Save", WHITE,1,0,BLACK);
	};
	writeText(10, 40, (char*)path.c_str(), COLOR(255, 255, 255), 1, 0, COLOR(20, 20, 20));
	saveButton.onClick = [&path] {
		CLW();
		SaveObjectInFile(path + ".txt");
		};
	saveButton.drawButton();
	while (closeWindow == 0) {
		if(GetAsyncKeyState(VK_ESCAPE)) {
			closeWindow = 1;
			return;
		}
		else if (closeWindow == 0) {
			bool ok = false;
			if(GetAsyncKeyState(VK_LBUTTON)) {
				if (mousex() >= 0 && mousex() <= 400 && mousey() >= 60 && mousey() <= 100) {
					saveButton.onClick();
					closegraph(CURRENT_WINDOW);
				};
			}else if (GetAsyncKeyState(0x41)) { // A
				path += 'a'; ok = true;
			} else if(GetAsyncKeyState(0x42)) { // B
				path += 'b'; ok = true;
			} else if(GetAsyncKeyState(0x43)) { // C
				path += 'c'; ok = true;
			} else if(GetAsyncKeyState(0x44)) { // D
				path += 'd'; ok = true;
			} else if(GetAsyncKeyState(0x45)) { // E
				path += 'e'; ok = true;
			} else if(GetAsyncKeyState(0x46)) { // F
				path += 'f'; ok = true;
			} else if(GetAsyncKeyState(0x47)) { // G
				path += 'g'; ok = true;
			} else if(GetAsyncKeyState(0x48)) { // H
				path += 'h'; ok = true;
			} else if(GetAsyncKeyState(0x49)) { // I
				path += 'i'; ok = true;
			} else if(GetAsyncKeyState(0x4A)) { // J
				path += 'j'; ok = true;
			} else if(GetAsyncKeyState(0x4B)) { // K
				path += 'k'; ok = true;
			} else if(GetAsyncKeyState(0x4C)) { // L
				path += 'l'; ok = true;
			} else if(GetAsyncKeyState(0x4D)) { // M
				path += 'm'; ok = true;
			} else if(GetAsyncKeyState(0x4E)) { // N
				path += 'n'; ok = true;
			} else if(GetAsyncKeyState(0x4F)) { // O
				path += 'o'; ok = true;
			} else if(GetAsyncKeyState(0x50)) { // P
				path += 'p'; ok = true;
			} else if(GetAsyncKeyState(0x51)) { // Q
				path += 'q'; ok = true;
			} else if(GetAsyncKeyState(0x52)) { // R
				path += 'r'; ok = true;
			} else if(GetAsyncKeyState(0x53)) { // S
				path += 's'; ok = true;
			} else if(GetAsyncKeyState(0x54)) { // T
				path += 't'; ok = true;
			} else if(GetAsyncKeyState(0x55)) { // U
				path += 'u'; ok = true;
			} else if(GetAsyncKeyState(0x56)) { // V
				path += 'v'; ok = true;
			} else if(GetAsyncKeyState(0x57)) { // W
				path += 'w'; ok = true;
			} else if(GetAsyncKeyState(0x58)) { // X
				path += 'x'; ok = true;
			} else if(GetAsyncKeyState(0x59)) { // Y
				path += 'y'; ok = true;
			} else if(GetAsyncKeyState(0x5A)) { // Z
				path += 'z'; ok = true;
			} else if(GetAsyncKeyState(0x30)) { // 0
				path += '0'; ok = true;
			} else if(GetAsyncKeyState(0x31)) { // 1
				path += '1'; ok = true;
			} else if(GetAsyncKeyState(0x32)) { // 2
				path += '2'; ok = true;
			} else if(GetAsyncKeyState(0x33)) { // 3
				path += '3'; ok = true;
			} else if(GetAsyncKeyState(0x34)) { // 4
				path += '4'; ok = true;
			} else if(GetAsyncKeyState(0x35)) { // 5
				path += '5'; ok = true;
			} else if(GetAsyncKeyState(0x36)) { // 6
				path += '6'; ok = true;
			} else if(GetAsyncKeyState(0x37)) { // 7
				path += '7'; ok = true;
			} else if(GetAsyncKeyState(0x38)) { // 8
				path += '8'; ok = true;
			} else if(GetAsyncKeyState(0x39)) { // 9
				path += '9'; ok = true;
			} else if(GetAsyncKeyState(VK_BACK) && path.length() >= 1) {
				path = path.substr(0, path.length() - 1); ok = true;
			}
			if(ok == true) {
				drawFilledRectangle(0, 0, 400, 60, COLOR(20, 20, 20));
				writeText(10, 40, (char*)path.c_str(), COLOR(255, 255, 255), 1, 0, COLOR(20, 20, 20));
			}
			delay(100);
		}
	}
	closegraph(CURRENT_WINDOW);
}