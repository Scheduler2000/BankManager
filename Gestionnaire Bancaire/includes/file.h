#ifndef __FILE__
#define __FILE__

void SaveBankAccounts(t_list* list); /* Sauvegarde de la liste chainée list représentant des fiches bancaires. */
t_list* LoadBankAccounts(char* path); /* Crée une liste chainée à partir des données lu dans 'path' et retourne son adresse. */
#endif
