#ifndef __STRING_EXTENSION__
#define __STRING_EXTENSION__
#include <string.h>
#include "../includes/list.h"

/* Supprime tous les espaces et saut de ligne ainsi les horizontal tab et retourne la chaine. */
char* ClearString(char *data);

/* Extrait un float selon une chaine de caractère de CompteBancaire.txt . */
float ConvertToFloat(char* data);

/* Formate le champ owner pour facilité l'ecriture et la lecture du fichier CompteBancaire.txt .*/
char* FormatAccountOwner(char* data);

/* Extrait le proprietaire sous forme d'une chaine formater "Prenom Nom" selon une chaine de caractère de CompteBancaire.txt . */
void GetAccountOwner(char* data, char** owner);

/* Extrait la date d'ouverture du compte(selon une chaine de caractère de CompteBancaire.txt) la stock dans une structure t_date et renvoie son adresse. */
t_date* GetAccountOpeningDate(char* data);

#endif
