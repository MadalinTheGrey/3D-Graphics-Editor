#ifndef CORP_H
#define CORP_H

#include "GlobalVariables.h"
#include <math.h>
#include <vector>
#include <string>

class Punct3D
{
public:
	double x, y, z;

	//------------------------------------------------Constructori-------------------------------------------

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

	//--------------------------------------------------Operatori---------------------------------------------

	bool operator==(Punct3D P)
	{
		if (P.x == x && P.y == y && P.z == z)
			return true;
		return false;
	}

	bool operator!=(Punct3D P)
	{
		if (P.x != x || P.y != y || P.z != z)
			return true;
		return false;
	}
};

class Punct
{
public:
	double x , y;

	//---------------------------------------Constructori-----------------------------------------

	Punct()
	{
		x = y = 0;
	}

	Punct(double coord_x, double coord_y)
	{
		x = coord_x;
		y = coord_y;
	}

	//-----------------------------------------Operatori-------------------------------------------

	bool operator==(Punct P)
	{
		if (P.x == x && P.y == y)
			return true;
		return false;
	}

	bool operator!=(Punct P)
	{
		if (P.x != x || P.y != y)
			return true;
		return false;
	}

	//-------------------------------------------Metode-------------------------------------------

	/// returneaza proiectia unui punct 3D pe planul ecranului
	static Punct Punct3Dto2D(Punct3D A)
	{
		Punct P;
		P.x = A.x * dist_obs / (dist_obs + A.z);
		P.y = A.y * dist_obs / (dist_obs + A.z);
		return P;
	}

	//converteste un punct 2D in 3D cunoscand pozitia sa in z
	static Punct3D Punct2Dto3D(Punct A, int z_pos)
	{
		Punct3D P;
		P.x = A.x * (dist_obs + z_pos) / dist_obs;
		P.y = A.y * (dist_obs + z_pos) / dist_obs;
		P.z = z_pos;
		return P;
	}
	
	///converteste coordonatele reale in coordonate pe ecran
	void ConvertCoord()
	{
		double p = x, dif;
		dif = p - (int)p;
		if (dif >= 0.5)
			p = (int)p + 1;
		x = p;
		p = y;
		dif = p - (int)p;
		if (dif >= 0.5)
			p = (int)p + 1;
		y = p;
	}
};

class Linie
{
public:
	int A, B; //indexurile punctelor in std::vectorul puncte

	//-----------------------------------------------Constructori------------------------------------------

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

	//------------------------------------------------Operatori-------------------------------------------

	bool operator==(const Linie& L)
	{
		if (L.A == A && L.B == B)
			return true;
		return false;
	}

	bool operator!=(const Linie& L)
	{
		if (L.A != A || L.B != B)
			return true;
		return false;
	}
};

class Sectiune
{
public:
	std::vector<Linie> linii_sect;
	int z; ///pozitia pe axa z a sectiunii

	//---------------------------------Constructori-------------------------------------------

	Sectiune()
	{
		z = 0;
	}

	Sectiune(int poz_z)
	{
		z = poz_z;
	}

	Sectiune(int poz_z, std::vector<Linie> B)
	{
		linii_sect = move(B);
		z = poz_z;
	}

	//--------------------------------Operatori--------------------------------------------

	bool operator==(Sectiune sect)
	{
		if (sect.z == z && linii_sect.size() == sect.linii_sect.size())
		{
			for (int i = 0; i < linii_sect.size(); i++)
				if (linii_sect[i] != sect.linii_sect[i])
					return false;
			return true;
		}
		return false;
	}

	bool operator!=(Sectiune sect)
	{
		if (sect.z == z && linii_sect.size() == sect.linii_sect.size())
		{
			for (int i = 0; i < linii_sect.size(); i++)
				if (linii_sect[i] != sect.linii_sect[i])
					return true;
			return false;
		}
		return true;
	}

	//-----------------------------------Metode-----------------------------------

	void AddLinie(Linie L)
	{
		linii_sect.push_back(L);
	}
};

class Corp
{
public:
	//---------------------------------Variabile-------------------------------------------------
	std::string name;
	Punct3D centru; // centrul corpului
	Punct tl_corner, lr_corner; // colturile stanga sus si dreapta jos corpului
	double tx, ty, tz, lx, ly, lz; // t = top, l = lower - determina coordonatele maxime si minime pentru a incadra corpul
	// intr-un cub caruia ii vom determina centrul
	std::vector<Sectiune> sectiuni;
	std::vector<Punct3D> puncte;
	std::vector<Linie> linii;

	//--------------------------------Constructori------------------------------------------

