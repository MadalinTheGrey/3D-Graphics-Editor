#include "Initialization.h"
#include "Render3D.h"

using namespace std;

int main()
{
    InitializeWindow();
    InitializeInterface();
    registermousehandler(WM_LBUTTONDOWN, checkMouseClick);
    readFromFile(R"(D:\Pogramming\IP\Editor de grafica 3D\SavedObjects\Corp1.txt)");
    render3D();
}
