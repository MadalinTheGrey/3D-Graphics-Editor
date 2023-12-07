class Button 
{
public:
	int Xs, Ys, Xd, Yd;

	Button(int xup, int yup, int xdown, int ydown) {
		Xs = xup; Ys = yup;
		Xd = xdown; Yd = ydown;
	}
};

class Punct3D
{
public:
	int x, y, z;

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
	int x, y;

	Punct()
	{
		x = y = 0;
	}

	Punct(int coord_x, int coord_y)
	{
		x = coord_x;
		y = coord_y;
	}

	Punct Punct3Dto2D(Punct3D A)
	{

	}
};

class Linie
{
public:
	Punct A, B;

	Linie()
	{

	}

	Linie(Punct P1, Punct P2)
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
	int nr_puncte, nr_linii; ///numarul de puncte si numarul de linii ale corpului
	int sectiune_curenta; ///sectiunea in care se deseneaza in momentul de fata
	int nr_sectiuni; ///numarul de sectiuni ale corpului, fiecare corp va avea minim o sectiune asa ca incepem de la 1
	Sectiune* sectiuni;

	Corp()
	{
		nr_puncte = 0;
		nr_linii = 0;
		sectiune_curenta = 0;
		nr_sectiuni = 1;
		sectiuni = new Sectiune[1];
	}

	///dubleaza marimea vectorului ce pastreaza sectiunile
	void GrowSectiuni()
	{

	}

	///deseneaza o linie pe ecran pentru user
	void DrawLine()
	{

	}

	///deseneaza un dreptunghi pe ecran pentru user
	void DrawRectangle()
	{

	}

	///deseneaza un cerc pe ecran pentru user
	void DrawCircle()
	{

	}

	///uneste sectiunile A si B ale corpului prin linii intre punctele corespunzatoare
	void UnesteSectiuni(Sectiune A, Sectiune B)
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
