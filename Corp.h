#pragma once
#include "GlobalVariables.h"
#include <math.h>
#include <vector>
#include <string>
#include <set>

class Punct3D
{
public:
	double x, y, z;

	//------------------------------------------------Constructori-------------------------------------------

	Punct3D();

	Punct3D(int coord_x, int coord_y, int coord_z);

	//--------------------------------------------------Operatori---------------------------------------------

	bool operator==(Punct3D P);

	bool operator!=(Punct3D P);
};

class Punct
{
public:
	double x, y;

	//---------------------------------------Constructori-----------------------------------------

	Punct();

	Punct(double coord_x, double coord_y);

	//-----------------------------------------Operatori-------------------------------------------

	bool operator==(Punct P);

	bool operator!=(Punct P);

	//-------------------------------------------Metode-------------------------------------------

	/// returneaza proiectia unui punct 3D pe planul ecranului
	static Punct Punct3Dto2D(Punct3D A);

	//converteste un punct 2D in 3D cunoscand pozitia sa in z
	static Punct3D Punct2Dto3D(Punct A, int z_pos);

	///converteste coordonatele reale in coordonate pe ecran
	void ConvertCoord();
};

class Linie
{
public:
	int A, B; //indexurile punctelor in vectorul puncte

	//-----------------------------------------------Constructori------------------------------------------

	Linie();

	Linie(int P1, int P2);

	//------------------------------------------------Operatori-------------------------------------------

	bool operator==(const Linie& L);

	bool operator!=(const Linie& L);
};

class Sectiune
{
public:
	int z; ///pozitia pe axa z a sectiunii
	//---------------------------------Constructori-------------------------------------------

	Sectiune();

	Sectiune(int poz_z);

	//--------------------------------Operatori--------------------------------------------

	bool operator==(Sectiune sect);

	bool operator!=(Sectiune sect);
};

class Corp
{
public:
	//---------------------------------Variabile-------------------------------------------------
	std::string name;
	Punct3D centru, pminim, pmaxim; // centrul corpului si punctele cu coordonate minime si maxime folosite pentru a incadra corpul
	// intr-un cub caruia ii vom determina centrul 
	Punct tl_corner, lr_corner; // colturile stanga sus si dreapta jos ale corpului
	Punct offset_local; //modificarea pozitiei pe x si y a corpului in 2D
	std::vector<Sectiune> sectiuni;
	std::vector<Sectiune> sectiuni_origin; //va memora sectiunile originale ale corpului
	std::vector<Punct3D> puncte;
	std::vector<Punct3D> puncte_origin; //va memora pozitia punctelor inainte de rotatie sau alte miscari
	std::vector<Linie> linii;
	std::vector<Linie> linii_origin; //va memora liniile originale ale corpului
	std::vector<std::vector<int>> faces;

	//--------------------------------Constructori------------------------------------------

	Corp();

	Corp(std::vector<Punct3D> pncte, std::vector<Linie> lnii, std::vector<Sectiune> sect, Punct offset, std::string nume);

	//---------------------------------------Operatori------------------------------------------
	bool operator==(Corp A);

	bool operator!=(Corp A);

	//-----------------------------------------------Metode------------------------------------------------

	///Afiseaza corpul pe ecran
	void AfisareCorp();
	void AfisareCorpFete(double tzoom, int offsetX, int offsetY);
	void AdaugareFata(std::vector<int> v);
	///Determina centrul si colturile corpului
	void DeterminaCentru_Colturi();

	//Adauga un punct in vectorul de puncte
	void AdaugarePunct(Punct3D P);

	//Elimina ultimul punct adaugat in vectorul de puncte
	void EliminaPunct();

	void AdaugareLinie(Linie L);

	///va roti corpul in sensul acelor de ceasornic pe axa X
	void RotesteXPoz();

	///va roti corpul in sens invers acelor de ceasornic pe axa X
	void RotesteXNeg();

	///va roti corpul in sensul acelor de ceasornic pe axa Y
	void RotesteYPoz();

	///va roti corpul in sens invers acelor de ceasornic pe axa Y
	void RotesteYNeg();

	///va roti corpul in sensul acelor de ceasornic pe axa Z
	void RotesteZPoz();

	///va roti corpul in sens invers acelor de ceasornic pe axa Z
	void RotesteZNeg();
};

class Scena
{
public:
	std::vector<Corp> corpuri;
	std::vector<Corp> corpuri_origin; //corpuri care erau original in scena
	std::vector<int> corpuri_selectate;

	//------------------------------------Constructori--------------------------------

	Scena()
	{

	}

	Scena(std::vector<Corp> corp);

	//-------------------------------------Metode---------------------------------------

	void ApplyChanges();

	void AdaugareCorp();

	void EliminaCorp(int ind_corp);

	void ResetObject(int ind_corp);

	void ResetScene();

	void ChangeSelected(int mouse_x, int mouse_y);

	///deseneaza o linie pe ecran pentru user
	void UserDrawLine(int mouse_x, int mouse_y, int draw_step, int z_pos, int ind_corp);

	///deseneaza un dreptunghi pe ecran pentru user
	void UserDrawRectangle(int mouse_x, int mouse_y, int draw_step, int z_pos, int ind_corp);

	///deseneaza un cerc pe ecran pentru user
	void UserDrawCircle(int mouse_x, int mouse_y, int draw_step, int z_pos, int ind_corp);

	void UserAddPoint(int mouse_x, int mouse_y, int z_pos, int ind_corp);

	void UserLinkPoints(int mouse_x, int mouse_y, int draw_step, int ind_corp);

	void IncarcaScena();
} S;
