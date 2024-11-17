#pragma once
#include "Corp.h"
#include "myGraphics.h"

Punct3D::Punct3D()
{
	x = y = z = 0;
}

Punct3D::Punct3D(int coord_x, int coord_y, int coord_z)
{
	x = coord_x;
	y = coord_y;
	z = coord_z;
}

bool Punct3D::operator==(Punct3D P)
{
	if (P.x == x && P.y == y && P.z == z)
		return true;
	return false;
}

bool Punct3D::operator!=(Punct3D P)
{
	if (P.x != x || P.y != y || P.z != z)
		return true;
	return false;
}

Punct::Punct()
{
	x = y = 0;
}

Punct::Punct(double coord_x, double coord_y)
{
	x = coord_x;
	y = coord_y;
}

bool Punct::operator==(Punct P)
{
	if (P.x == x && P.y == y)
		return true;
	return false;
}

bool Punct::operator!=(Punct P)
{
	if (P.x != x || P.y != y)
		return true;
	return false;
}

Punct Punct::Punct3Dto2D(Punct3D A)
{
	Punct P;
	P.x = A.x * dist_obs / (dist_obs + A.z);
	P.y = A.y * dist_obs / (dist_obs + A.z);
	return P;
}

Punct3D Punct::Punct2Dto3D(Punct A, int z_pos)
{
	Punct3D P;
	P.x = A.x * (dist_obs + z_pos) / dist_obs;
	P.y = A.y * (dist_obs + z_pos) / dist_obs;
	P.z = z_pos;
	return P;
}

void Punct::ConvertCoord()
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

Linie::Linie()
{
	A = 0;
	B = 0;
}

Linie::Linie(int P1, int P2)
{
	A = P1;
	B = P2;
}

bool Linie::operator==(const Linie& L)
{
	if (L.A == A && L.B == B)
		return true;
	return false;
}

bool Linie::operator!=(const Linie& L)
{
	if (L.A != A || L.B != B)
		return true;
	return false;
}

Sectiune::Sectiune()
{
	z = 0;
}

Sectiune::Sectiune(int poz_z)
{
	z = poz_z;
}

bool Sectiune::operator==(Sectiune sect)
{
	if (sect.z == z)
		return true;
	return false;
}

bool Sectiune::operator!=(Sectiune sect)
{
	if (sect.z == z)
		return false;
	return true;
}

Corp::Corp()
{
	name = "";
	pminim = { 1280, 1280, 1280 };
	pmaxim = { 0, 0, 0 };
	centru = { 0, 0, 0 };
	offset_local = { 0, 0 };
}

Corp::Corp(std::vector<Punct3D> pncte, std::vector<Linie> lnii, std::vector<Sectiune> sect, Punct offset, std::string nume)
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

bool Corp::operator==(Corp A)
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

bool Corp::operator!=(Corp A)
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

void Corp::AfisareCorp()
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
		if (puncte[l.A].z == selectedStrat && puncte[l.B].z == selectedStrat && editMode && selectedCorpName == this->name)
			drawLine(P1.x, P1.y, P2.x, P2.y, GREEN);
		else
			drawLine(P1.x, P1.y, P2.x, P2.y, WHITE);
	}
}

