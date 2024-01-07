#pragma once
#include "GlobalVariables.h"
#include <stdio.h>
bool _closeSaveWindow = false;

void SaveFile() {
	_closeSaveWindow = false;
	string path = current_file;

	initwindow(410, 110, "Save File", 500, 300);
	int x1 = 10, y1 = 10, x2 = 390, y2 = 50;
	drawEmptyRectangle(x1, y1, x2, y2, WHITE);
	Button saveButton = *new Button("Save File", 40, 50, 190, 100);
	saveButton.drawButton = [saveButton] {
		drawEmptyRectangle(saveButton.x1 + 10, saveButton.y1 + 10, saveButton.x2 - 10, saveButton.y2 - 10, COLOR(100, 100, 100));
		writeText(saveButton.x1 + 45, saveButton.y1 + 35, "Save file", WHITE);
	};
	saveButton.onClick = [&path] {
		path = path.substr(0, path.length() - 1);
		path += ".txt";
		SaveObjectInFile(path);
		_closeSaveWindow = true;
	};
	saveButton.drawButton();
	Button cancelButton = *new Button("Cancel", 210, 50, 360, 100);
	cancelButton.drawButton = [&cancelButton] {
		drawEmptyRectangle(cancelButton.x1 + 10, cancelButton.y1 + 10, cancelButton.x2 - 10, cancelButton.y2 - 10, COLOR(100, 100, 100));
		writeText(cancelButton.x1 + 50, cancelButton.y1 + 35, "Cancel", WHITE);
	};
	cancelButton.onClick = [] {
		_closeSaveWindow = true;
	};
	cancelButton.drawButton();
	path = path.substr(0, path.length() - 4);
	path += "|";
	writeText(x1 + 10, y1 + 30, (char*)path.c_str(), WHITE);
	while (!_closeSaveWindow) {
		if (GetAsyncKeyState(VK_LBUTTON)) {
			int x = mousex(); int y = mousey();
			if (x > cancelButton.x1 && x < cancelButton.x2 && y > cancelButton.y1 && y < cancelButton.y2) {
				cancelButton.onClick();
			}
			else if (x > saveButton.x1 && x < saveButton.x2 && y > saveButton.y1 && y < saveButton.y2) {
				saveButton.onClick();
			}
		}
		else if (!_closeSaveWindow) {
			bool ok = false;
			if (GetAsyncKeyState(0x41)) { // A
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'A';
				else 
					path += 'a'; 
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x42)) { // B
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'B';
				else
					path += 'b';  
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x43)) { // C
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'C';
				else
					path += 'c';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x44)) { // D
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'D';
				else
					path += 'd';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x45)) { // E
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'E';
				else
					path += 'e';				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x46)) { // F
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'F';
				else
					path += 'f';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x47)) { // G
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'G';
				else
					path += 'g';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x48)) { // H
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'H';
				else
					path += 'h';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x49)) { // I
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'I';
				else
					path += 'i';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4A)) { // J
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'J';
				else
					path += 'j';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4B)) { // K
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'K';
				else
					path += 'k';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4C)) { // L
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'L';
				else
					path += 'l';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4D)) { // M
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'M';
				else
					path += 'm';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4E)) { // N
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'N';
				else
					path += 'n';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4F)) { // O
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'O';
				else
					path += 'o';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x50)) { // P
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'P';
				else
					path += 'p';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x51)) { // Q
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'Q';
				else
					path += 'q';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x52)) { // R
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'R';
				else
					path += 'r';				
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x53)) { // S
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'S';
				else
					path += 's';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x54)) { // T
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'T';
				else
					path += 't';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x55)) { // U
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'U';
				else
					path += 'u';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x56)) { // V
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'V';
				else
					path += 'v';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x57)) { // W
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'W';
				else
					path += 'w';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x58)) { // X
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'X';
				else
					path += 'x';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x59)) { // Y
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'Y';
				else
					path += 'y';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x5A)) { // Z
				path = path.substr(0, path.length()-1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'Z';
				else
					path += 'z';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x30)) { // 0
				path = path.substr(0, path.length()-1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += ')';
				else
					path += '0';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x31)) { // 1
				path = path.substr(0, path.length()-1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '!';
				else
					path += '1';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x32)) { // 2
				path = path.substr(0, path.length()-1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '@';
				else
					path += '2';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x33)) { // 3
				path = path.substr(0, path.length()-1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '#';
				else
					path += '3';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x34)) { // 4
				path = path.substr(0, path.length()-1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '$';
				else
					path += '4';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x35)) { // 5
				path = path.substr(0, path.length()-1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '%';
				else
					path += '5';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x36)) { // 6
				path = path.substr(0, path.length()-1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '^';
				else
					path += '6';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x37)) { // 7
				path = path.substr(0, path.length()-1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '&';
				else
					path += '7';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x38)) { // 8
				path = path.substr(0, path.length()-1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '*';
				else
					path += '8';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x39)) { // 9
				path = path.substr(0, path.length()-1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '(';
				else
					path += '9';
				ok = true;
				path += "|";
				}
			else if (GetAsyncKeyState(VK_SPACE)) {
				path = path.substr(0, path.length() - 1);
				ok = true;
				path += " ";
				path += "|";
			}
			else if (GetAsyncKeyState(VK_BACK) && path.length() > 1) {
				path = path.substr(0, path.length() - 2); 
				ok = true;
				path += "|";
			}
			if (ok == true) {
				drawFilledRectangle(x1 + 5,y1 + 5,x2 - 5,y2 - 5);
				writeText(x1 + 10, y1 + 30, (char*)path.c_str(), WHITE, 1, BLACK);
			}
		}
		if (_closeSaveWindow) {
			closegraph(CURRENT_WINDOW);
		}
		delay(100);
	}
	setcurrentwindow(1);
	setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
	
}