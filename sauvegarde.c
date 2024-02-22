//
// Created by samudec on 04/04/2022.
//

#include "sauvegarde.h"

void sauvegarde(DlcController controller, char*file_name)
{
    //check que le controller soit pas vide
    if (controller.list_question != NULL && controller.list_perso != NULL)
    {
        //creation d'un header pour recup les questions a enregistrer
        DlcHeader *temp = controller.list_question;
        FILE *fp;

        //check que le fichier soit bien ouvert
        if ((fp = fopen(file_name, "w")) != NULL)
        {
            //écriture des questions
            while (temp != NULL)
            {
                fprintf(fp, "%s\n", temp->content);
                temp = temp->suiv_header;
            }
            fprintf(fp, "\n");

            //passage aux perso et réponse
            temp = controller.list_perso;
            while (temp != NULL)
            {
                DlcBody *temp2 = temp->first_body;
                fprintf(fp, "%s", temp->content);
                fprintf(fp, "|");
                while (temp2 != NULL)
                {
                    fprintf(fp, "%c", temp2->etat);
                    temp2 = temp2->suiv_perso;
                }
                fprintf(fp, "\n");
                temp = temp->suiv_header;
            }
            printf("\nSauvegarde terminée !\n\n");
        }else
        {
            printf("erreur\n");
        }
        fclose(fp);
    }else
    {
        printf("erreur\n");
    }
}