void Corp::AfisareCorpFete(double tzoom, int offsetX, int offsetY)
{
	for (auto& l : linii) {
		Punct P1, P2;
		P1 = Punct::Punct3Dto2D(puncte[l.A]);
		P2 = Punct::Punct3Dto2D(puncte[l.B]);
		P1.ConvertCoord();
		P2.ConvertCoord();
		P1.x = tzoom * P1.x + offsetX;
		P1.y = tzoom * P1.y + offsetY;
		P2.x = tzoom * P2.x + offsetX;
		P2.y = tzoom * P2.y + offsetY;
		drawLine(P1.x, P1.y, P2.x, P2.y, WHITE);
	}

	printf("Afisare zoom: %i\n", tzoom);
	std::vector<Punct> puncte2D;
	for (auto& p : puncte) {
		Punct P = Punct::Punct3Dto2D(p);
		P.ConvertCoord();
		P.x = tzoom * P.x + offsetX;
		P.y = tzoom * P.y + offsetY;
		puncte2D.push_back(P);
	}
	std::set<int> strats;
	for (auto& p : puncte) {
		strats.insert(p.z);
	}
	std::vector<int> v;
	for (auto x : strats) {
		v.push_back(x);
	}
	reverse(v.begin(), v.end());

	int fr[100];
	for (int i = 0; i < 100; ++i) {
		fr[i] = 0;
	}
	for (auto s : v) {
		//Cautam intai fete care au puncte cu acelasi Z
		int index = 0;
		for (auto f : faces) {
			if (fr[index] == 0) {
				int aux = f[f.size() - 1]; f.pop_back();
				bool ok = true;
				for (auto x : f) {
					if (puncte[x].z != s) {
						ok = false;
						break;
					}
				}
				if (ok) {
					fr[index] = 1;
					int fxy[20]; int index = 0;
					//cream poligonul 
					for (auto p : f) {
						fxy[index++] = puncte2D[p].x;
						fxy[index++] = puncte2D[p].y;
					}
					fxy[index++] = puncte2D[f[0]].x;
					fxy[index] = puncte2D[f[0]].y;
					setfillstyle(SOLID_FILL, aux);
					fillpoly(f.size(), fxy);
				}
				f.push_back(aux);
			}
			index++;
		}
		//Cautam fete care au macar o coordonata z = s
		index = 0;
		for (auto f : faces) {
			if (fr[index] == 0) {
				int aux = f[f.size() - 1]; f.pop_back();
				bool ok = false;
				for (auto x : f) {
					if ((int)puncte[x].z == s) {
						ok = true;
						break;
					}
				}
				if (ok) {

					fr[index] = 1;
					int fxy[20]; int index = 0;
					//cream poligonul 
					for (auto p : f) {
						fxy[index++] = puncte2D[p].x;
						fxy[index++] = puncte2D[p].y;
					}
					fxy[index++] = puncte2D[f[0]].x;
					fxy[index] = puncte2D[f[0]].y;
					setfillstyle(SOLID_FILL, aux);
					fillpoly(f.size(), fxy);
				}
				f.push_back(aux);
			}
			index++;
		}
	}
}

void Corp::AdaugareFata(std::vector<int> v)
{
	faces.push_back(v);
}

void Corp::DeterminaCentru_Colturi()
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

void Corp::AdaugarePunct(Punct3D P)
{
	puncte.push_back(P);
}

void Corp::EliminaPunct()
{
	puncte.pop_back();
}

void Corp::AdaugareLinie(Linie L)
{
	linii.push_back(L);
}

void Corp::RotesteXPoz()
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

void Corp::RotesteXNeg()
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

void Corp::RotesteYPoz()
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

void Corp::RotesteYNeg()
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

void Corp::RotesteZPoz()
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

void Corp::RotesteZNeg()
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

Scena::Scena(std::vector<Corp> corp)
{
	corpuri = move(corp);
	corpuri_origin = corpuri;
}

void Scena::ApplyChanges()
{
	for (auto& C : S.corpuri)
	{
		C.puncte_origin = C.puncte;
		C.linii_origin = C.linii;
		C.sectiuni_origin = C.sectiuni;
	}
	S.corpuri_origin = S.corpuri;
}

void Scena::AdaugareCorp()
{
	Corp C;
	int len = corpuri.size();
	C.name = "Corp" + std::to_string(len);
	corpuri.push_back(C);
	corpuri_selectate.push_back(corpuri.size() - 1);
}

void Scena::EliminaCorp(int ind_corp)
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

void Scena::ResetObject(int ind_corp)
{
	corpuri[ind_corp].puncte = corpuri[ind_corp].puncte_origin;
	corpuri[ind_corp].offset_local = { 0, 0 };
	corpuri[ind_corp].linii = corpuri[ind_corp].linii_origin;
	corpuri[ind_corp].sectiuni = corpuri[ind_corp].sectiuni_origin;
	clearviewport();
	IncarcaScena();
}

void Scena::ResetScene()
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

void Scena::ChangeSelected(int mouse_x, int mouse_y)
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

void Scena::UserDrawLine(int mouse_x, int mouse_y, int draw_step, int z_pos, int ind_corp)
{
	bool exists = false;
	for (auto& sect : corpuri[ind_corp].sectiuni)
		if (sect.z == selectedStrat)
			exists = true;
	if (!exists) corpuri[ind_corp].sectiuni.push_back(Sectiune(selectedStrat));
	if (draw_step == 0)
	{
		Punct P(mouse_x, mouse_y);
		corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
	}
	else if (draw_step == 1)
	{
		Punct P(mouse_x, mouse_y);
		corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
		int len = corpuri[ind_corp].puncte.size();
		corpuri[ind_corp].AdaugareLinie(Linie(len - 2, len - 1));
		clearviewport();
		IncarcaScena();
	}
}

