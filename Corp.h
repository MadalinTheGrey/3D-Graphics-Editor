#ifndef INC_3D_EDITOR_V2_CORP_H
#define INC_3D_EDITOR_V2_CORP_H
#include "GlobalVariables.h"
#include "myGraphics.h"
#include <math.h>
#include <iostream>

#pragma once

class Punct3D
{
public:
    double x, y, z;

    Punct3D()
    {
        x = y = z = 0;
    }

    Punct3D(int coord_x, int coord_y, int coord_z)
    {
        x = coord_x;
        y = coord_y;
        z = coord_z;
    }
};

class Punct
{
public:
    double x_real , y_real;
    int x, y;

    Punct()
    {
        x = y = x_real = y_real = 0;
    }

    Punct(int coord_x, int coord_y)
    {
        x_real = x = coord_x;
        y_real = y = coord_y;
    }

    /// returneaza proiectia unui punct 3D pe planul ecranului
    Punct Punct3Dto2D(Punct3D A)
    {
        Punct P;
        P.x_real = A.x * dist_obs / (dist_obs + A.z);
        P.y_real = A.y * dist_obs / (dist_obs + A.z);
        return P;
    }

    ///converteste coordonatele reale in coordonate pe ecran
    void ConvertCoord()
    {
        double p = x_real, dif;
        dif = p - (int)p;
        if (dif >= 0.5)
            p++;
        x = p;
        p = y_real;
        dif = p - (int)p;
        if (dif >= 0.5)
            p++;
        y = p;
    }
};

class Linie
{
public:
    int A, B; //indexurile punctelor in vectorul puncte

    Linie()
    {
        A = 0;
        B = 0;
    }

    Linie(int P1, int P2)
    {
        A = P1;
        B = P2;
    }
};

class Sectiune
{
public:
    Linie* A; ///vector dinamic care memoreaza liniile
    int nr_linii; ///numarul de linii care au fost reprezentate
    int z; ///pozitia pe axa z a sectiunii

    Sectiune()
    {
        A = new Linie;
        nr_linii = 0;
        z = 0;
    }

    Sectiune(int poz_z)
    {
        A = new Linie;
        nr_linii = 0;
        z = poz_z;
    }

    Sectiune(int poz_z, int nr_laturi)
    {
        A = new Linie[nr_laturi];
        nr_linii = nr_laturi;
        z = poz_z;
    }

    void AddLaturi()
    {

    }
};

class Corp
{
public:
    int nr_puncte, nr_linii; // numarul de puncte si numarul de linii ale corpului
    int sectiune_curenta; // sectiunea in care se deseneaza in momentul de fata
    int nr_sectiuni; // numarul de sectiuni ale corpului, fiecare corp va avea minim o sectiune asa ca incepem de la 1
    Punct3D centru; // centrul corpului
    double tx, ty, tz, lx, ly, lz; // t = top, l = lower - determina coordonatele maxime si minime pentru a incadra corpul
    // intr-un cub caruia ii vom determina centrul
    Sectiune* sectiuni;
    Punct3D* puncte;
    Linie* linii;

    Corp()
    {
        tx = ty = tz = 1280;
        lx = ly = lz = 0;
        centru = { 0, 0, 0 };
        nr_puncte = 1;
        nr_linii = 1;
        sectiune_curenta = 0;
        nr_sectiuni = 1;
        sectiuni = new Sectiune[nr_sectiuni];
        puncte = new Punct3D[nr_puncte];
        linii = new Linie[nr_linii];
    }

    Corp(int nr_p, int nr_l, int nr_sect, Punct3D pcte[], Linie lni[])
    {
        tx = ty = tz = 1280;
        lx = ly = lz = 0;
        centru = { 0, 0, 0 };
        nr_puncte = nr_p;
        nr_linii = nr_l;
        sectiune_curenta = 0;
        nr_sectiuni = nr_sect;
        sectiuni = new Sectiune[nr_sectiuni];
        puncte = new Punct3D[nr_puncte];
        linii = new Linie[nr_linii];
        for (int i = 0; i < nr_puncte; i++)
            puncte[i] = pcte[i];
        for (int i = 0; i < nr_linii; i++)
            linii[i] = lni[i];
        DeterminaCentru();
    }

