//
// Created by Lorenzo on 22/03/2022.
//

#ifndef AKINATOR_C_LINKED_LIST_ID_H
#define AKINATOR_C_LINKED_LIST_ID_H

typedef struct lcId {
    int id;
    struct lcId *suiv;
} LcId;

void insertionFinListe(LcId **F, LcId *E);
void suppressionBonnePlace(LcId **F, int id);
void affiche_file(LcId *F);
void init_file(LcId *F);
void suppressionTotId(LcId **F);

#endif //AKINATOR_C_LINKED_LIST_ID_H





