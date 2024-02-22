//
// Created by sylvain on 22/03/2022.
//

#ifndef AKINATOR_C_DOUBLE_LINKED_LIST_H
#define AKINATOR_C_DOUBLE_LINKED_LIST_H

#include "linked_list_id_etat.h"
#include "linked_list_id.h"

#define HEADER_MAX_STRING_SIZE 256

typedef struct dlcBody {
    char etat;
    int id_question;
    int id_perso;
    struct dlcBody *suiv_perso;
    struct dlcBody *suiv_question;
} DlcBody;

typedef struct dlcHeader {
    int id;
    char content[HEADER_MAX_STRING_SIZE];
    struct dlcHeader *suiv_header;
    DlcBody *first_body;
} DlcHeader;

typedef struct dlcController {
    DlcHeader *list_question;
    DlcHeader *list_perso;
    int next_id_question;
    int next_id_perso;
} DlcController;


DlcController dlcControllerInit();

DlcHeader *dlcHeaderInit();

DlcBody *dlcBodyInit();

int dlcControllerGetNextIdQuestion(DlcController *controller);

int dlcControllerGetNextIdPerso(DlcController *controller);

void dlcControllerAddQuestion(DlcController *controller, DlcHeader *question);

void dlcControllerAddPerso(DlcController *controller, DlcHeader *perso);

void dlcPrint(DlcController controller);

void dlcControlerFreeMemory(DlcController *controller);

void fill_respsonse(DlcHeader *perso, LcIdEtat *responses);

void dlcControllerGetPerso(DlcController controller, LcId **list);

DlcHeader *dlcControllerGetPersoById(DlcController controller, int id);

DlcHeader *dlcControllerGetQuestionById(DlcController controller, int id);

DlcHeader *getNextQuestion(DlcController controller, LcIdEtat *listQuestionPose);

void eliminatePerso(DlcController controller, LcId **list_perso, LcIdEtat *last_question);

DlcBody *dlcControllerGetBodyByIds(DlcController controller, int id_perso, int id_question);

DlcHeader *dlcControllerGetPersoProposition(DlcController controller, LcId *list_perso, LcIdEtat *list_question);

#endif //AKINATOR_C_DOUBLE_LINKED_LIST_H
