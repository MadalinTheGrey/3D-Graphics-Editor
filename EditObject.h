#pragma once
#include <stdio.h>
#include "Button.h"
#include "ButtonManager.h"
#include <set>
vector<Button> strats;
vector<Button> menuStratsButtons;
set<int> extraAddedStrats;

int stratsOffset = 0;
void SelectStrat(int s);

void DisplayStrats(bool resetSts = true);

void AddNewStrat();

void CleanUp();

void DisplayMenus();

void EditObject();
