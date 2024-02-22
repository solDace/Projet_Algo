#include "chargement.h"

void chargement(DlcController *controller, char*file_name)
{
    FILE *fichier = fopen(file_name, "r");
    if(fichier==NULL) return;
    char memo[HEADER_MAX_STRING_SIZE];
    char nom[HEADER_MAX_STRING_SIZE];
    char reponse;
    int temp = 0;

    while (fgets(memo, sizeof(memo), fichier))
    {
        DlcHeader *header_question = dlcHeaderInit();
        DlcHeader *header_perso = dlcHeaderInit();


        //chargement des questions
        if (temp == 0)
        {
            //condition de sortie des questions
            if (strcmp(memo, "\n") == 0)
            {
                temp = 1;
            }else
            {
                //retire le '\n' en fin de ligne
                memo[strcspn(memo, "\n")] = 0;

                //ajout de la question question
                strcpy(header_question->content, memo);
                header_question->suiv_header = NULL;
                dlcControllerAddQuestion(controller, header_question);
            }
        }
        //chargement des personnages et réponses
        else
        {
            //pour derouler la ligne charactère par charactère
            int i=0, id=1;
            memset(nom, '\0', HEADER_MAX_STRING_SIZE);

            //recupération de la partie nom
            while (memo[i] != '|')
            {
                nom[i] = memo[i];
                i = i + 1;
            }
            //ajout du personnage
            strcpy(header_perso->content, nom);
            header_perso->suiv_header = NULL;
            dlcControllerAddPerso(controller, header_perso);

            //saut du charactère '|'
            i=i+1;
            LcIdEtat *states = NULL;
            //ajout des réponses dans une liste LcIdEtat
            while (memo[i] != '\n')
            {
                reponse = memo[i]; //y,n,u
                LcIdEtat *tmp = malloc(sizeof(LcIdEtat));
                init_fileEtat(tmp);
                tmp->id=id;
                tmp->etat=reponse;
                insertionFinListeEtat(&states,tmp);

                id= id + 1;
                i = i + 1;
            }
            //ajout de la liste dans le body (une ligne correspondant au personnage ajouté au dessus
            fill_respsonse(header_perso, states);
        }
    }
    printf("chargement terminé\n");
    fclose(fichier);
}

