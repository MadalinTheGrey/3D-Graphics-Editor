#include "myGraphics.h"
#include "Interface.h"
#include "Render3D.h"
#include "EditObject.h"
using namespace std;
int main() {
    InitializeWindow();
    InitializeInterface();
    registermousehandler(WM_LBUTTONDOWN, checkMouseClick);
    //readFromFile(R"(D:\Andrei\Downloads\BGI2010\bgi\SavedObjects\Corp1.txt)");
    string path = receivePathToFile(1);
    printf("%s", path.c_str());
    readFromFile(path);
    InitializeRightMenu();
    render3D();
    return 0;
}
