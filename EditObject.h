#pragma once
#include <vector>
#include "Corp.h"
#include "myGraphics.h"
using namespace std;
struct bttn {
	int x1, y1, x2, y2;
};
vector<bttn> bttns;
int ystart = 10, cellSize = 40;
void InitializeRightMenu() {
	ystart = 10;
	setviewport(0, 0, 1280, 720, 1);
	for(auto x:S.corpuri) {
		bttns.push_back({1080, ystart-cellSize, 1280, ystart+cellSize});
		ystart += cellSize;
		drawEmptyRectangle(1080, ystart-cellSize/2, getmaxx()-10, ystart + cellSize/2, COLOR(182,182,182));
		writeText(1080+20, ystart+15, (char*)x.name.c_str(), COLOR(182,182,182), COLOR(20, 20, 20));
	}
	setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
}