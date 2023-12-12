#include <cstdio>
#include "myGraphics.h"
#include "Interface.h"
#include "Corp.h"
#include "FilesManager.h"
#include "Render3D.h"
#include <iostream>
using namespace std;

int main() {
    printf("Starting program...\n");
    InitializeWindow();
    InitializeInterface();
    registermousehandler(WM_LBUTTONDOWN, checkIfButtonClicked);
    render3D();
    getch();
}
//TODO Lines
//TODO Modify interface
//TODO WriteToFile
//TODO Border Control