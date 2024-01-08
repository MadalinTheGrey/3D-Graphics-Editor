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
        string read, r1, r2, r3, nume;
        while (fin >> read) {
            if (read == "Corp:") {
                fin >> read;
                nume = read;
                vector<Punct3D> puncte;
                vector<Linie> linii;
                vector<Sectiune> sect;
                while (read != "EndCorp") {
                    fin >> read;
                    if (read == "Punct:") {
                        fin >> r1 >> r2 >> r3;
                        int z = stoi(r3);
                        puncte.push_back(*new Punct3D(stoi(r1), stoi(r2), z));
                        bool exists = false;
                        for (auto& sct : sect)
                            if (sct.z == z) exists = true;
                        if (!exists) sect.push_back(Sectiune(z));
                    }
                    else if (read == "Linie:") {
                        fin >> r1 >> r2;
                        linii.push_back(*new Linie(stoi(r1), stoi(r2)));
                    }
                }
                Punct offset = { 0, 0 };
                Corp corp(puncte, linii, sect, offset, nume);
                scena.corpuri.push_back(corp);
            }
        }
        S = Scena(scena.corpuri);
    }
}

void SaveObjectInFile(string path) {
    TCHAR NPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, NPath);
    std::string ppath(NPath);
    path = ppath + "\\SavedObjects\\" + path;
    printf("Saving object in path %s\n", path.c_str());
    ofstream fout(path.c_str());
    for (auto& corp : S.corpuri) {
        fout << "Corp: " << corp.name << endl;
        for (auto& punct : corp.puncte) {
            fout << "Punct: " << punct.x << " " << punct.y << " " << punct.z << endl;
        }
        for (auto& linie : corp.linii) {
            fout << "Linie: " << linie.A << " " << linie.B << endl;
        }
        fout << "EndCorp" << endl;
    }
    fout.close();
}
#endif //INC_3D_EDITOR_V2_FILESMANAGER_H
