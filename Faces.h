#pragma once
#include "graphics.h"
#include "myGraphics.h"
#include "Button.h"
#include "Screenshot.h"
#include <vector>
#include "Corp.h"

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

void Reload();
void CreateFace();
void SelectPoint(int index);
void Edit();
void Top();
void Buttons();
void ShowFaces();