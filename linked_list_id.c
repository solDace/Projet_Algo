//
// Created by Lorenzo on 22/03/2022.
//

#include "linked_list_id.h"

#include <stdio.h>
#include <stdlib.h>

void init_file(LcId *F){
    F->id = 0;
    F->suiv = NULL;
}

void affiche_file(LcId *F){
    LcId *cour = F;
    while(cour!=NULL){
        printf("%d\n",cour->id);
        cour=cour->suiv;
    }
}


void insertionFinListe(LcId **F, LcId *E){
    LcId *cour = *F;
    if(cour == NULL){
        *F=E;
        return;
    }
    while(cour->suiv != NULL){
        cour = cour->suiv;
    }
    cour->suiv = E;

}

void suppressionBonnePlace(LcId **F, int id){
    LcId *cour = *F, *prec = *F;
    if(cour == NULL){
        return;
    }
    while(cour != NULL && cour->id != id ){
        prec = cour;
        cour = cour->suiv;
    }
    if( cour != NULL){
        if(prec == cour){
            *F = cour->suiv;
        }else {
            prec->suiv = cour->suiv;
        }
        free(cour);
    }
}

void suppressionTotId(LcId **F){
    LcId *cour = *F, *prec = *F;
    if(cour == NULL){
        return;
    }
    while(cour != NULL ){
        prec = cour;
        cour = cour->suiv;
        free(prec);
    }
}











































































