#pragma once
#include <string>
#include "myGraphics.h"
#include <iostream>
#include <vector>
#include <functional>
#include "Button.h"
using namespace std;
vector<Button> _menuButtons;
vector<Button> _filesButtons;
vector<string> files;
string _path = "";
bool _closeThisWindow = false;
bool _isSelectedAFile = false;
vector<string> get_all_files_names_within_folder(string folder);
int cellWidth = 50;
int _offset = 0;
void DrawFilesButtons();
void Offset(int x);
string receivePathToFile(int first = 0);