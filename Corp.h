//
// Created by andre on 12/10/2023.
//

#ifndef INC_3D_EDITOR_CORP_H
#define INC_3D_EDITOR_CORP_H
#include "GlobalVariables.h"
#include "myGraphics.h"
#include <utility>
#include <vector>
#pragma once

class Punct3D{
public:
    int x, y, z;
};
class Punct2D{
public:
    int x, y;
};
class Linie {
public:
    int pointA, pointB;
};
//Corp ce contine puncte 3D si linii, corp ce va face parte dintr-o scena
class Corp {
public:
    std::string name;
    std::vector<Punct3D> puncte3D;
    std::vector<Linie> linii;
    Corp() {
        this->name = "Corp";
        this->puncte3D = std::vector<Punct3D>();
        this->linii = std::vector<Linie>();
    }
    Corp(std::vector<Punct3D> _puncte, std::vector<Linie> _linii, std::string _name = "Corp") {
        this->puncte3D = std::move(_puncte);
        this->linii = std::move(_linii);
        this->name = std::move(_name);
        ConvertFrom3Dto2D(0);
    }
    void AfisareCorp(int offset = 0, int zoom = 0) {
        ConvertFrom3Dto2D(zoom);
        offset-=zoom*2; //TODO fix zoom to be smother
        for(auto i : linii)
            drawLine(puncte2D[i.pointA].x-offset, puncte2D[i.pointA].y,
                     puncte2D[i.pointB].x-offset, puncte2D[i.pointB].y,
                     WHITE, 1, SOLID_LINE);
        for(auto i : puncte2D)
            drawFilledRectangle(i.x - 3 - offset, i.y - 3, i.x + 3 - offset, i.y + 3, WHITE, SOLID_FILL);
    }
private:
    std::vector<Punct2D> puncte2D = std::vector<Punct2D>();
    void ConvertFrom3Dto2D(int zoom) {
        puncte2D.clear();
        for(auto punct3d : puncte3D) {
            Punct2D punct2d = Punct2D();
            double p = (double)punct3d.x * dist_obs / (dist_obs + punct3d.z + zoom);
            double q = (double)punct3d.y * dist_obs / (dist_obs + punct3d.z + zoom);
            double dif = p - (int)p;
            if(dif >= 0.5)
                p++;
            dif = q - (int)q;
            if(dif >= 0.5)
                q++;
            punct2d.x = (int)p;
            punct2d.y = (int)q;
            puncte2D.push_back(punct2d);
        }
    }
};
//Scena ce va contine mai multe corpuri ce vor fi afisate pe ecran
class Scena {
public:
    std::string name;
    std::vector<Corp> corpuri;
    Scena() {
        name = "Scena";
        this->corpuri = std::vector<Corp>();
    }
    Scena(std::string _name, std::vector<Corp> _corpuri) {
        this->corpuri = std::move(_corpuri);
        this->name = std::move(_name);
    }
    void AfisareScena() {
        for (auto & corp : corpuri)
            corp.AfisareCorp();
    }
};

#endif //INC_3D_EDITOR_CORP_H

