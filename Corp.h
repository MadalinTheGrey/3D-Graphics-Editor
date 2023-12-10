#include "GlobalVariables.h"
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
		P.x_real = A.x * GB.dist_obs / (GB.dist_obs + A.z);
		P.y_real = A.y * GB.dist_obs / (GB.dist_obs + A.z);
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
	Punct3D A, B;

	Linie()
	{

	}

	Linie(Punct3D P1, Punct3D P2)
	{
		A = P1;
		B = P2;
	}

	///Deseneaza linia
	void DrawLine()
	{
		Punct P1, P2;
		P1 = P1.Punct3Dto2D(A);
		P2 = P2.Punct3Dto2D(B);
		P1.ConvertCoord();
		P2.ConvertCoord();
		line(P1.x, P1.y, P2.x, P2.y);
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
	int nr_puncte, nr_linii; ///numarul de puncte si numarul de linii ale corpului
	int sectiune_curenta; ///sectiunea in care se deseneaza in momentul de fata
	int nr_sectiuni; ///numarul de sectiuni ale corpului, fiecare corp va avea minim o sectiune asa ca incepem de la 1
	Sectiune* sectiuni;
	Punct3D* puncte;
	Linie* linii;

	Corp()
	{
		nr_puncte = 0;
		nr_linii = 0;
		sectiune_curenta = 0;
		nr_sectiuni = 1;
		sectiuni = new Sectiune[nr_sectiuni];
		puncte = new Punct3D[nr_puncte];
		linii = new Linie[nr_linii];
	}

	Corp(int nr_p, int nr_l, int nr_sect, Punct3D pcte[], Linie lni[])
	{
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
	}

	void AfisareCorp()
	{
		for (int i = 0; i < nr_linii; i++)
			linii[i].DrawLine();
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

	///uneste sectiunile corpului prin linii intre punctele corespunzatoare
	void UnesteSectiuni()
	{

	}

	///salveaza corpul reprezentat intr-un fisier
	void SalveazaCorp()
	{

	}

	///incarca un corp dintr-un fisier
	void IncarcaCorp()
	{

	}

	///va roti corpul in sensul acelor de ceasornic pe axa X
	void RotesteXPoz()
	{

	}

	///va roti corpul in sens invers acelor de ceasornic pe axa X
	void RotesteXNeg()
	{

	}

	///va roti corpul in sensul acelor de ceasornic pe axa Y
	void RotesteYPoz()
	{

	}

	///va roti corpul in sens invers acelor de ceasornic pe axa Y
	void RotesteYNeg()
	{

	}

	///va roti corpul in sensul acelor de ceasornic pe axa Z
	void RotesteZPoz()
	{

	}

	///va roti corpul in sens invers acelor de ceasornic pe axa Z
	void RotesteZNeg()
	{

	}
};