#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../includes/list.h"
#include "../includes/ConsoleExtension.h"
#include "../includes/stringExtension.h"
#include "../includes/file.h"

void SaveBankAccounts(t_list* list)
{
    FILE* file = fopen("CompteBancaire.txt","w+");
    int i = 0;
    char* owner = NULL;
    t_node* node;

    if(file != NULL && list != NULL && list->length != 0)
    {
        node = list->first;
        fputs("{\n\n",file);
        for(i = 0; i < list->length; i++)
        {
            owner = malloc(sizeof(char) * strlen(node->owner));
            strcpy(owner,node->owner);
            FormatAccountOwner(owner);
            fputs("\t{\n",file);
            fprintf(file, "\t\tOwner : %s\n",owner);
            fprintf(file, "\t\tBalance : %.2f $\n",node->balance);
            fprintf(file,"\t\tOpening date : %d.%d.%d\n",node->openingDate->day,node->openingDate->month,node->openingDate->year);
            fputs("\t}\n\n",file);
            node = node->next;
            free(owner);
        }
        fputs("}END",file);
        fclose(file);
        DisplayBankMessage("All the bank accounts have been saved.");
    }
    else
        DisplayBankMessage("save bank accounts failed...");
}

t_list* LoadBankAccounts(char* path)
{
    FILE* file = fopen(path,"r+");
    t_list* list = InitializeBank();
    t_date* openingDate = NULL;
    char input[100] = "\0", *data = NULL, *owner = NULL;
    float balance = 0.0;
    int dataLength = 0;

    if(file != NULL && list != NULL)
    {
        while(fgets(input,100,file) != NULL)
        {
            dataLength = strlen(ClearString(input) + 1);
            data = malloc(sizeof(char) * dataLength);
            strcpy(data,ClearString(input));
            if(data[0] == 'B') /* Si la premiere lettre de data* est un B alors nous sommes sur la ligne Balance : xxxx. */
                balance = ConvertToFloat(data);
            else if(data[0] == 'O' && data[1] == 'w') /* Même logique sauf que Opening date et Owner commence tout deux par O. */
                GetAccountOwner(data,&owner);
            else if(data[0] == 'O' && data[1] == 'p') /* On regarde ainsi la seconde lettre pour savoir sur quelle ligne nous sommes. */
               openingDate = GetAccountOpeningDate(data);
            else if(data[0] == '}' && data[1] != 'E') /* Ici nous devons ajouter l'ensemble des données a la liste + Reset les données utilisées. */
            {
                PushBankAccount(list,owner,balance,openingDate);
                memset(input,'\0',100);
                free(owner); // GetAccountOwner() alloue un espace memoire pour le champ owner => on peut le free.
            }


        }
        fclose(file);
        DisplayBankMessage("Loading accounts...");
        Sleep(1500);
        DisplayBankMessage("[Bank successfully loaded]\n\n");
        Sleep(1000);

    }

    return list;
}
