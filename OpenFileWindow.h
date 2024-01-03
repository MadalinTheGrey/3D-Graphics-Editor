#ifndef INC_3D_EDITOR_V2_OPENFILEWINDOW_H
#define INC_3D_EDITOR_V2_OPENFILEWINDOW_H
#include <string>
#include "graphics.h"
#include <iostream>
#include <vector>
#include <functional>
#include "Render3D.h"
using namespace std;
struct btn {
    int x1, y1, x2, y2;
};
vector<btn> btt;
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
string receivePathToFile(int first = 0) {
    btt.clear();
    if (first == 1) {
        TCHAR NPath[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, NPath);
        std::string path(NPath);
        path += "\\SavedObjects";
        vector<string> files = get_all_files_names_within_folder(path);
        current_file = files[0];
        return path + "\\" + files[0];
    }
    currentWindow = 0;
    initwindow(400, 400, "Open file", 500, 250);
    setviewport(0, 0, 400, 400, 1);
    TCHAR NPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, NPath);
    std::string path(NPath);
    path+="\\SavedObjects";
    vector<string> files = get_all_files_names_within_folder(path);
    for (int i = 0; i < files.size(); ++i) {
        char* cstr(const_cast<char*>(files[i].c_str()));
        drawEmptyRectangle(0, i * cellWidth, getmaxx(), (i + 1) * cellWidth);
        outtextxy(10, i * cellWidth + 10, cstr);
        btt.push_back({ 0, i * cellWidth, getmaxx(), (i + 1) * cellWidth });
    }
    while (GetAsyncKeyState(VK_ESCAPE) == 0) {
        if (GetAsyncKeyState(VK_LBUTTON)) {
            for (int i = 0; i < btt.size(); ++i) {
                if (mousex() > btt[i].x1 && mousex() < btt[i].x2 && mousey() > btt[i].y1 && mousey() < btt[i].y2) {
                    printf("Selected file: %s", files[i].c_str());
                    current_file = files[i];
                    renderAgain = 1; currentWindow = 1;
                    closegraph(CURRENT_WINDOW);
                    path = path + "/" + files[i];
                    return path;
                }
            }
        }
    }
    //closegraph(CURRENT_WINDOW);
    return  "null";
}

#endif //INC_3D_EDITOR_V2_OPENFILEWINDOW_H
