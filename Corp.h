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
	double x, y;

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
	int A, B; //indexurile punctelor in vectorul puncte

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
	std::vector<int> linii_sect; //memoreaza indicii liniilor sectiunii din vectorul de linii al corpului
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

	Sectiune(int poz_z, std::vector<int> B)
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

	//--------------------------------Constructori------------------------------------------

	Corp()
	{
		name = "";
		pminim = { 1280, 1280, 1280 };
		pmaxim = { 0, 0, 0 };
		centru = { 0, 0, 0 };
		offset_local = { 0, 0 };
	}

	Corp(std::vector<Punct3D> pncte, std::vector<Linie> lnii, std::vector<Sectiune> sect, Punct offset, std::string nume)
	{
		name = nume;
		pminim = { 1280, 1280, 1280 };
		pmaxim = { 0, 0, 0 };
		centru = { 0, 0, 0 };
		offset_local = offset;
		puncte = move(pncte);
		puncte_origin = puncte;
		linii = move(lnii);
		linii_origin = linii;
		sectiuni = move(sect);
		sectiuni_origin = sectiuni;
		DeterminaCentru_Colturi();
	}

	//---------------------------------------Operatori------------------------------------------
	bool operator==(Corp A)
	{
		if (A.name == name && A.pmaxim == pmaxim && A.pminim == pminim && A.centru == centru
			&& A.sectiuni.size() == sectiuni.size() && A.linii.size() == linii.size() && A.puncte.size() == puncte.size())
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
		if (A.name == name && A.pmaxim == pmaxim && A.pminim == pminim && A.centru == centru
			&& A.sectiuni.size() == sectiuni.size() && A.linii.size() == linii.size() && A.puncte.size() == puncte.size())
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
		for (auto& l : linii)
		{
			Punct P1, P2;
			P1 = Punct::Punct3Dto2D(puncte[l.A]);
			P2 = Punct::Punct3Dto2D(puncte[l.B]);
			P1.ConvertCoord();
			P2.ConvertCoord();
			P1.x = zoom * (P1.x - tl_corner.x) + tl_corner.x - offsetX - offset_local.x;
			P1.y = zoom * (P1.y - tl_corner.y) + tl_corner.y - offsetY - offset_local.y;
			P2.x = zoom * (P2.x - tl_corner.x) + tl_corner.x - offsetX - offset_local.x;
			P2.y = zoom * (P2.y - tl_corner.y) + tl_corner.y - offsetY - offset_local.y;
			if(puncte[l.A].z == selectedStrat && puncte[l.B].z == selectedStrat && editMode && selectedCorpName == this->name)
				drawLine(P1.x, P1.y, P2.x, P2.y, GREEN);
			else 
				drawLine(P1.x, P1.y, P2.x, P2.y, WHITE);
		}
	}

	///Determina centrul si colturile corpului
	void DeterminaCentru_Colturi()
	{
		pminim = { 1280, 1280, 1280 };
		pmaxim = { 0, 0, 0 };
		for (auto& p : puncte)
		{
			if (p.x < pminim.x) pminim.x = p.x;
			if (p.x > pmaxim.x) pmaxim.x = p.x;
			if (p.y < pminim.y) pminim.y = p.y;
			if (p.y > pmaxim.y) pmaxim.y = p.y;
			if (p.z < pminim.z) pminim.z = p.z;
			if (p.z > pmaxim.z) pmaxim.z = p.z;
		}
		if (pminim == Punct3D(1280, 1280, 1280) && pmaxim == Punct3D(0, 0, 0))
		{
			centru = { 0, 0, 0 };
			tl_corner = { 0, 0 };
			lr_corner = { 0, 0 };
		}
		else
		{
			centru.x = (pminim.x + pmaxim.x) / 2;
			centru.y = (pminim.y + pmaxim.y) / 2;
			centru.z = (pminim.z + pmaxim.z) / 2;
			Punct3D P(pminim.x, pminim.y, pmaxim.z);
			tl_corner = Punct::Punct3Dto2D(P);
			tl_corner.ConvertCoord();
			P.x = pmaxim.x; P.y = pmaxim.y; P.z = pminim.z;
			lr_corner = Punct::Punct3Dto2D(P);
			lr_corner.ConvertCoord();
		}
	}

	//Adauga un punct in vectorul de puncte
	void AdaugarePunct(Punct3D P)
	{
		puncte.push_back(P);
	}

	//Elimina ultimul punct adaugat in vectorul de puncte
	void EliminaPunct()
	{
		puncte.pop_back();
	}
	void AdaugareLinie(Linie L)
	{
		linii.push_back(L);
	}

	///va roti corpul in sensul acelor de ceasornic pe axa X
	void RotesteXPoz()
	{
		double cz, cy;
		for (auto& P : puncte)
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
		for (auto& P : puncte)
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
		for (auto& P : puncte)
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
		for (auto& P : puncte)
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
		for (auto& P : puncte)
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
		for (auto& P : puncte)
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
	std::vector<Corp> corpuri_origin; //corpuri care erau original in scena
	std::vector<int> corpuri_selectate;

	//------------------------------------Constructori--------------------------------

	Scena()
	{

	}

	Scena(std::vector<Corp> corp)
	{
		corpuri = move(corp);
		corpuri_origin = corpuri;
	}

	//-------------------------------------Metode---------------------------------------

	void ApplyChanges()
	{
		for (auto& C : S.corpuri)
		{
			C.puncte_origin = C.puncte;
			C.linii_origin = C.linii;
			C.sectiuni_origin = C.sectiuni;
		}
		S.corpuri_origin = S.corpuri;
	}

	void AdaugareCorp()
	{
		Corp C;
		corpuri.push_back(C);
		corpuri_selectate.push_back(corpuri.size() - 1);
	}

	void EliminaCorp(int ind_corp)
	{
		int i;
		corpuri.erase(corpuri.begin() + ind_corp);
		for (i = 0; i < corpuri_selectate.size(); i++)
			if (corpuri_selectate[i] == ind_corp)
				break;
		corpuri_selectate.erase(corpuri_selectate.begin() + i);
		clearviewport();
		IncarcaScena();
	}

	void ResetObject(int ind_corp)
	{
		corpuri[ind_corp].puncte = corpuri[ind_corp].puncte_origin;
		corpuri[ind_corp].offset_local = { 0, 0 };
		corpuri[ind_corp].linii = corpuri[ind_corp].linii_origin;
		corpuri[ind_corp].sectiuni = corpuri[ind_corp].sectiuni_origin;
		clearviewport();
		IncarcaScena();
	}

	void ResetScene()
	{
		for (int i = 0; i < corpuri.size(); i++)
			ResetObject(i);
		offsetX = offsetY = 0;
		zoom = 1;
		corpuri = corpuri_origin;
		corpuri_selectate.clear();
		clearviewport();
		IncarcaScena();
	}

	void ChangeSelected(int mouse_x, int mouse_y)
	{
		bool is_selected = false;
		int i, j;
		for (i = 0; i < corpuri.size(); i++)
		{
			Corp C = corpuri[i];
			//cream colturile luand in considerare zoom-ul si offset-ul
			Punct TL(C.tl_corner.x - offsetX - C.offset_local.x - 10 + vp_tl_x, C.tl_corner.y - offsetY - C.offset_local.y - 10 + vp_tl_y), LR(zoom * (C.lr_corner.x - C.tl_corner.x) + C.tl_corner.x - offsetX - C.offset_local.x + 10 + vp_tl_x, zoom * (C.lr_corner.y - C.tl_corner.y) + C.tl_corner.y - offsetY - C.offset_local.y + 10 + vp_tl_y);
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
				break;
			}
		}
	}

	///deseneaza o linie pe ecran pentru user
	void UserDrawLine(int mouse_x, int mouse_y, int draw_step, int z_pos, int ind_corp)
	{
		if (draw_step == 0)
		{
			Punct P(mouse_x, mouse_y);
			corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
		}
		else if (draw_step == 1)
		{
			Punct P(mouse_x, mouse_y);
			S.corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
			int len = corpuri[ind_corp].puncte.size();
			corpuri[ind_corp].AdaugareLinie(Linie(len - 2, len - 1));
			clearviewport();
			IncarcaScena();
		}
	}

	///deseneaza un dreptunghi pe ecran pentru user
	void UserDrawRectangle(int mouse_x, int mouse_y, int draw_step, int z_pos, int ind_corp)
	{
		if (draw_step == 0)
		{
			Punct P(mouse_x, mouse_y);
			corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
		}
		else if (draw_step == 1)
		{
			Punct P(mouse_x, mouse_y);
			int len = corpuri[ind_corp].puncte.size();
			Punct P1 = Punct::Punct3Dto2D(corpuri[ind_corp].puncte[len - 1]);
			P1.ConvertCoord();
			S.corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(Punct(mouse_x, P1.y), z_pos));
			S.corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
			S.corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(Punct(P1.x, mouse_y), z_pos));
			len = corpuri[ind_corp].puncte.size();
			corpuri[ind_corp].AdaugareLinie(Linie(len - 1, len - 4));
			corpuri[ind_corp].AdaugareLinie(Linie(len - 4, len - 3));
			corpuri[ind_corp].AdaugareLinie(Linie(len - 3, len - 2));
			corpuri[ind_corp].AdaugareLinie(Linie(len - 2, len - 1));
			clearviewport();
			IncarcaScena();
		}
	}

	///deseneaza un cerc pe ecran pentru user
	void UserDrawCircle(int mouse_x, int mouse_y, int draw_step, int z_pos, int ind_corp)
	{
		if (draw_step == 0)
		{
			Punct P(mouse_x, mouse_y);
			S.corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
		}
		else if (draw_step == 1)
		{
			int len = S.corpuri[ind_corp].puncte.size();
			Punct P(mouse_x, mouse_y);
			Punct P1 = Punct::Punct3Dto2D(S.corpuri[ind_corp].puncte[len - 1]);
			P1.ConvertCoord();
			S.corpuri[ind_corp].EliminaPunct(); //eliminam punctul adaugat pentru referinta
			len--;
			Punct centru((P.x + P1.x) / 2, (P.y + P1.y) / 2);
			double width = abs(P.x - P1.x), height = abs(P.y - P1.y), a = width / 2, b = height / 2;
			int nr_puncte = (width + height) / 8;
			double unghi_dif = 2 * PI / nr_puncte; //unghiul dintre puncte relativ la centru
			for (double i = 0; i < nr_puncte; i++)
			{
				Punct A(centru.x + a * cos(i * unghi_dif), centru.y + b * sin(i * unghi_dif));
				S.corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(A, z_pos));
				len++;
				if (i > 0) S.corpuri[ind_corp].AdaugareLinie(Linie(len - 1, len - 2));
			}
			S.corpuri[ind_corp].AdaugareLinie(Linie(len - 1, len - nr_puncte));
			clearviewport();
			IncarcaScena();
		}
	}

	void UserAddPoint(int mouse_x, int mouse_y, int z_pos, int ind_corp)
	{
		Punct P(mouse_x, mouse_y);
		S.corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
		clearviewport();
		IncarcaScena();
	}

	void UserLinkPoints(int mouse_x, int mouse_y, int draw_step, int ind_corp)
	{
		static int punct_selectat = 0;
		double dist_min = 200000, dist = 0, diff_x, diff_y;
		Punct P1;
		if (draw_step == 0)
		{
			for (int i = 0; i < S.corpuri[ind_corp].puncte.size(); i++)
			{
				Punct3D P = S.corpuri[ind_corp].puncte[i];
				P1 = Punct::Punct3Dto2D(P);
				P1.ConvertCoord();
				diff_x = abs(P1.x - mouse_x);
				diff_y = abs(P1.y - mouse_y);
				dist = sqrt(diff_x * diff_x + diff_y * diff_y);
				if (dist < dist_min)
				{
					dist_min = dist;
					punct_selectat = i;
				}
			}
		}
		else
		{
			int punct_nou = 0;
			for (int i = 0; i < S.corpuri[ind_corp].puncte.size(); i++)
			{
				Punct3D P = S.corpuri[ind_corp].puncte[i];
				P1 = Punct::Punct3Dto2D(P);
				P1.ConvertCoord();
				diff_x = abs(P1.x - mouse_x);
				diff_y = abs(P1.y - mouse_y);
				dist = sqrt(diff_x * diff_x + diff_y * diff_y);
				if (dist < dist_min)
				{
					dist_min = dist;
					punct_nou = i;
				}
			}
			S.corpuri[ind_corp].AdaugareLinie(Linie(punct_selectat, punct_nou));
			clearviewport();
			IncarcaScena();
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
					drawEmptyRectangle(C.tl_corner.x - offsetX - C.offset_local.x - 10, C.tl_corner.y - offsetY - C.offset_local.y - 10, zoom * (C.lr_corner.x - C.tl_corner.x) + C.tl_corner.x - offsetX - C.offset_local.x + 10, zoom * (C.lr_corner.y - C.tl_corner.y) + C.tl_corner.y - offsetY - C.offset_local.y + 10, COLOR(118, 118, 118), 1, DOTTED_LINE);
		}
	}
} S;
#endif // !CORP_H