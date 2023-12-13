#include <iostream>
#include "myGraphics.h"
#include "Interface.h"
#include "Render3D.h"

using namespace std;

int main() {
    InitializeWindow();
    InitializeInterface();
    registermousehandler(WM_LBUTTONDOWN, checkIfButtonClicked);
    render3D();
    return 0;
}
//TODO transforma din vector STL in vector dinamic si muta in GB? Button 25
//TODO new file implementation Button 36
//TODO open file implementation Button 47
//TODO for string too myGraphics.h 37 OPTIONAL, maybe delete
//TODO write to file
//TODO offset Render3D.h 15