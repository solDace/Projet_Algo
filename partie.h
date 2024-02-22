//
// Created by isen on 28/03/2022.
//

#ifndef AKINATOR_C_PARTIE_H
#define AKINATOR_C_PARTIE_H
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "double_linked_list.h"
#include "linked_list_id.h"
#include "linked_list_id_etat.h"
#include <time.h>

void partie(char *file_name);
void ask_player(char *buffer, int size, char* prompt);
LcIdEtat *askReponseQuestion(DlcHeader *question);
char prop_perso(char *buffer,DlcHeader* propositionPerso);
void flex_aleatoir();

#endif //AKINATOR_C_PARTIE_H