void Scena::UserDrawRectangle(int mouse_x, int mouse_y, int draw_step, int z_pos, int ind_corp)
{
	bool exists = false;
	for (auto& sect : corpuri[ind_corp].sectiuni)
		if (sect.z == selectedStrat)
			exists = true;
	if (!exists) corpuri[ind_corp].sectiuni.push_back(Sectiune(selectedStrat));
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
		corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(Punct(mouse_x, P1.y), z_pos));
		corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
		corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(Punct(P1.x, mouse_y), z_pos));
		len = corpuri[ind_corp].puncte.size();
		corpuri[ind_corp].AdaugareLinie(Linie(len - 1, len - 4));
		corpuri[ind_corp].AdaugareLinie(Linie(len - 4, len - 3));
		corpuri[ind_corp].AdaugareLinie(Linie(len - 3, len - 2));
		corpuri[ind_corp].AdaugareLinie(Linie(len - 2, len - 1));
		clearviewport();
		IncarcaScena();
	}
}

void Scena::UserDrawCircle(int mouse_x, int mouse_y, int draw_step, int z_pos, int ind_corp)
{
	bool exists = false;
	for (auto& sect : corpuri[ind_corp].sectiuni)
		if (sect.z == selectedStrat)
			exists = true;
	if (!exists) corpuri[ind_corp].sectiuni.push_back(Sectiune(selectedStrat));
	if (draw_step == 0)
	{
		Punct P(mouse_x, mouse_y);
		corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
	}
	else if (draw_step == 1)
	{
		int len = S.corpuri[ind_corp].puncte.size();
		Punct P(mouse_x, mouse_y);
		Punct P1 = Punct::Punct3Dto2D(S.corpuri[ind_corp].puncte[len - 1]);
		P1.ConvertCoord();
		corpuri[ind_corp].EliminaPunct(); //eliminam punctul adaugat pentru referinta
		len--;
		Punct centru((P.x + P1.x) / 2, (P.y + P1.y) / 2);
		double width = abs(P.x - P1.x), height = abs(P.y - P1.y), a = width / 2, b = height / 2;
		int nr_puncte = (width + height) / 8;
		double unghi_dif = 2 * PI / nr_puncte; //unghiul dintre puncte relativ la centru
		for (double i = 0; i < nr_puncte; i++)
		{
			Punct A(centru.x + a * cos(i * unghi_dif), centru.y + b * sin(i * unghi_dif));
			corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(A, z_pos));
			len++;
			if (i > 0) S.corpuri[ind_corp].AdaugareLinie(Linie(len - 1, len - 2));
		}
		corpuri[ind_corp].AdaugareLinie(Linie(len - 1, len - nr_puncte));
		clearviewport();
		IncarcaScena();
	}
}

void Scena::UserAddPoint(int mouse_x, int mouse_y, int z_pos, int ind_corp)
{
	bool exists = false;
	for (auto& sect : corpuri[ind_corp].sectiuni)
		if (sect.z == selectedStrat)
			exists = true;
	if (!exists) corpuri[ind_corp].sectiuni.push_back(Sectiune(selectedStrat));
	Punct P(mouse_x, mouse_y);
	corpuri[ind_corp].AdaugarePunct(Punct::Punct2Dto3D(P, z_pos));
	clearviewport();
	IncarcaScena();
}

void Scena::UserLinkPoints(int mouse_x, int mouse_y, int draw_step, int ind_corp)
{
	static int punct_selectat = 0;
	double dist_min = 200000, dist = 0, diff_x, diff_y;
	Punct P1;
	if (draw_step == 0)
	{
		for (int i = 0; i < S.corpuri[ind_corp].puncte.size(); i++)
		{
			Punct3D P = corpuri[ind_corp].puncte[i];
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
		for (int i = 0; i < corpuri[ind_corp].puncte.size(); i++)
		{
			Punct3D P = corpuri[ind_corp].puncte[i];
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
		corpuri[ind_corp].AdaugareLinie(Linie(punct_selectat, punct_nou));
		clearviewport();
		IncarcaScena();
	}
}

void Scena::IncarcaScena()
{
	for (auto& C : corpuri)
	{
		C.DeterminaCentru_Colturi();
		C.AfisareCorp();
		//evidentiaza corpurile selectate
		for (auto& i : corpuri_selectate)
			if (corpuri[i] == C)
				drawEmptyRectangle(C.tl_corner.x - offsetX - C.offset_local.x - 10, C.tl_corner.y - offsetY - C.offset_local.y - 10, zoom * (C.lr_corner.x - C.tl_corner.x) + C.tl_corner.x - offsetX - C.offset_local.x + 10, zoom * (C.lr_corner.y - C.tl_corner.y) + C.tl_corner.y - offsetY - C.offset_local.y + 10, COLOR(118, 118, 118), 1, DOTTED_LINE);
	}
}