//
// Created by Lorenzo on 28/03/2022.
//

#ifndef AKINATOR_C_LINKED_LIST_ID_ETAT_H
#define AKINATOR_C_LINKED_LIST_ID_ETAT_H
typedef struct lcIdEtat {
    int id;
    char etat;
    struct lcIdEtat *suiv;
} LcIdEtat;

void insertionFinListeEtat(LcIdEtat **F, LcIdEtat *E);
void suppressionBonnePlaceEtat(LcIdEtat **F, int id);
void affiche_fileEtat(LcIdEtat *F);
void init_fileEtat(LcIdEtat *F);
void suppressionTot(LcIdEtat **F);
#endif //AKINATOR_C_LINKED_LIST_ID_ETAT_H

