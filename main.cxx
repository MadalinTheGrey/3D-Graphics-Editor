#include <iostream>
#include <stdio.h>
#include "graphics.h"
#include "Initialization.h"
#include "Corp.h"

using namespace std;

int main()
{
    InitializeWindow();
    /*Punct3D pcte[] = {
        Punct3D(200, 200, 200),
        Punct3D(200, 400, 200),
        Punct3D(400, 400, 200),
        Punct3D(400, 200, 200),
        Punct3D(200, 200, 400),
        Punct3D(200, 400, 400),
        Punct3D(400, 400, 400),
        Punct3D(400, 200, 400)
    };
    Linie lnii[] = {
        Linie(pcte[0], pcte[1]),
        Linie(pcte[1], pcte[2]),
        Linie(pcte[2], pcte[3]),
        Linie(pcte[3], pcte[0]),
        Linie(pcte[4], pcte[5]),
        Linie(pcte[5], pcte[6]),
        Linie(pcte[6], pcte[7]),
        Linie(pcte[7], pcte[4]),
        Linie(pcte[4], pcte[0]),
        Linie(pcte[5], pcte[1]),
        Linie(pcte[6], pcte[2]),
        Linie(pcte[7], pcte[3])
    };
    Corp C(8, 12, 2, pcte, lnii);
    C.AfisareCorp();*/
    getch();
    closegraph();
}