#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include "Intialization.h"
using namespace std;

int main()
{
    InitializeWindow();
    while(kbhit) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            //printf("%i, %i\n", mousex(), mousey());
            if(GB.MAPPED_BUTTONS[mousex()][mousey()] != 0) {
                //cand sunt mai multe facem search la ce buton a fost apasat
                printf("The button has been clicked\n");
                clearmouseclick(WM_LBUTTONDOWN);
                delay(10);
            }
        }
        delay(10);
    }
    getch();
}