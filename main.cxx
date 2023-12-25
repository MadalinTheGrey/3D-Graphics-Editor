#include "myGraphics.h"
#include "Interface.h"
#include "Render3D.h"

using namespace std;
int main() {
    InitializeWindow();
    InitializeInterface();
    registermousehandler(WM_LBUTTONDOWN, checkMouseClick);
    readFromFile(R"(D:\Andrei\Desktop\My Projects\3D Editor V2\SavedObjects\Corp1.txt)");
    render3D();
    return 0;
}
