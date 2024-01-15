#ifndef INC_3D_EDITOR_V2_GLOBALVARIABLES_H
#define INC_3D_EDITOR_V2_GLOBALVARIABLES_H

#define BLACK 0x000000
#define PI 3.14159265358979323846

static int windowWidth = 1280;
static int windowHeight = 720;
static char windowName[100] = "3D Editor";
static int windowBgColor = BLACK;
static int windowPosX = 100;
static int windowPosY = 50;
static int dist_obs = 600;
static double zoom = 1;
static double default_angle = 0.01; //unghiul cu care se roteste corpul la cerinta utilizatorului
static int draw_precision = 1; //precizia cu care se deseneaza. poate fi 1/5/10 aproximandu-se coordonatele mouse-ului la un multiplu al acesteia
static double offsetX = 0, offsetY = 0; //modifica pozitia corpurilor in scena
static int last_clicked_button = 0; //retine indicele ultimului buton apasat din meniul din stanga
static int vp_tl_x = 40, vp_tl_y = 30; // coordonate implicite stanga sus viewport
static int vp_dr_x = 1080, vp_dr_y = 720; // coordonate implicite dreapta jos viewport
int FIRST_WINDOW = 1; //variabila care retine daca este prima fereastra deschisa
std::string current_file = ""; //retine numele fara path al fisierului deschis curent
bool renderSceneAgain = false; //cand incarcam din fisier alte scene, sa cu primul frame
bool editButtonSelectable = false;
int selectedCorp = -1;
std::string selectedCorpName = "";
bool editMode = false;
int selectedStrat = 0;
#endif //INC_3D_EDITOR_V2_GLOBALVARIABLES_H