	Corp()
	{
		name = "";
		tx = ty = tz = 1280;
		lx = ly = lz = 0;
		centru = { 0, 0, 0 };
	}

	Corp(std::vector<Punct3D> pncte, std::vector<Linie> lnii, std::string nume)
	{
		name = nume;
		tx = ty = tz = 1280;
		lx = ly = lz = 0;
		centru = { 0, 0, 0 };
		puncte = move(pncte);
		linii = move(lnii);
		DeterminaCentru_Colturi();
	}

	//---------------------------------------Operatori------------------------------------------
	bool operator==(Corp A)
	{
		if (A.name == name && A.lx == lx && A.ly == ly && A.lz == lz && A.tx == tx && A.ty == ty && A.tz == tz
			&& A.centru == centru && A.sectiuni.size() == sectiuni.size() && A.linii.size() ==
			linii.size() && A.puncte.size() == puncte.size())
		{
			for (int i = 0; i < sectiuni.size(); i++)
				if (sectiuni[i] != A.sectiuni[i])
					return false;
			for (int i = 0; i < linii.size(); i++)
				if (linii[i] != A.linii[i])
					return false;
			for (int i = 0; i < puncte.size(); i++)
				if (puncte[i] != A.puncte[i])
					return false;
			return true;
		}
		return false;
	}

	bool operator!=(Corp A)
	{
		if (A.name == name && A.lx == lx && A.ly == ly && A.lz == lz && A.tx == tx && A.ty == ty && A.tz == tz
			&& A.centru == centru && A.sectiuni.size() == sectiuni.size() && A.linii.size() ==
			linii.size() && A.puncte.size() == puncte.size())
		{
			for (int i = 0; i < sectiuni.size(); i++)
				if (sectiuni[i] != A.sectiuni[i])
					return true;
			for (int i = 0; i < linii.size(); i++)
				if (linii[i] != A.linii[i])
					return true;
			for (int i = 0; i < puncte.size(); i++)
				if (puncte[i] != A.puncte[i])
					return true;
			return false;
		}
		return true;
	}

	//-----------------------------------------------Metode------------------------------------------------

	///Afiseaza corpul pe ecran
	void AfisareCorp()
	{
		Punct3D tl(tx, ty, lz);
		Punct TL = Punct::Punct3Dto2D(tl);
		TL.ConvertCoord();
		for (auto& l : linii)
		{
			Punct P1, P2;
			P1 = Punct::Punct3Dto2D(puncte[l.A]);
			P2 = Punct::Punct3Dto2D(puncte[l.B]);
			P1.ConvertCoord();
			P2.ConvertCoord();
			P1.x = zoom * (P1.x - TL.x) + TL.x - offsetX;
			P1.y = zoom * (P1.y - TL.y) + TL.y - offsetY;
			P2.x = zoom * (P2.x - TL.x) + TL.x - offsetX;
			P2.y = zoom * (P2.y - TL.y) + TL.y - offsetY;
			drawLine(P1.x, P1.y, P2.x, P2.y);
		}
	}

	///Determina centrul si colturile corpului
	void DeterminaCentru_Colturi()
	{
		tx = ty = tz = 1280;
		lx = ly = lz = 0;
		for (auto& p : puncte)
		{
			if (p.x < tx) tx = p.x;
			if (p.x > lx) lx = p.x;
			if (p.y < ty) ty = p.y;
			if (p.y > ly) ly = p.y;
			if (p.z < tz) tz = p.z;
			if (p.z > lz) lz = p.z;
		}
		centru.x = (tx + lx) / 2;
		centru.y = (ty + ly) / 2;
		centru.z = (tz + lz) / 2;
		Punct3D P(tx, ty, lz);
		tl_corner = Punct::Punct3Dto2D(P);
		tl_corner.ConvertCoord();
		P.x = lx; P.y = ly; P.z = tz;
		lr_corner = Punct::Punct3Dto2D(P);
		lr_corner.ConvertCoord();
	}
	
	//Adauga un punct in std::vectorul de puncte
	void AdaugarePunct(Punct3D P)
	{
		puncte.push_back(P);
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
		double cz, cy;
		for (auto &P : puncte)
		{
			cy = P.y - centru.y;
			cz = P.z - centru.z;
			P.y = cos(default_angle) * cy - sin(default_angle) * cz + centru.y;
			P.z = sin(default_angle) * cy + cos(default_angle) * cz + centru.z;
		}
	}

