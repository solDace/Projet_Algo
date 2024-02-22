//
// Created by sylvain on 22/03/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "double_linked_list.h"

DlcController dlcControllerInit() {
    DlcController controller;
    controller.list_perso = NULL;
    controller.list_question = NULL;
    controller.next_id_question = 1;
    controller.next_id_perso = 1;
    return controller;
}

DlcHeader *dlcHeaderInit() {
    DlcHeader *header = malloc(sizeof(DlcHeader));
    if (header == NULL) {
        perror("Erreur d'allocation memoire\n");
        exit(-10);
    }
    header->suiv_header = NULL;
    header->first_body = NULL;
    header->id = 0;
    return header;
}

DlcBody *dlcBodyInit() {
    DlcBody *body = malloc(sizeof(DlcBody));
    if (body == NULL) {
        perror("Erreur d'allocation memoire\n");
        exit(-10);
    }
    body->etat = 'u';
    body->id_perso = 0;
    body->id_question = 0;
    body->suiv_perso = NULL;
    body->suiv_question = NULL;
    return body;
}

int dlcControllerGetNextIdQuestion(DlcController *controller) {
    return controller->next_id_question++;
}

int dlcControllerGetNextIdPerso(DlcController *controller) {
    return controller->next_id_perso++;
}

void dlcControllerAddQuestion(DlcController *controller, DlcHeader *question) {
    if (controller->list_question == NULL) {
        controller->list_question = question;
    } else {
        DlcHeader *courQuestion = controller->list_question;
        while (courQuestion->suiv_header != NULL) {
            courQuestion = courQuestion->suiv_header;
        }
        courQuestion->suiv_header = question;
    }
    question->id = dlcControllerGetNextIdQuestion(controller);
    DlcHeader *courPerso = controller->list_perso;
    // On garde la trace du dernier body pour faire la chaine sur la question
    DlcBody **last_body_question = &(question->first_body);

    // On parcourt tous les perso
    while (courPerso != NULL) {
        DlcBody *new_body = dlcBodyInit();
        new_body->id_perso = courPerso->id;
        new_body->id_question = question->id;

        DlcBody **cour_body = &(courPerso->first_body);
        // On atteint le dernier maillon
        while (*cour_body != NULL) {
            cour_body = &(*cour_body)->suiv_perso;
        }
        *cour_body = new_body;
        *last_body_question = new_body;
        last_body_question = &new_body->suiv_question;

        courPerso = courPerso->suiv_header;
    }

}

void dlcControllerAddPerso(DlcController *controller, DlcHeader *perso) {
    if (controller->list_perso == NULL) {
        controller->list_perso = perso;
    } else {
        DlcHeader *cur_perso = controller->list_perso;
        while (cur_perso->suiv_header != NULL) {
            cur_perso = cur_perso->suiv_header;
        }
        cur_perso->suiv_header = perso;
    }
    perso->id = dlcControllerGetNextIdPerso(controller);
    DlcHeader *cur_question = controller->list_question;
    // On garde la trace du dernier body pour faire la chaine sur le perso
    DlcBody **last_body_perso = &(perso->first_body);

    // On parcourt toutes les questions
    while (cur_question != NULL) {
        DlcBody *new_body = dlcBodyInit();
        new_body->id_perso = perso->id;
        new_body->id_question = cur_question->id;

        DlcBody **cour_body = &(cur_question->first_body);
        // On atteint le dernier maillon
        while (*cour_body != NULL) {
            cour_body = &(*cour_body)->suiv_question;
        }
        *cour_body = new_body;
        *last_body_perso = new_body;
        last_body_perso = &new_body->suiv_perso;

        cur_question = cur_question->suiv_header;
    }

}

void dlcPrint(DlcController controller) {
    // Affichage des questions
    DlcHeader *cur_question = controller.list_question;
    while (cur_question != NULL) {
        printf("q%d : %s\n", cur_question->id, cur_question->content);
        cur_question = cur_question->suiv_header;
    }
    // Affichage des questions
    DlcHeader *cur_perso = controller.list_perso;
    while (cur_perso != NULL) {
        printf("p%d : %s -> ", cur_perso->id, cur_perso->content);
        DlcBody *question = cur_perso->first_body;
        while (question != NULL) {
            printf("%c", question->etat);
            if (question->suiv_perso) {
                printf("|");
            } else {
                printf("\n");
            }
            question = question->suiv_perso;
        }
        cur_perso = cur_perso->suiv_header;
    }
}

void dlcControlerFreeMemory(DlcController *controller) {
    DlcHeader *cur_question = controller->list_question;
    while (cur_question != NULL) {
        DlcBody *cur_body = cur_question->first_body;
        while (cur_body != NULL) {
            DlcBody *suiv = cur_body->suiv_question;
            free(cur_body);
            cur_body = suiv;
        }
        DlcHeader *suiv = cur_question->suiv_header;
        free(cur_question);
        cur_question = suiv;
    }
    DlcHeader *cur_perso = controller->list_perso;
    while (cur_perso != NULL) {
        DlcHeader *suiv = cur_perso->suiv_header;
        free(cur_perso);
        cur_perso = suiv;
    }
    controller->list_perso = NULL;
    controller->list_question = NULL;
}

