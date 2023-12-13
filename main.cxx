#include <iostream>
#include <stdio.h>
#include "graphics.h"
#include "Initialization.h"
#include "Corp.h"
#include "GlobalVariables.h"

using namespace std;

int main()
{
    InitializeWindow();
    Punct3D pcte[] = {
        Punct3D(100, 100, 100),
        Punct3D(100, 200, 100),
        Punct3D(200, 200, 100),
        Punct3D(200, 100, 100),
        Punct3D(100, 100, 200),
        Punct3D(100, 200, 200),
        Punct3D(200, 200, 200),
        Punct3D(200, 100, 200)
    };
    Linie lnii[] = {
        Linie(0, 1),
        Linie(1, 2),
        Linie(2, 3),
        Linie(3, 0),
        Linie(4, 5),
        Linie(5, 6),
        Linie(6, 7),
        Linie(7, 4),
        Linie(4, 0),
        Linie(5, 1),
        Linie(6, 2),
        Linie(7, 3)
    };
    Corp C(8, 12, 2, pcte, lnii);
    setviewport(GB.vp_tl_x, GB.vp_tl_y, GB.vp_dr_x, GB.vp_dr_y, 0);
    C.AfisareCorp();

    //Rotire
    char tasta;
    do
    {
        tasta = getch();
        if (tasta == 'e') C.RotesteXPoz();
        else if (tasta == 'w') C.RotesteXNeg();
        else if (tasta == 'd') C.RotesteYPoz();
        else if (tasta == 's') C.RotesteYNeg();
        else if (tasta == 'x') C.RotesteZNeg();
        else if (tasta == 'c') C.RotesteZPoz();
        else if (tasta == 'p') GB.zoom += 0.2;
        else if (tasta == 'm') GB.zoom -= 0.2;
        clearviewport();
        C.AfisareCorp();
    } while (tasta != 'q');
    closegraph();
}
