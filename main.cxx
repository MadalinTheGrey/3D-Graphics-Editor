#include "Initialization.h"
#include "Render3D.h"

using namespace std;

int main()
{
    InitializeWindow();
    InitializeInterface();
    string path = receivePathToFile(1);
    printf("Opened: %s\n", path.c_str());
    readFromFile(path);
    render3D();
    return 0;
}