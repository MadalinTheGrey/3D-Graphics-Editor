#include <iostream>
#include <stdio.h>
#include "graphics.h"
#include "Initialization.h"
#include "Corp.h"
#include "Render3D.h"
#include "GlobalVariables.h"

using namespace std;

int main()
{
    InitializeWindow();
    InitializeInterface();
    registermousehandler(WM_LBUTTONDOWN, checkIfButtonClicked);
    LoadFromFile();
}
