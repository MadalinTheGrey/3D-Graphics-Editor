#pragma once
#include <stdio.h>
#include "Button.h"
#include "ButtonManager.h"
#include <set>
vector<Button> strats;
vector<Button> menuStratsButtons;
set<int> extraAddedStrats;

int stratsOffset = 0;
void SelectStrat(int s) {
	selectedStrat = s;
	setviewport(0, 0, 1280, 720, 1);
	drawFilledRectangle(1080, 30, 1280, 300, COLOR(20, 20, 20));
	for (auto& st : strats) {
		if (st.name == to_string(s)) {
			st.drawButtonDif();
		}
		else {
			st.drawButton();
		}
	}
	setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
	setbkcolor(BLACK);
}
void DisplayStrats(bool resetSts = true) {
	setviewport(0, 0, 1280, 720, 1);
	drawFilledRectangle(1080, 30, 1280, 300, COLOR(20,20,20));
	//drawFilledRectangle(1080, 300, 1280, 350, BLUE);
	strats.clear();
	set<int> sts;
	for (auto& sect : S.corpuri[selectedCorp].sectiuni) {
		sts.insert(sect.z);
	}
	for (auto x : extraAddedStrats) {
		sts.insert(x);
	}
	int y = 30;
	for (auto s : sts) {
		Button temp = *new Button(to_string(s), 1080, y + stratsOffset, 1280, y + 30 + stratsOffset);
		temp.drawButton = [temp, y] {
			if (temp.y1 >= 30 && temp.y2 <= 300) {
				drawEmptyRectangle(temp.x1, temp.y1, temp.x2 - 12, temp.y2, WHITE);
				writeText(temp.x1 + 10, temp.y1 + 25, (char*)("Strat: " + temp.name).c_str(), WHITE, 1, COLOR(20, 20, 20));
			}
		};
		temp.drawButtonDif = [temp, y] {
			if (temp.y1 >= 30 && temp.y2 <= 300) {
				drawEmptyRectangle(temp.x1, temp.y1, temp.x2 - 12, temp.y2, WHITE);
				writeText(temp.x1 + 10, temp.y1 + 25, (char*)("Strat: " + temp.name + " -------------------").c_str(), GREEN, 1, COLOR(20, 20, 20));
			}
			};
		temp.onClick = [temp, s] {
			if (temp.y1 >= 30 && temp.y2 <= 300) {
				printf("Selected strat: %i\n", s);
				SelectStrat(s);
				renderSceneAgain = 1;
			}
		};
		temp.drawButton();
		strats.push_back(temp);
		y += 30;
	}
	setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
	setbkcolor(BLACK);
}
void AddNewStrat() {
	bool finished = false;
	setviewport(0, 0, 1280, 720, 1);
	string text = "|";
	drawFilledRectangle(1152, 317, 1218, 343, COLOR(20, 20, 20));
	writeText(1165, 340, (char*)text.c_str(), WHITE, 1, COLOR(20, 20, 20));

	while (!finished) {
		if (GetAsyncKeyState(VK_RETURN)) {
			if (text == "|") {
				printf("Invalid\n");
				menuStratsButtons[3].drawButton();
			}
			else {
				printf("HEHEEEE\n");
				text = text.substr(0, text.length() - 1);
				extraAddedStrats.insert(stoi(text));
				menuStratsButtons[3].drawButton();
				DisplayStrats(false);
			}
			break;
		}
		bool ok = false;
		if (GetAsyncKeyState(0x30)) { // 0
			text = text.substr(0, text.length() - 1);
			text += '0'; ok = true;
			text += "|";
		}
		else if (GetAsyncKeyState(0x31)) { // 1
			text = text.substr(0, text.length() - 1);
			text += '1'; ok = true;
			text += "|";
		}
		else if (GetAsyncKeyState(0x32)) { // 2
			text = text.substr(0, text.length() - 1);
			text += '2'; ok = true;
			text += "|";
		}
		else if (GetAsyncKeyState(0x33)) { // 3
			text = text.substr(0, text.length() - 1);
			text += '3'; ok = true;
			text += "|";
		}
		else if (GetAsyncKeyState(0x34)) { // 4
			text = text.substr(0, text.length() - 1);
			text += '4'; ok = true;
			text += "|";
		}
		else if (GetAsyncKeyState(0x35)) { // 5
			text = text.substr(0, text.length() - 1);
			text += '5'; ok = true;
			text += "|";
		}
		else if (GetAsyncKeyState(0x36)) { // 6
			text = text.substr(0, text.length() - 1);
			text += '6'; ok = true;
			text += "|";
		}
		else if (GetAsyncKeyState(0x37)) { // 7
			text = text.substr(0, text.length() - 1);
			text += '7'; ok = true;
			text += "|";
		}
		else if (GetAsyncKeyState(0x38)) { // 8
			text = text.substr(0, text.length() - 1);
			text += '8'; ok = true;
			text += "|";
		}
		else if (GetAsyncKeyState(0x39)) { // 9
			text = text.substr(0, text.length() - 1);
			text += '9'; ok = true;
			text += "|";
		}
		else if (GetAsyncKeyState(VK_BACK) && text.length() >= 1) {
			text = text.substr(0, text.length() - 2); ok = true;
			text += "|";
		}
		if (ok) {
			drawFilledRectangle(1152, 317, 1218, 343, COLOR(20, 20, 20));
			writeText(1165, 340, (char*)text.c_str(), WHITE, 1, COLOR(20, 20, 20));
		}
		Sleep(100);
	}
	setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
	setbkcolor(BLACK);
}
void CleanUp() {
	strats.clear();
	menuStratsButtons.clear();
	editMode = false;
	if (S.corpuri_selectate.size() != 1)
		editButtonSelectable = false;
	renderSceneAgain = 1;
	setviewport(0, 0, 1280, 720, 1);
	drawFilledRectangle(1080, 30, 1280, 355, COLOR(20, 20, 20));
	int x1 = 1120, y1 = 60, x2 = 1230, y2 = 90;
	drawEmptyRectangle(x1, y1, x2, y2, WHITE);
	writeText(x1 + 25, y1 + 25, "Edit object", WHITE, 1, COLOR(20, 20, 20));
	if (!editButtonSelectable) {
		drawLine(x1, y1, x1 + 10, y2, WHITE);
		drawLine(x1 + 10, y1, x1 + 20, y2, WHITE);
		drawLine(x1 + 20, y1, x1 + 30, y2, WHITE);
		drawLine(x1 + 30, y1, x1 + 40, y2, WHITE);
		drawLine(x1 + 40, y1, x1 + 50, y2, WHITE);
		drawLine(x1 + 50, y1, x1 + 60, y2, WHITE);
		drawLine(x1 + 60, y1, x1 + 70, y2, WHITE);
		drawLine(x1 + 70, y1, x1 + 80, y2, WHITE);
		drawLine(x1 + 80, y1, x1 + 90, y2, WHITE);
		drawLine(x1 + 90, y1, x1 + 100, y2, WHITE);
		drawLine(x1 + 100, y1, x1 + 110, y2, WHITE);
	}
	setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
	setbkcolor(BLACK);
}
void DisplayMenus() {
	setviewport(0, 0, 1280, 720, 1);
	menuStratsButtons.clear();
	Button closeButton = *new Button("Close button", 1080, 315, 1150, 345);
	closeButton.drawButton = [closeButton] {
		drawEmptyRectangle(closeButton.x1, closeButton.y1, closeButton.x2, closeButton.y2, WHITE);
		writeText(closeButton.x1 + 17, closeButton.y1 + 23, "Close", WHITE, 1, COLOR(20, 20, 20));
	};
	closeButton.onClick = [] {
		printf("Closeeeee\n");
		CleanUp();
	};
	closeButton.drawButton();
	Button upBT = *new Button("UP", 1230, 305, 1260, 330);
	upBT.drawButton = [upBT] {
		drawLine((upBT.x1 + upBT.x2) / 2, upBT.y1 + 5, upBT.x1 + 5, upBT.y2 - 5, WHITE);
		drawLine((upBT.x1 + upBT.x2) / 2, upBT.y1 + 5, upBT.x2 - 5, upBT.y2 - 5, WHITE);
		drawLine(upBT.x1 + 5, upBT.y2 - 5, upBT.x2 - 5, upBT.y2 - 5, WHITE);
	};
	upBT.onClick = [] {
		stratsOffset -= 10;
		DisplayStrats();
	};
	upBT.drawButton();
	Button downBT = *new Button("DOWN", 1230, 330, 1260, 355);
	downBT.drawButton = [&downBT] {
		drawLine((downBT.x1 + downBT.x2) / 2, downBT.y2 - 5, downBT.x1 + 5, downBT.y1 + 5, WHITE);
		drawLine((downBT.x1 + downBT.x2) / 2, downBT.y2 - 5, downBT.x2 - 5, downBT.y1 + 5, WHITE);
		drawLine(downBT.x1 + 5, downBT.y1 + 5, downBT.x2 - 5, downBT.y1 + 5, WHITE);
	};
	downBT.onClick = [] {
		stratsOffset += 10;
		DisplayStrats();
	};
	downBT.drawButton();
	Button addButton = *new Button("Add", 1150, 315, 1220, 345);
	addButton.drawButton = [addButton] {
		drawEmptyRectangle(addButton.x1, addButton.y1, addButton.x2, addButton.y2, WHITE);
		writeText(addButton.x1 + 15, addButton.y1 + 25, "Add S", WHITE, 1, COLOR(20, 20, 20));
	};
	addButton.onClick = [] {
		AddNewStrat();
	};
	addButton.drawButton();
	menuStratsButtons.push_back(closeButton);
	menuStratsButtons.push_back(upBT);
	menuStratsButtons.push_back(downBT);
	menuStratsButtons.push_back(addButton);
	setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
	setbkcolor(BLACK);
}
void EditObject() {
	editMode = true;
	stratsOffset = 0;
	extraAddedStrats.clear();
	printf("Edit Object\n");
	selectedCorp = S.corpuri_selectate[0];
	selectedCorpName = S.corpuri[selectedCorp].name;
	printf("Selected corp: %i\n", selectedCorp);
	DisplayStrats();
	DisplayMenus();
}