	///va roti corpul in sens invers acelor de ceasornic pe axa X
	void RotesteXNeg()
	{
		double cz, cy;
		for (auto &P : puncte)
		{
			cy = P.y - centru.y;
			cz = P.z - centru.z;
			P.y = cos(-default_angle) * cy - sin(-default_angle) * cz + centru.y;
			P.z = sin(-default_angle) * cy + cos(-default_angle) * cz + centru.z;
		}
	}

	///va roti corpul in sensul acelor de ceasornic pe axa Y
	void RotesteYPoz()
	{
		double cz, cx;
		for (auto &P : puncte)
		{
			cx = P.x - centru.x;
			cz = P.z - centru.z;
			P.x = cos(default_angle) * cx - sin(default_angle) * cz + centru.x;
			P.z = sin(default_angle) * cx + cos(default_angle) * cz + centru.z;
		}
	}

	///va roti corpul in sens invers acelor de ceasornic pe axa Y
	void RotesteYNeg()
	{
		double cz, cx;
		for (auto &P : puncte)
		{
			cx = P.x - centru.x;
			cz = P.z - centru.z;
			P.x = cos(-default_angle) * cx - sin(-default_angle) * cz + centru.x;
			P.z = sin(-default_angle) * cx + cos(-default_angle) * cz + centru.z;
		}
	}

	///va roti corpul in sensul acelor de ceasornic pe axa Z
	void RotesteZPoz()
	{
		double cy, cx;
		for (auto &P : puncte)
		{
			cx = P.x - centru.x;
			cy = P.y - centru.y;
			P.x = cos(default_angle) * cx - sin(default_angle) * cy + centru.x;
			P.y = sin(default_angle) * cx + cos(default_angle) * cy + centru.y;
		}
	}

	///va roti corpul in sens invers acelor de ceasornic pe axa Z
	void RotesteZNeg()
	{
		double cy, cx;
		for (auto &P : puncte)
		{
			cx = P.x - centru.x;
			cy = P.y - centru.y;
			P.x = cos(-default_angle) * cx - sin(-default_angle) * cy + centru.x;
			P.y = sin(-default_angle) * cx + cos(-default_angle) * cy + centru.y;
		}
	}
};

class Scena
{
public:
	std::vector<Corp> corpuri;
	std::vector<int> corpuri_selectate;

	//------------------------------------Constructori--------------------------------

	Scena()
	{

	}

	Scena(std::vector<Corp> corp)
	{
		corpuri = move(corp);
	}

	//-------------------------------------Metode---------------------------------------

	void AdaugareCorp()
	{
		Corp C;
		corpuri.push_back(C);
		corpuri_selectate.push_back(corpuri.size() - 1);
	}

	void ChangeSelected(int mouse_x, int mouse_y)
	{
		bool is_selected = false;
		int i, j;
		for (i = 0; i < corpuri.size(); i++)
		{
			Corp C = corpuri[i];
			//cream colturile luand in considerare zoom-ul si offset-ul
			Punct TL(C.tl_corner.x - offsetX - 10, C.tl_corner.y - offsetY - 10), LR(zoom * (C.lr_corner.x - C.tl_corner.x) + C.tl_corner.x - offsetX + 10, zoom * (C.lr_corner.y - C.tl_corner.y) + C.tl_corner.y - offsetY + 10);
			if (mouse_x >= TL.x && mouse_x <= LR.x && mouse_y >= TL.y && mouse_y <= LR.y) //verificam daca mouse-ul era in interiorul corpului cand s-a facut click
			{
				for (j = 0; is_selected == false && j < corpuri_selectate.size(); j++)
					if (corpuri_selectate[j] == i)
						is_selected = true;
				if (is_selected)
				{
					j--; //daca s-a gasit corpul in corpuri_selectate se va trece oricum la urmatorul asa ca trebuie sa decrementam
					corpuri_selectate.erase(corpuri_selectate.begin() + j);
				}
				else corpuri_selectate.push_back(i);
				clearviewport();
				IncarcaScena();
			}
		}
	}

	void IncarcaScena()
	{
		for (auto& C : corpuri)
		{
			C.DeterminaCentru_Colturi();
			C.AfisareCorp();
			//evidentiaza corpurile selectate
			for (auto& i : S.corpuri_selectate)
				if (S.corpuri[i] == C)
					drawEmptyRectangle(C.tl_corner.x - offsetX - 10, C.tl_corner.y - offsetY - 10, zoom * (C.lr_corner.x - C.tl_corner.x) + C.tl_corner.x - offsetX + 10, zoom * (C.lr_corner.y - C.tl_corner.y) + C.tl_corner.y - offsetY + 10, COLOR(118, 118, 118), 1, DOTTED_LINE);
		}
	}
} S;
#endif // !CORP_H
