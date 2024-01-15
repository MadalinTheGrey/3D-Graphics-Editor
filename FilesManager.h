#pragma once
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
                vector<vector<int>> fcs;
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
                    else if (read == "Fata:") {
                        fin >> r1;
                        r1 = r1.substr(r1.size() - 2);
                        int n = stoi(r1), x;
                        vector<int> v;
                        for (int i = 0; i < n; ++i) {
                            fin >> r1;
                            x = stoi(r1);
                            v.push_back(x);
                        }
                        fcs.push_back(v);
                    }
                }
                Punct offset = { 0, 0 };
                Corp corp(puncte, linii, sect, offset, nume);
                corp.faces = fcs;
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
        for (auto& f : corp.faces) {
            fout << "Fata: ";
            fout << f.size() << "E ";
            for (auto& x : f) {
                fout << x << ' ';
            }
            fout << '\n';
        }
        fout << "EndCorp" << endl;
    }
    fout.close();
}
