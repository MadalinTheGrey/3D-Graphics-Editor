#ifndef INC_3D_EDITOR_V2_OPENFILEWINDOW_H
#define INC_3D_EDITOR_V2_OPENFILEWINDOW_H
#include <string>
#include "graphics.h"
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
vector<string> get_all_files_names_within_folder(string folder)
{
    vector<string> names;
    string search_path = folder + "/*.*";
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                names.push_back(fd.cFileName);
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
}
int cellWidth = 50;
int _offset = 0;
void DrawFilesButtons() {
    _filesButtons.clear();
    clearviewport();
    for (int i = 0; i < files.size(); ++i) {
        char* cstr(const_cast<char*>(files[i].c_str()));
        Button temp = *new Button(string(cstr), 0, i * cellWidth, getmaxx() - 10, (i + 1) * cellWidth);
        temp.drawButton = [&temp, cstr] {
            drawEmptyRectangle(temp.x1 + 5, temp.y1 + 5 + _offset, temp.x2 - 5, temp.y2 - 5 + _offset, COLOR(100, 100, 100));
            writeText(temp.x1 + 30, temp.y1 + 35 + _offset, cstr, WHITE, 1, BLACK);
            };
        temp.onClick = [temp] {
            printf("Selected file: %s\n", temp.name.c_str());
            current_file = temp.name;
            closegraph(CURRENT_WINDOW);
            _path = _path + "/" + temp.name;
            _isSelectedAFile = true;
            _closeThisWindow = true;
            };
        temp.drawButton();
        _filesButtons.push_back(temp);
    }
}
void Offset(int x) {
    _offset += x;
    DrawFilesButtons();
}
string receivePathToFile(int first = 0) {
    _closeThisWindow = false;
    _isSelectedAFile = false;
    _menuButtons.clear();
    _filesButtons.clear();
    _path = "";
    files.clear();
    if (first == 1) {
        TCHAR NPath[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, NPath);
        std::string path(NPath);
        path += "\\SavedObjects";
        vector<string> files = get_all_files_names_within_folder(path);
        current_file = files[0];
        return path + "\\" + files[0];
    }
    initwindow(410, 410, "Open file", 500, 250);
    Button cancelF = *new Button("Cancel", 0, 350, 150, 400);
    cancelF.drawButton = [&cancelF] {
        drawEmptyRectangle(cancelF.x1 + 10, cancelF.y1 + 10, cancelF.x2 - 10, cancelF.y2 - 10, WHITE);
        writeText(cancelF.x1 + 50, cancelF.y1 + 35, "Cancel", WHITE);
    };
    cancelF.onClick = [] {
        printf("Cancel\n");
        closegraph(CURRENT_WINDOW);
        _closeThisWindow = true;
        };
    cancelF.drawButton();
    Button upButton = *new Button("UP", 350, 350, 400, 375);
    upButton.drawButton = [&upButton] {
        drawLine((upButton.x1 + upButton.x2) / 2, upButton.y1 + 5, upButton.x1 + 5, upButton.y2 - 5, WHITE);
        drawLine((upButton.x1 + upButton.x2) / 2, upButton.y1 + 5, upButton.x2 - 5, upButton.y2 - 5, WHITE);
        drawLine(upButton.x1 + 5, upButton.y2 - 5, upButton.x2 - 5, upButton.y2 - 5, WHITE);
    };
    upButton.onClick = [] {
        Offset(10);
        };
    upButton.drawButton();
    cancelF.drawButton();
    Button downButton = *new Button("DOWN", 350, 375, 400, 400);
    downButton.drawButton = [&downButton] {
        drawLine((downButton.x1 + downButton.x2) / 2, downButton.y2 - 5, downButton.x1 + 5, downButton.y1 + 5, WHITE);
        drawLine((downButton.x1 + downButton.x2) / 2, downButton.y2 - 5, downButton.x2 - 5, downButton.y1 + 5, WHITE);
        drawLine(downButton.x1 + 5, downButton.y1 + 5, downButton.x2 - 5, downButton.y1 + 5, WHITE);
        };
    downButton.onClick = [] {
        Offset(-10);
        };
    downButton.drawButton();

    _menuButtons.push_back(cancelF);
    _menuButtons.push_back(upButton);
    _menuButtons.push_back(downButton);
    
    setviewport(0, 0, 410, 350, 1);
    
    TCHAR NPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, NPath);
    _path  = string(NPath);
    _path += "\\SavedObjects";
    files = get_all_files_names_within_folder(_path);
    DrawFilesButtons();
    while (!_closeThisWindow) {
        if (GetAsyncKeyState(VK_LBUTTON)) {
            bool is_menu = false;
            for (auto& btnM : _menuButtons) {
                if (!_closeThisWindow) {
                    int x = mousex(); int y = mousey();
                    if (x > btnM.x1 && x < btnM.x2 && y > btnM.y1 && y < btnM.y2 && !_closeThisWindow) {
                        is_menu = true;
                        btnM.onClick();
                    }
                }
            }
            if (is_menu == false) {
                for (auto& btnF : _filesButtons) {
                    if (!_closeThisWindow) {
                        int x = mousex();
                        int y = mousey() - _offset;
                        if (x > btnF.x1 && x < btnF.x2 && y > btnF.y1 && y < btnF.y2 && !_closeThisWindow) {
                            btnF.onClick();
                        }
                    }
                }
            }
        }
        Sleep(50);
        if (_closeThisWindow && _isSelectedAFile) {
            return _path;
        }
    }
    return  "null";
}

#endif //INC_3D_EDITOR_V2_OPENFILEWINDOW_H