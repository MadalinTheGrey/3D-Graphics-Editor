#pragma once
#include "graphics.h"
#include "myGraphics.h"
#include "Button.h"
#include "Screenshot.h"

std::vector<Button> menuButtons;
std::vector<Button> points;
std::vector<Button> colors;
std::vector<int> sPoints;

bool _closeFacesWindow = false;
double _thisZoom = 1.0f;
int _thisOffsetX = 0;
int _thisOffsetY = 0;
int color = BLACK;

int curentVisualPage = 0;

Corp selectedC;

void Reload() {
	if (curentVisualPage == 0) {
		setactivepage(1);
		clearviewport();
		selectedC.AfisareCorpFete(_thisZoom, _thisOffsetX, _thisOffsetY);
		setvisualpage(1);
		curentVisualPage = 1;
	}
	else {
		setactivepage(0);
		clearviewport();
		selectedC.AfisareCorpFete(_thisZoom, _thisOffsetX, _thisOffsetY);
		setvisualpage(0);
		curentVisualPage = 0;
	}
}
void CreateFace() {
	printf("Yaaayy");
	if (sPoints.size() >= 3) {
		sPoints.push_back(color);
		selectedC.AdaugareFata(sPoints);
		Reload();
		sPoints.pop_back();
	}
	Sleep(500);
}
void SelectPoint(int index) {
	points[index].drawButtonDif();
	bool ok = true;
	for (auto x : sPoints) {
		if (x == index) {
			ok = false;
			break;
		}
	}
	if(ok)
		sPoints.push_back(index);
}
void Edit() {
	int index = 0;
	points.clear();
	sPoints.clear();
	for (auto& punct : selectedC.puncte) {
		Punct pct = Punct::Punct3Dto2D(punct);
		pct.x = _thisZoom * pct.x + _thisOffsetX;
		pct.y = _thisZoom * pct.y + _thisOffsetY;
		Button temp = *new Button(to_string(punct.x) + " " + to_string(punct.y) + " " + to_string(punct.z), pct.x - 4, pct.y - 4, pct.x + 4, pct.y + 4);
		temp.drawButton = [temp] {
			drawEmptyCircle((temp.x1 + temp.x2) / 2, (temp.y1 + temp.y2) / 2, 3*_thisZoom, RED, 5*_thisZoom);
			};
		temp.drawButtonDif = [temp] {
			drawEmptyCircle((temp.x1 + temp.x2) / 2, (temp.y1 + temp.y2) / 2, 3*_thisZoom, GREEN, 5*_thisZoom);
			};
		temp.onClick = [temp, index] {
			SelectPoint(index);
			};
		temp.drawButton();
		points.push_back(temp);
		index++;
	}
}
void Top() {
	setactivepage(0);
	drawFilledRectangle(0, 0, getmaxx(), 30, COLOR(35, 35, 35));
	setactivepage(1);
	drawFilledRectangle(0, 0, getmaxx(), 30, COLOR(35, 35, 35));
	setactivepage(0);
}
void Buttons() {
	setactivepage(0);
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
	Button save = *new Button("Save", 100, 0, 200, 30);
	save.drawButton = [save] {
		drawLine(save.x2, save.y1, save.x2, save.y2, COLOR(182, 182, 182));
		writeText(save.x1 + 35, save.y1 + 25, "Save", COLOR(182, 182, 182), 1, COLOR(35, 35, 35));
	};
	save.onClick = [] {
		S.corpuri[S.corpuri_selectate[0]] = selectedC;
		_closeFacesWindow = true;
	};
	save.drawButton();
	menuButtons.push_back(save);

	Button screenshot = *new Button("Screenshot", 200, 0, 350, 30);
	screenshot.drawButton = [screenshot] {
		drawLine(screenshot.x2, screenshot.y1, screenshot.x2, screenshot.y2, COLOR(182, 182, 182));
		writeText(screenshot.x1 + 35, screenshot.y1 + 25, "Screenshot", COLOR(182, 182, 182), 1, COLOR(35, 35, 35));
		};
	screenshot.onClick = [] {
		SaveScreenShot(1);
	};
	screenshot.drawButton();
	menuButtons.push_back(screenshot);
	//COLORS
	Button red = *new Button("red", 500, 0,530, 30);
	red.drawButton = [red] {
	drawFilledRectangle(red.x1, red.y1, red.x2, red.y2, RED);
	}; 
	red.drawButton();
	red.onClick = [] {
		color = RED;
		CreateFace();
	};
	Button yellow = *new Button("yellow", 530, 0, 560, 30);
	yellow.drawButton = [yellow] {
		drawFilledRectangle(yellow.x1, yellow.y1, yellow.x2, yellow.y2, YELLOW);
	}; 
	yellow.drawButton();
	yellow.onClick = [] {
		color = YELLOW;
		CreateFace();
	};
	Button blue = *new Button("blue", 560, 0, 590, 30);
	blue.drawButton = [blue] {
		drawFilledRectangle(blue.x1, blue.y1, blue.x2, blue.y2, BLUE);
	}; 
	blue.drawButton();
	blue.onClick = [] {
		color = BLUE;
		CreateFace();
	};
	Button lblue = *new Button("lblue", 590, 0, 620, 30);
	lblue.drawButton = [lblue] {
		drawFilledRectangle(lblue.x1, lblue.y1, lblue.x2, lblue.y2, LIGHTBLUE);
	}; 
	lblue.drawButton();
	lblue.onClick = [] {
		color = LIGHTBLUE;
		CreateFace();
	};
	Button green = *new Button("green", 620, 0, 650, 30);
	green.drawButton = [green] {
		drawFilledRectangle(green.x1, green.y1, green.x2, green.y2, GREEN);
	}; 
	green.drawButton();
	green.onClick = [] {
		color = GREEN;
		CreateFace();
	};
	Button lgreen = *new Button("lgreen", 650, 0, 680, 30);
	lgreen.drawButton = [lgreen] {
		drawFilledRectangle(lgreen.x1, lgreen.y1, lgreen.x2, lgreen.y2, LIGHTGREEN);
	}; 
	lgreen.drawButton();
	lgreen.onClick = [] {
		color = LIGHTGREEN;
		CreateFace();
	};
	Button white = *new Button("white", 680, 0, 710, 30);
	white.drawButton = [white] {
		drawFilledRectangle(white.x1, white.y1, white.x2, white.y2, WHITE);
	}; white.drawButton();
	white.onClick = [] {
		color = WHITE;
		CreateFace();
	};
	Button black = *new Button("black", 710, 0, 740, 30);
	black.drawButton = [black] {
		drawFilledRectangle(black.x1, black.y1, black.x2, black.y2, BLACK);
	}; 
	black.drawButton();
	black.onClick = [] {
		color = BLACK;
		CreateFace();
	};
	colors.push_back(red);
	colors.push_back(blue);
	colors.push_back(yellow);
	colors.push_back(lblue);
	colors.push_back(green);
	colors.push_back(lgreen);
	colors.push_back(white);
	colors.push_back(black);
	setactivepage(1);
	red.drawButton();
	blue.drawButton();
	yellow.drawButton();
	lblue.drawButton();
	green.drawButton();
	lgreen.drawButton();
	white.drawButton();
	black.drawButton();
	save.drawButton();
	edit.drawButton();
	close.drawButton();
	setactivepage(0);
}
void ShowFaces() {
	initwindow(1280, 720, "Faces", windowPosX, windowPosY);
	menuButtons.clear();
	colors.clear();
	_closeFacesWindow = false;
	_thisZoom = 1.0f;
	_thisOffsetX = 0;
	_thisOffsetY = 0;
	curentVisualPage = 0;
	selectedC = S.corpuri[S.corpuri_selectate[0]];

	Top();
	Buttons();
	setviewport(0, 30, 1280, 720, 1);
	setbkcolor(BLACK);
	selectedC.AfisareCorpFete(_thisZoom, _thisOffsetX, _thisOffsetY);


	while (!_closeFacesWindow) {
		
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			int x = mousex();
			int y = mousey();
			for (auto& b : menuButtons) {
				if (x > b.x1 && x < b.x2 && y > b.y1 && y < b.y2) {
					b.onClick();
				}
			}
			if (!_closeFacesWindow) {
				for (auto& b : colors) {
					if (x > b.x1 && x < b.x2 && y > b.y1 && y < b.y2 && !_closeFacesWindow) {
						b.onClick();
					}
				}
				y -= 30;
				for (auto& p : points) {
					if (x > p.x1 && x < p.x2 && y > p.y1 && y < p.y2) {
						p.onClick();
					}
				}
				printf("Points: ");
				for (auto x : sPoints) {
					printf("%i, ", x);
				}
				printf("\n");
			}
		}
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN)
			||GetAsyncKeyState(0x46) || GetAsyncKeyState(0x47) && !_closeFacesWindow) {
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
	curentVisualPage = 0;
	setcurrentwindow(1);
	setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
	setbkcolor(BLACK);
	renderSceneAgain = 1;
}