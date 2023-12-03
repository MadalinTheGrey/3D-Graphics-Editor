#include "myGraphics.h"
#include "GlobalVariables.h"
#include "Menu.h"
void MainPanels() {
    
}
void InitializeWindow()
{
	CreateStartWindow(GB.window_width, GB.window_height, GB.window_name, GB.window_bg_color, GB.window_startPosX, GB.window_startPosY);
	InitializeMenu();
}
