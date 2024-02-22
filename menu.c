//
// Created by isen on 25/03/2022.
//

#include "menu.h"
// repertoire d'imote ⊩╢║╝╔╗╚ ≺⚟⚞≻

int menu() {
    int choix = 0;

    printf("\n╔═══════⚞≻Menu≺⚟════════╗\n");
    printf("║Quel est votre choix ? ║\n");
    printf("╟-----------------------╢\n");
    printf("║1 - jouer :            ║\n");
    printf("║0 - Quitter:           ║\n");
    printf("╚═══════════════════════╝\n");
    char buffer[256]="";
    fgets(buffer,256,stdin);
    sscanf(buffer,"%d", &choix);

    return choix;
}

int menu_theme() {
    int choix = 0;

    printf("\n╔═══════⚞≻Menu≺⚟════════╗\n");
    printf("║Quel est votre choix ? ║\n");
    printf("╟-----------------------╢\n");
    printf("║1 - anime :            ║\n");
    printf("║2 - film :             ║\n");
    printf("║3 - jeux-vidéo :       ║\n");
    printf("║0 - Quitter:           ║\n");
    printf("╚═══════════════════════╝\n");

    char buffer[256]="";
    fgets(buffer,256,stdin);
    sscanf(buffer,"%d", &choix);

    return choix;
}

int menu_selecteur(int choix){
    int choix2=-1;
    switch (choix)
    {
        case 0:
        {
            system("clear");
            break;
        }
        case 1:
            system("clear");
            choix2=menu_theme();
            choix=menu_theme_selecteur(choix2,choix);
            break;
    }
    return choix;
}

int menu_theme_selecteur(int choix2,int choix){
    switch (choix2) {
        case 0: {
            system("clear");
            choix=-1;
            break;
        }
        case 1:
            system("clear");
            printf("Vous jouez en mode anime\n");
            partie("anime.txt");
            break;
        case 2: {
            system("clear");
            printf("Vous jouez en mode film\n");
            partie("film.txt");
            break;
        }
        case 3: {
            system("clear");
            printf("Vous jouez en mode jeux-vidéo\n");
            partie("jv.txt");
            break;
        }
    }
    return choix;
}