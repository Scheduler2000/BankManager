#ifndef __LIST__
#define __LIST__


typedef struct Date
{
	int day;
	int month;
	int year;
}t_date;

/* Représente un compte bancaire */
typedef struct Node
{
	char* owner;
	float balance;
	t_date* openingDate;
	struct Node* next;
	struct Node* previous;
}t_node;

typedef struct List
{
	t_node* first;
	t_node* last;
	int length;
}t_list;

t_list* InitializeBank(); /* Initialize une structure de controle t_list et renvoie son adresse. */
void PushBankAccount(t_list* list, char* owner, float balance, t_date* openingDate); /* Ajoute en dernière position de liste un nouveau compte bancaire. */
void RemoveBankAccount(t_list* list, char* owner); /* Supprime un compte en banque en fonction du nom du proprietaire qui fait office de clé primaire. */
void ModifyBankAccount(t_node* account, char* newOwner, float newBalance); /* Permet de modifier le proprietaire ou le solde d'un compte bancaire ou les deux. */
void DisplayBankAccounts(t_list* list); /* Affiche en sortie tous les comptes de la banque via le parcours de la liste chainée list. */
void DisplayBankAccount(t_node* node); /* Affiche un compte en banque (le maillon qui le représente). */
t_node* FetchBankAccount(t_list* list, char* owner); /* Recherche un compte en banque en fonction du nom proprietaire et renvoie son adresse mémoire ou NULL. */
/* Recherche tous les comptes de la banque selon un critère de recherche et renvoie une sous-liste les contenant tous. NB : Voir implémentation */
t_list* FetchBankAccounts(t_list* list, t_date* date, char criterion);
t_list* SortAscendingOrderByOwnerName(t_list* list); /* Trie par odre croissant les comptes bancaires selon le nom du proprietaire du compte.*/
t_list* SortDescendingOrderByOwnerName(t_list* list);/* Trie par odre décroissant les comptes bancaires selon le nom du proprietaire du compte.*/
t_list* SortAscendingOrderByBalance(t_list* list);  /* Trie par odre croissant les comptes en fonction de leur solde bancaire.*/
t_list* SortDescendingOrderByBalance(t_list* list); /* Trie par odre décroissant les comptes en fonction de leur solde bancaire.*/
t_node* CreateNode(char* owner, float balance, t_date* date); /* Créer un maillon dynamiquement et retourne son adresse. */

#endif