void fill_respsonse(DlcHeader *perso, LcIdEtat *responses) {
    DlcBody *cur_body = perso->first_body;
    while (cur_body != NULL) {
        LcIdEtat *cur_question = responses;
        while (cur_question != NULL && cur_question->id != cur_body->id_question) {
            cur_question = cur_question->suiv;
        }
        if (cur_question != NULL) {
            if (cur_body->etat == 'u' || cur_body->etat == cur_question->etat) {
                cur_body->etat = cur_question->etat;
            }
        }
        cur_body = cur_body->suiv_perso;
    }
}

void dlcControllerGetPerso(DlcController controller, LcId **list) {
    DlcHeader *cur_perso = controller.list_perso;
    while (cur_perso != NULL) {
        LcId *maillon = malloc(sizeof(LcId));
        if (maillon == NULL) {
            perror("Erreur allocation memoire\n");
            exit(-10);
        }
        init_file(maillon);
        maillon->id = cur_perso->id;
        insertionFinListe(list, maillon);
        cur_perso = cur_perso->suiv_header;
    }
}

DlcHeader *dlcControllerGetPersoById(DlcController controller, int id) {
    DlcHeader *cur_perso = controller.list_perso;
    while (cur_perso != NULL) {
        if (cur_perso->id == id) {
            return cur_perso;
        }
        cur_perso = cur_perso->suiv_header;
    }
    return NULL;
}

DlcHeader *dlcControllerGetQuestionById(DlcController controller, int id) {
    DlcHeader *cur_question = controller.list_question;
    while (cur_question != NULL) {
        if (cur_question->id == id) {
            return cur_question;
        }
        cur_question = cur_question->suiv_header;
    }
    return NULL;
}

DlcHeader *getNextQuestion(DlcController controller, LcIdEtat *listQuestionPose) {
    LcIdEtat *cur_question_pose = listQuestionPose;
    DlcHeader *nextQuestion = NULL;
    if (cur_question_pose == NULL) {
        return controller.list_question;
    } else {
        // on atteind le dernier maillon
        while (cur_question_pose->suiv != NULL) {
            cur_question_pose = cur_question_pose->suiv;
        }
        DlcHeader *last_question = dlcControllerGetQuestionById(controller, cur_question_pose->id);
        return last_question->suiv_header;
    }
}

void eliminatePerso(DlcController controller, LcId **list_perso, LcIdEtat *last_question) {
    if (last_question == NULL) {
        return;
    }
    DlcHeader *question_header = dlcControllerGetQuestionById(controller, last_question->id);
    if (question_header == NULL) {
        return;
    }
    // On parcours tous les perso pour enlever ceux qui ne correspondent pas
    DlcBody *cur_body = question_header->first_body;
    while (cur_body != NULL) {
        if (cur_body->etat != 'u' && cur_body->etat != last_question->etat) {
            suppressionBonnePlace(list_perso, cur_body->id_perso);
        }
        cur_body = cur_body->suiv_question;
    }
}

DlcBody *dlcControllerGetBodyByIds(DlcController controller, int id_perso, int id_question) {
    DlcHeader *cur_perso = controller.list_perso;
    while (cur_perso != NULL) {
        if (cur_perso->id == id_perso) {
            DlcBody *cur_body = cur_perso->first_body;
            while (cur_body != NULL) {
                if (cur_body->id_question == id_question) {
                    return cur_body;
                }
                cur_body = cur_body->suiv_perso;
            }
            return NULL;
        }
        cur_perso = cur_perso->suiv_header;
    }
    return NULL;
}

/**
 * Retourne un header de perso si un seul perso correspond à toutes les questions jusqu'ici
 * @param controller
 * @param list_perso
 * @param list_question
 * @return DlcHeader or NULL
 */
DlcHeader *dlcControllerGetPersoProposition(DlcController controller, LcId *list_perso, LcIdEtat *list_question) {
    if(list_perso != NULL && list_perso->suiv == NULL){
        DlcHeader * perso_proposition = dlcControllerGetPersoById(controller, list_perso->id);
        if(perso_proposition != NULL){
            return perso_proposition;
        }
    }
    LcId *strict_list_perso = NULL;
    LcId *cur_perso = list_perso;
    while (cur_perso != NULL) {
        LcIdEtat *cur_question = list_question;
        char is_current_streak = 1;
        while (cur_question != NULL && is_current_streak == 1) {
            DlcBody *target = dlcControllerGetBodyByIds(controller, cur_perso->id, cur_question->id);
            if (target == NULL) {
                char err[256] = "";
                sprintf(err, "Réponse à la question %d introuvable pour %d, ceci n'est pas censé arrivé",
                        cur_question->id, cur_perso->id);
                perror(err);
                exit(-20);
            }
            // si pas erreur
            if (target->etat != cur_question->etat) {
                is_current_streak = 0;
            } else {
                cur_question = cur_question->suiv;
            }
        }
        if (cur_question == NULL) {
            LcId *new = malloc(sizeof(LcId));
            if(new == NULL){
                perror("Erreur d'allocation memoire\n");
                exit(-10);
            }
            init_file(new);
            new->id = cur_perso->id;
            insertionFinListe(&strict_list_perso, new);
        }
        cur_perso = cur_perso->suiv;
    }
    if(strict_list_perso != NULL){
        if(strict_list_perso->suiv == NULL){
            // une seule correspondance
            DlcHeader * perso_proposition = dlcControllerGetPersoById(controller, strict_list_perso->id);
            if(perso_proposition != NULL){
                suppressionTotId(&strict_list_perso);
                return perso_proposition;
            }
        }
    }
    suppressionTotId(&strict_list_perso);
    return NULL;
}