#include "graphics.h"
#pragma once
using namespace std;

static class GlobalVariables{
public:
    unsigned int window_width = 1280;
    unsigned int window_height = 720;
    char window_name[10] = "Editor 3D";
    int window_bg_color = BLACK;
    int window_startPosX = 100;
    int window_startPosY = 50;
    int MAPPED_COLORS[1280][720] = {0};
    int MAPPED_BUTTONS[1280][720] =  {0};
    int dist_obs = 600;
}GB;
