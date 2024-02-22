//
// Created by Lorenzo on 28/03/2022.
//

#include "linked_list_id_etat.h"
#include <stdlib.h>
#include <stdio.h>


void init_fileEtat(LcIdEtat *F){
    F->id = 0;
    F->etat = 'u';
    F->suiv = NULL;
}

void affiche_fileEtat(LcIdEtat *F){
    LcIdEtat *cour = F;
    while(cour!=NULL){
        printf("%d\n%c\n",cour->id,cour->etat);
        cour=cour->suiv;
    }
}


void insertionFinListeEtat(LcIdEtat **F, LcIdEtat *E){
    LcIdEtat *cour = *F;
    if(cour == NULL){
        *F=E;
        return;
    }
    while(cour->suiv != NULL){
        cour = cour->suiv;
    }
    cour->suiv = E;

}

void suppressionBonnePlaceEtat(LcIdEtat **F, int id){
    LcIdEtat *cour = *F, *prec = *F;
    if(cour == NULL){
        return;
    }
    while(cour != NULL && cour->id != id ){
        prec = cour;
        cour = cour->suiv;
    }
    if( cour != NULL){
        prec->suiv = cour->suiv;
        free(cour);
    }
}

void suppressionTot(LcIdEtat **F){
    LcIdEtat *cour = *F, *prec = *F;
    if(cour == NULL){
        return;
    }
    while(cour != NULL ){
        prec = cour;
        cour = cour->suiv;
        free(prec);
    }
}