    void AfisareCorp()
    {
        //for(int i=0; i<nr_puncte; ++i)
            //std::cout << puncte[i].x << " " << puncte[i].y << " " << puncte[i].z << "\n";
        for (int i = 0; i < nr_linii; i++)
        {
            Punct P1, P2, TL;
            Punct3D tl(tx, ty, lz);
            TL = TL.Punct3Dto2D(tl);
            TL.ConvertCoord();
            P1 = P1.Punct3Dto2D(puncte[linii[i].A]);
            P2 = P2.Punct3Dto2D(puncte[linii[i].B]);
            P1.ConvertCoord();
            P2.ConvertCoord();
            P1.x = zoom * (P1.x - TL.x) + TL.x;
            P1.y = zoom * (P1.y - TL.y) + TL.y;
            P2.x = zoom * (P2.x - TL.x) + TL.x;
            P2.y = zoom * (P2.y - TL.y) + TL.y;
            drawLine(P1.x, P1.y, P2.x, P2.y);
        }
    }

    void DeterminaCentru()
    {
        int i;
        for (i = 0; i < nr_puncte; i++)
        {
            if (puncte[i].x < tx) tx = puncte[i].x;
            if (puncte[i].x > lx) lx = puncte[i].x;
            if (puncte[i].y < ty) ty = puncte[i].y;
            if (puncte[i].y > ly) ly = puncte[i].y;
            if (puncte[i].z < tz) tz = puncte[i].z;
            if (puncte[i].z > lz) lz = puncte[i].z;
        }
        centru.x = (tx + lx) / 2;
        centru.y = (ty + ly) / 2;
        centru.z = (tz + lz) / 2;
    }

    ///dubleaza marimea vectorului ce pastreaza sectiunile
    void GrowSectiuni()
    {

    }

    ///deseneaza o linie pe ecran pentru user
    void UserDrawLine()
    {

    }

    ///deseneaza un dreptunghi pe ecran pentru user
    void UserDrawRectangle()
    {

    }

    ///deseneaza un cerc pe ecran pentru user
    void UserDrawCircle()
    {

    }

    ///va roti corpul in sensul acelor de ceasornic pe axa X
    void RotesteXPoz()
    {
        int i;
        double cz, cy;
        for (i = 0; i < nr_puncte; i++)
        {
            cy = puncte[i].y - centru.y;
            cz = puncte[i].z - centru.z;
            puncte[i].y = cos(default_angle) * cy - sin(default_angle) * cz + centru.y;
            puncte[i].z = sin(default_angle) * cy + cos(default_angle) * cz + centru.z;
        }
    }

    ///va roti corpul in sens invers acelor de ceasornic pe axa X
    void RotesteXNeg()
    {
        int i;
        double cz, cy;
        for (i = 0; i < nr_puncte; i++)
        {
            cy = puncte[i].y - centru.y;
            cz = puncte[i].z - centru.z;
            puncte[i].y = cos(-default_angle) * cy - sin(-default_angle) * cz + centru.y;
            puncte[i].z = sin(-default_angle) * cy + cos(-default_angle) * cz + centru.z;
        }
    }

    ///va roti corpul in sensul acelor de ceasornic pe axa Y
    void RotesteYPoz()
    {
        int i;
        double cz, cx;
        for (i = 0; i < nr_puncte; i++)
        {
            cx = puncte[i].x - centru.x;
            cz = puncte[i].z - centru.z;
            puncte[i].x = cos(default_angle) * cx - sin(default_angle) * cz + centru.x;
            puncte[i].z = sin(default_angle) * cx + cos(default_angle) * cz + centru.z;
        }
    }

    ///va roti corpul in sens invers acelor de ceasornic pe axa Y
    void RotesteYNeg()
    {
        int i;
        double cz, cx;
        for (i = 0; i < nr_puncte; i++)
        {
            cx = puncte[i].x - centru.x;
            cz = puncte[i].z - centru.z;
            puncte[i].x = cos(-default_angle) * cx - sin(-default_angle) * cz + centru.x;
            puncte[i].z = sin(-default_angle) * cx + cos(-default_angle) * cz + centru.z;
        }
    }

    ///va roti corpul in sensul acelor de ceasornic pe axa Z
    void RotesteZPoz()
    {
        int i;
        double cy, cx;
        for (i = 0; i < nr_puncte; i++)
        {
            cx = puncte[i].x - centru.x;
            cy = puncte[i].y - centru.y;
            puncte[i].x = cos(default_angle) * cx - sin(default_angle) * cy + centru.x;
            puncte[i].y = sin(default_angle) * cx + cos(default_angle) * cy + centru.y;
        }
    }

    ///va roti corpul in sens invers acelor de ceasornic pe axa Z
    void RotesteZNeg()
    {
        int i;
        double cy, cx;
        for (i = 0; i < nr_puncte; i++)
        {
            cx = puncte[i].x - centru.x;
            cy = puncte[i].y - centru.y;
            puncte[i].x = cos(-default_angle) * cx - sin(-default_angle) * cy + centru.x;
            puncte[i].y = sin(-default_angle) * cx + cos(-default_angle) * cy + centru.y;
        }
    }
};
#endif //INC_3D_EDITOR_V2_CORP_H
