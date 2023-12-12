//
// Created by andrei
//

#ifndef INC_3D_EDITOR_FILESMANAGER_H
#define INC_3D_EDITOR_FILESMANAGER_H

#include <fstream>
#include <vector>
#include <string>
#include "Corp.h"
Scena readFromFile(const std::string& fileName = "D://Andrei//Desktop//My Projects//3D Editor//Saved//corp1.txt") {
    std::ifstream fin(fileName);
    std::string read1,read2, r1, r2, r3;
    if(!fin.is_open())
        printf("Error opening file!\n");
    Scena scena = Scena();
    while(fin >> read1) {
        if(read1 == "Name:") {
            fin >> r1;
            scena.name = r1;
        }else if(read1 == "Corp:") {
            fin >> r1;
            Corp corp = Corp();
            corp.name = r1;
            fin >> read2;
            while(read2 != "EndCorp") {
                if(read2 == "Punct:") {
                    fin >> r1 >> r2 >> r3;
                    Punct3D punct = Punct3D();
                    punct.x = std::stoi(r1);
                    punct.y = std::stoi(r2);
                    punct.z = std::stoi(r3);
                    corp.puncte3D.push_back(punct);
                }else if(read2 == "Linie:") {
                    fin >> r1 >> r2;
                    Linie linie = Linie();
                    linie.pointA = std::stoi(r1);
                    linie.pointB = std::stoi(r2);
                    corp.linii.push_back(linie);
                }
                fin >> read2;
            }
            scena.corpuri.push_back(corp);
        }
    }
    fin.close();
    return scena;
}

#endif //INC_3D_EDITOR_FILESMANAGER_H
