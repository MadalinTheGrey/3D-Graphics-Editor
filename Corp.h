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

	Punct()
	{
		x = y = 0;
	}

	Punct(double coord_x, double coord_y)
	{
		x = coord_x;
		y = coord_y;
	}

	/// returneaza proiectia unui punct 3D pe planul ecranului
	Punct Punct3Dto2D(Punct3D A)
	{
		Punct P;
		P.x = A.x * dist_obs / (dist_obs + A.z);
		P.y = A.y * dist_obs / (dist_obs + A.z);
		return P;
	}

	//converteste un punct 2D in 3D cunoscand pozitia sa in z
	Punct3D Punct2Dto3D(Punct A, int z_pos)
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

	void AddLinie(Linie L)
	{
		linii_sect.push_back(L);
	}
};

class Corp
{
public:
	std::string name;
	bool selected;
	Punct3D centru, tl_corner, lr_corner; // centrul corpului si colturile
	double tx, ty, tz, lx, ly, lz; // t = top, l = lower - determina coordonatele maxime si minime pentru a incadra corpul
	// intr-un cub caruia ii vom determina centrul
	std::vector<Sectiune> sectiuni;
	std::vector<Punct3D> puncte;
	std::vector<Linie> linii;

	Corp()
	{
		name = "";
		selected = false;
		tx = ty = tz = 1280;
		lx = ly = lz = 0;
		centru = { 0, 0, 0 };
	}

	Corp(std::vector<Punct3D> pncte, std::vector<Linie> lnii, std::string nume)
	{
		name = nume;
		selected = false;
		tx = ty = tz = 1280;
		lx = ly = lz = 0;
		centru = { 0, 0, 0 };
		puncte = move(pncte);
		linii = move(lnii);
		DeterminaCentru();
	}

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

	void AfisareCorp()
	{
		Punct TL;
		Punct3D tl(tx, ty, lz);
		TL = TL.Punct3Dto2D(tl);
		TL.ConvertCoord();
		for (auto& l : linii)
		{
			Punct P1, P2;
			P1 = P1.Punct3Dto2D(puncte[l.A]);
			P2 = P2.Punct3Dto2D(puncte[l.B]);
			P1.ConvertCoord();
			P2.ConvertCoord();
			P1.x = zoom * (P1.x - TL.x) + TL.x - offsetX;
			P1.y = zoom * (P1.y - TL.y) + TL.y - offsetY;
			P2.x = zoom * (P2.x - TL.x) + TL.x - offsetX;
			P2.y = zoom * (P2.y - TL.y) + TL.y - offsetY;
			drawLine(P1.x, P1.y, P2.x, P2.y);
		}
		if (selected)
		{
			Punct3D lr(lx, ly, tz);
			Punct LR;
			LR = LR.Punct3Dto2D(lr);
			LR.ConvertCoord();
			TL.x = TL.x - offsetX - 10;
			TL.y = TL.y - offsetY - 10;
			LR.x = zoom * (LR.x - TL.x) + TL.x - offsetX + 10;
			LR.y = zoom * (LR.y - TL.y) + TL.y - offsetY + 10;
			drawEmptyRectangle(TL.x, TL.y, LR.x, LR.y, COLOR(118, 118, 118), 1, DOTTED_LINE);
		}
	}

	void DeterminaCentru()
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
	std::vector<Corp> corpuri_selectate;

	Scena()
	{
		
	}

	Scena(std::vector<Corp> corp)
	{
		corpuri = move(corp);
	}

	void AdaugareCorp()
	{
		Corp C;
		corpuri_selectate.clear();
		corpuri_selectate.push_back(C);
		corpuri.push_back(C);
	}

	void ChangeSelected(int mouse_x, int mouse_y)
	{
		Punct3D P;
		Punct P1, P2;
		for (auto& C : corpuri)
		{
			P.x = C.tx; P.y = C.ty; P.z = C.lz;
			P1 = P1.Punct3Dto2D(P);
			P1.ConvertCoord();
			P.x = C.lx; P.y = C.ly; P.z = C.tz;
			P2 = P2.Punct3Dto2D(P);
			P2.ConvertCoord();
			P1.x = P1.x - offsetX - 10;
			P1.y = P1.y - offsetY - 10;
			P2.x = zoom * (P2.x - P1.x) + P1.x - offsetX + 10;
			P2.y = zoom * (P2.y - P1.y) + P1.y - offsetY + 10;
			if (mouse_x >= P1.x && mouse_x <= P2.x && mouse_y >= P1.y && mouse_y <= P2.y)
			{
				if (C.selected == true)
				{
					for (int i = 0;C.selected == true && i < corpuri_selectate.size(); i++)
						if (corpuri_selectate[i] == C)
						{
							corpuri_selectate.erase(corpuri_selectate.begin() + i);
							C.selected = false;
						}
				}
				else
				{
					corpuri_selectate.push_back(C);
					C.selected = true;
				}
				clearviewport();
				IncarcaScena();
			}
		}
	}

	void IncarcaScena()
	{
		for (auto& C : corpuri)
			C.AfisareCorp();
	}
} S;
#endif // !CORP_H
