#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../includes/stringExtension.h"

/* Ce fichier est exclusivement réalisé pour la lecture du fichier CompteBancire.txt -> LoadBankAccounts(); */

char * ClearString(char *data)
{
    int length = strlen(data);
    int j = 0;
    int i = 0;
    char* clean = malloc(sizeof(char) * length);
    memset(clean,'\0',length);

    for(i = 0; i < length; i++)
    {
        if(data[i] != ' ' && data[i] != '\n' && data[i] != 9) /* 9 = Horizontal TAB */
        {
            clean[j] = data[i];
            j++;
        }
    }

    return clean;
}


float ConvertToFloat(char* data)
{

    char* ret = strchr(data,':');
    int length = strlen(ret);
    int i = 0, j = 0;
    char* floatting = malloc(sizeof(char) * length);

    for(i = 0; i < length; i++)
    {
        if(ret[i] == '.' || isdigit(ret[i]))
        {
            floatting[j] = ret[i];
            j++;
        }
    }

    return strtof(floatting,NULL);
}

char* FormatAccountOwner(char* data)
{
    int i = 0;
    for(i = 0; i < strlen(data); i ++)
        if(data[i] == ' ')
            data[i] = '_'; /* On remplace l'espace par le _ pour facilité la lecture et le formatage de owner (GetAccountOwner(char* d)). */

    return data;
}

void GetAccountOwner(char* data, char** owner)
{
    char* ret = strchr(data,':');
    int length = strlen(ret);
    int i = 0;
    *owner = malloc(sizeof(char) * length);
    for(i = 0; i < length; i++)
        (*(owner))[i] = (ret[i+1] == '_' ) ? ' ' : ret[i+1]; // On remplace le '_' par un ' ' pour une meilleur lisibilité de Owner.
}

/* lit une date du format : dd.mm.yy */
t_date* GetAccountOpeningDate(char* data)
{
    t_date* date = malloc(sizeof(t_date));
    char* dstring = malloc(sizeof(char) * 9); /* dd.mm.yy + '\0' = 9*/
    char* ptr1 = NULL;
    char* ptr2 = NULL;
    int i = 0, j = 0;

    if(date == NULL)
        return NULL;

    for(i = 0; i < strlen(data); i++)
        if(data[i] == '.' || isdigit(data[i]))
        {
            dstring[j] = data[i];
            j++;
        }
    date->day = strtol(dstring,&ptr1,10);
    ptr1[0] = ' ';
    date->month = strtol(ptr1,&ptr2,10);
    ptr2[0] = ' ';
    date->year = strtol(ptr2,NULL,10);

    return date;
}
