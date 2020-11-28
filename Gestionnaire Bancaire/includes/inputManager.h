#ifndef __INPUT_MANAGER__
#define __INPUT_MANAGER__
#include "../includes/list.h"

typedef enum ResearchType
{
    precise,
    global
}ResearchType;

t_node* AskAccountInformation(); /* Crée un maillon selon les entrées du l'utilisateur. */
char* AskAccountHolder(); /* Demande à l'utilisateur de rentrer le nom du titulaire du compte et retourne son adresse. */
int AskModifyAccountHolder(); /* Demande à l'utilisateur s'il souhaite modifier le nom du proprietaire du compte retourne 1(oui) ou 0(non) */
int AskModifyBalanceAccount(); /* Demande à l'utilisateur s'il souhaite modifier le solde du compte retourne 1(oui) ou 0(non) */
float AskBalanceAccount(); /* Demande à l'utilisateur de rentrer le solde bancaire du compte et retourne sa valeur. */
ResearchType AskResearchType(); /* Demande à l'utilisateur s'il souhaite faire une recherche globale(plusieurs comptes) ou précise(1 compte).*/
char AskCriterionResearch(); /* Demande à l'utilisateur quel est le critere de recherche global et renvoie son code (voir FetchBankAccounts() -> list.c) */
t_date* AskResearchDate(char criterion); /* Demande la date de recherche et l'encapsule dans une structure t_date et retourn son adresse.*/
int AskSortType(); /* Demande à l'utilisateur sur quel champ il souhaite effectuer un tri et renvoie le code correspondant.*/

#endif
