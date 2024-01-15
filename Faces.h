#pragma once
#include "graphics.h"
#include "myGraphics.h"
#include "Button.h"

std::vector<Button> menuButtons;
std::vector<Button> points;
std::vector<int> sPoints;

bool _closeFacesWindow = false;
double _thisZoom = 1.0f;
int _thisOffsetX = 0;
int _thisOffsetY = 0;

void SelectPoint(int index) {
	points[index].drawButtonDif();
	sPoints.push_back(index);
}
void Edit() {
	Corp ct = S.corpuri[S.corpuri_selectate[0]];
	int index = 0;
	points.clear();
	sPoints.clear();
	for (auto& punct : ct.puncte) {
		Punct pct = Punct::Punct3Dto2D(punct);
		pct.x = _thisZoom * pct.x + _thisOffsetX;
		pct.y = _thisZoom * pct.y + _thisOffsetY;
		Button temp = *new Button(to_string(punct.x) + " " + to_string(punct.y) + " " + to_string(punct.z), pct.x - 4, pct.y - 4, pct.x + 4, pct.y + 4);
		temp.drawButton = [temp] {
			drawEmptyCircle((temp.x1 + temp.x2) / 2, (temp.y1 + temp.y2) / 2, 3, RED, 4);
			};
		temp.drawButtonDif = [temp] {
			drawEmptyCircle((temp.x1 + temp.x2) / 2, (temp.y1 + temp.y2) / 2, 3, GREEN, 4);
			};
		temp.onClick = [temp, index] {
			printf("Punct: %s\n", temp.name.c_str());
			SelectPoint(index);
			};
		temp.drawButton();
		points.push_back(temp);
		index++;
	}
}
void Top() {
	drawFilledRectangle(0, 0, getmaxx(), 30, COLOR(35, 35, 35));
}
void Buttons() {
	Button close = *new Button("Close", 1170, 0, 1270, 30);
	close.drawButton = [close] {
		drawLine(close.x1, close.y1, close.x1, close.y2, COLOR(182, 182, 182));
		drawLine(close.x2, close.y1, close.x2, close.y2, COLOR(182, 182, 182));
		writeText(close.x1 + 30, close.y1 + 25, "Close", COLOR(182,182,182), 1, COLOR(35, 35, 35));
	};
	close.onClick = [] {
		printf("Close\n");
		_closeFacesWindow = true;
	};
	close.drawButton();
	menuButtons.push_back(close);
	Button edit = *new Button("Edit", 0, 0, 100, 30);
	edit.drawButton = [edit] {
		drawLine(edit.x2, edit.y1, edit.x2, edit.y2, COLOR(182, 182, 182));
		writeText(edit.x1 + 35, edit.y1 + 25, "Edit", COLOR(182,182,182), 1, COLOR(35,35,35));
	};
	edit.onClick = [] {
		Edit();
	};
	edit.drawButton();
	menuButtons.push_back(edit);
}
void Reload() {
	clearviewport();
	S.corpuri[S.corpuri_selectate[0]].AfisareCorpFete(_thisZoom, _thisOffsetX, _thisOffsetY);
}
void ShowFaces() {
	initwindow(1280, 720, "Faces", windowPosX, windowPosY);
	menuButtons.clear();
	_closeFacesWindow = false;

	Top();
	Buttons();
	setviewport(0, 30, 1280, 720, 1);
	setbkcolor(BLACK);
	S.corpuri[S.corpuri_selectate[0]].AfisareCorpFete(_thisZoom, _thisOffsetX, _thisOffsetY);


	while (!_closeFacesWindow) {
		
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			int x = mousex();
			int y = mousey();
			for (auto& b : menuButtons) {
				if (x > b.x1 && x < b.x2 && y > b.y1 && y < b.y2) {
					b.onClick();
				}
			}
			y -= 30;
			for (auto& p : points) {
				if (x > p.x1 && x < p.x2 && y > p.y1 && y < p.y2) {
					p.onClick();
				}
			}
		}
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)
			||GetAsyncKeyState(0x46) || GetAsyncKeyState(0x47)) {
			if (GetAsyncKeyState(0x46)) {
				_thisZoom += 0.01f;
			}
			if (GetAsyncKeyState(0x47)) {
				_thisZoom -= 0.01f;
			}
			if (GetAsyncKeyState(VK_LEFT)) {
				_thisOffsetX -= 10;
			}
			if (GetAsyncKeyState(VK_RIGHT)) {
				_thisOffsetX += 10;
			}
			if (GetAsyncKeyState(VK_UP)) {
				_thisOffsetY -= 10;
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				_thisOffsetY += 10;
			}
			Reload();
		}
		Sleep(10);
	}

	closegraph(CURRENT_WINDOW);
	setcurrentwindow(1);
	setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
	setbkcolor(BLACK);
	renderSceneAgain = 1;
}