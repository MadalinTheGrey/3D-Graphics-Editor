#ifndef INC_3D_EDITOR_V2_FILESMANAGER_H
#define INC_3D_EDITOR_V2_FILESMANAGER_H

#include "graphics.h"
#include <fstream>
#include "Corp.h"
#include "GlobalVariables.h"
using namespace std;
void readFromFile(string path) {
    ifstream fin(path.c_str());
    Scena scena;
    if (!fin.is_open()) {
        printf("Error opening file!\n");
        return;
    }
    else {
        vector<Corp> corpuri;
        string read, r1, r2, r3;
        while (fin >> read) {
            if (read == "Corp:") {
                Corp corp;
                fin >> read;
                corp.name = read;
                vector<Punct3D> puncte;
                vector<Linie> linii;
                while (read != "EndCorp") {
                    fin >> read;
                    if (read == "Punct:") {
                        fin >> r1 >> r2 >> r3;
                        puncte.push_back(*new Punct3D(stoi(r1), stoi(r2), stoi(r3)));
                    }
                    else if (read == "Linie:") {
                        fin >> r1 >> r2;
                        linii.push_back(*new Linie(stoi(r1), stoi(r2)));
                    }
                }
                corp.puncte = puncte;
                corp.linii = linii;
                scena.corpuri.push_back(corp);
            }
        }
        S = Scena(scena);
    }
}

#endif //INC_3D_EDITOR_V2_FILESMANAGER_H
