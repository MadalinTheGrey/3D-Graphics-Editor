#include "graphics.h"

void InitializeWindow()
{
	initwindow(1280, 720);
}

void InitializeMenuPanels()
{
	setfillstyle(SOLID_FILL, COLOR(35, 35, 35));
	bar(0, 0, getmaxx(), 30);
	setfillstyle(SOLID_FILL, COLOR(20, 20, 20));
	bar(1080, 30, getmaxx(), getmaxy());
	bar(0, 100, 40, getmaxy() - 100);
}
