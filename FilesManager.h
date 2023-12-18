#ifndef INC_3D_EDITOR_V2_FILESMANAGER_H
#define INC_3D_EDITOR_V2_FILESMANAGER_H

#include "graphics.h"
#include <fstream>
#include "Corp.h"
using namespace std;
Corp readFromFile(char path[]) {
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
    Corp C(8, 12, 2, pcte, lnii, "georgel");
    return C;
    /**ifstream fin(path);
    string read, r1, r2, r3;
    Corp corp = Corp();
    Linie linii[100]; int indexLinii = 0;
    Punct3D puncte[100]; int indexPuncte = 0;
    if(!fin.is_open()) {
        printf("Error opening file!\n");
        return corp;
    }
    while(fin >> read) {
        if(read == "Punct:") {
            fin >> r1 >> r2 >> r3;
            puncte[indexPuncte++] = {stoi(r1), stoi(r2), stoi(r3)};
        } else if(read == "Linie:") {
            fin >> r1 >> r2;
            linii[indexLinii++] = {stoi(r1), stoi(r2)};
        }
    }
    corp.puncte = puncte;
    corp.linii = linii;
    corp.nr_puncte = indexPuncte;
    corp.nr_linii = indexLinii;
    return corp;**/
}

#endif //INC_3D_EDITOR_V2_FILESMANAGER_H
