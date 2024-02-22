//
// Created by isen on 28/03/2022.
//

#include "partie.h"
#include "chargement.h"
#include "sauvegarde.h"

void partie(char *file_name) {
    char fin = 0;
    char buffer[256];
    int checkPerso = 0;
    int checkquestion = 0;
    LcId *lcperso = NULL;
    LcIdEtat *lcquestion = NULL;
    DlcController controller = dlcControllerInit();
    chargement(&controller, file_name);
    //dlcPrint(controller);//affiche
    dlcControllerGetPerso(controller, &lcperso);
    printf("Pensez a un perso\n");
    ask_player(buffer, 256, "Ecrivez 'pret' quand vous l'etes\n");
    if (strcmp(buffer, "pret") == 0) {
        while (fin == 0) {
            DlcHeader *nextquestion = getNextQuestion(controller, lcquestion);
            if (nextquestion == NULL || lcperso==NULL) {
                //demande d'un perso
                printf("Je n'est pas trouvé ton personnage, quel été-t-il ?\n");
                DlcHeader *new_perso = dlcHeaderInit();
                ask_player(buffer, 256, "Entrer le nom d'un personnage : ");
                strcpy(new_perso->content, buffer);
                DlcHeader *cur_perso = controller.list_perso;
                while (cur_perso != NULL) {
                    if (strcmp(new_perso->content, cur_perso->content) == 0) {
                        //printf("perso deja dans la liste\n");

                        fill_respsonse(cur_perso, lcquestion);
                        checkPerso = 1;
                    }
                    cur_perso = cur_perso->suiv_header;
                }
                if (checkPerso == 0) {
                    // Si le perso n'est pas déjà dans la liste -> demande question
                    dlcControllerAddPerso(&controller, new_perso);
                    DlcHeader *new_question = dlcHeaderInit();
                    do {
                        ask_player(buffer, 256, "Entrer une question qui défini le perso : ");
                        strcpy(new_question->content, buffer);
                        DlcHeader *cur_question = controller.list_question;
                        while (cur_question != NULL) {
                            if (strcmp(new_question->content, cur_question->content) == 0) {
                                printf("Question deja dans la liste\n");
                                checkquestion = 1;
                            }
                            cur_question = cur_question->suiv_header;
                        }
                    } while (checkquestion == 1);
                    dlcControllerAddQuestion(&controller, new_question);
                    //demande de la réponse à la question pour le personnage donné
                    printf("Quelle est la réponse à cette question pour ton perso ?");
                    LcIdEtat *reponse = askReponseQuestion(new_question);
                    insertionFinListeEtat(&lcquestion, reponse);
                    fill_respsonse(new_perso, lcquestion);

                    checkquestion = 0;
                }
                checkPerso = 0;
                fin = 1;
            } else {
                printf("%s\n", nextquestion->content);
                LcIdEtat *reponse = askReponseQuestion(nextquestion);
                insertionFinListeEtat(&lcquestion, reponse);
                eliminatePerso(controller, &lcperso, reponse);
                DlcHeader *propositionPerso = dlcControllerGetPersoProposition(controller, lcperso, lcquestion);
                if (propositionPerso != NULL) {
                    fin = prop_perso(buffer, propositionPerso);
                    if (fin == 0) {
                        // c'était pas le bon perso
                        suppressionBonnePlace(&lcperso, propositionPerso->id);
                    }else{
                        //C'était le bon perso
                        fill_respsonse(propositionPerso,lcquestion);
                    }
                }
            }
        }
        //post partie
        suppressionTotId(&lcperso);
        suppressionTot(&lcquestion);
        sauvegarde(controller, file_name);
        dlcControlerFreeMemory(&controller);
    }
}

void ask_player(char *buffer, int size, char *prompt) {
    memset(buffer, 0, size);
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

LcIdEtat *askReponseQuestion(DlcHeader *question) {
    LcIdEtat *reponse = malloc(sizeof(LcIdEtat));
    if (reponse == NULL) {
        perror("Erreur d'allocation memoire\n");
        exit(-10);
    }
    init_fileEtat(reponse);
    reponse->id = question->id;
    char checkWhile = 0;
    char buffer[256] = "";
    while (checkWhile != 1) {
        ask_player(buffer, 256, "");
        if (strcmp(buffer, "y") == 0 || strcmp(buffer, "Y") == 0) {
            reponse->etat = 'y';
            checkWhile = 1;
        } else if (strcmp(buffer, "n") == 0 || strcmp(buffer, "N") == 0) {
            reponse->etat = 'n';
            checkWhile = 1;
        } else {
            printf("Répondez par n ou y\n");
        }
    }
    return reponse;
}

char prop_perso(char *buffer, DlcHeader *propositionPerso) {
    int checkWhile = 0;

    printf("Je pense que ton perso est : %s\n", propositionPerso->content);
    //fgets(buffer,256,stdin);
    while (checkWhile != 1) {
        //scanf("%s", buffer);
        ask_player(buffer, 256, "");
        if (strcmp(buffer, "y") == 0 || strcmp(buffer, "Y") == 0) {
            flex_aleatoir();
            checkWhile = 1;
            return 1;
        } else if (strcmp(buffer, "n") == 0 || strcmp(buffer, "N") == 0) {
            checkWhile = 1;
            return 0;
        } else {
            printf("Répondez par n ou y\n");
        }
        checkWhile = 0;
    }
}

void flex_aleatoir() {
    srand(time(NULL));
    int aleat = rand() % 5;
    switch (aleat) {
        case 0: {
            printf("Je suis un boss!\n");
            break;
        }
        case 1: {
            printf("Tema la taille du cerveau\n");
            break;
        }
        case 2: {
            printf("N'est pas géni qui veut\n");
            break;
        }
        case 3: {
            printf("Maintenent tu as le droit de me vénérer\n");
            break;
        }
        case 4: {
            printf("Appel moi dieu en fait !\n");
            break;
        }

    }
}
