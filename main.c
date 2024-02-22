//
// Created by sylvain on 21/03/2022.
//
#include <stdio.h>
#include "menu.h"

int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    int choix =-1;
    while (choix!=0) {
        choix = menu();
        choix=menu_selecteur(choix);
    }
    return 0;
}