#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../includes/inputManager.h"
#include "../includes/stringExtension.h"
#include "../includes/ConsoleExtension.h"

t_node* AskAccountInformation()
{
    char* owner;
    float balance = 0.0;
    char date[10] = "\0";
    t_date* openingDate;

    owner = AskAccountHolder();
    balance = AskBalanceAccount();
    printf("\nDate d'ouverture du compte (jj.mm.aa) : ");
    fgets(date,9,stdin);
    CleanConsole();
    openingDate = GetAccountOpeningDate(date);

    return (t_node*)CreateNode(owner, balance, openingDate);
}

char* AskAccountHolder()
{
    char owner[30] = "\0";
    char* ret;
    int i = 0;

    printf("\nNom du proprietaire : ");
    fgets(owner,30,stdin);
    CleanConsole();
    ret = malloc(sizeof(char) * (strlen(owner) -1)); // On supprime le '\n' donc un espace en moins.
    if(ret != NULL)
        for(i = 0; i < strlen(owner) - 1; i++)
            ret[i] = owner[i];
    ret[i] = '\0';

    return ret;
}

float AskBalanceAccount()
{
    float balance = 0.0;

    printf("\nSolde bancaire : ");
    scanf("%f",&balance);
    CleanConsole();

    return balance;
}

int AskModifyAccountHolder()
{
    char choice;

    printf("\nSouhaitez-vous modifier le nom du proprietaire du compte ? [O/N] : ");
    choice = getc(stdin);
    CleanConsole();

    return toupper(choice) == 'O' ? 1 : 0;
}

int AskModifyBalanceAccount()
{
    char choice;

    printf("\nSouhaitez-vous modifier le solde bancaire du compte ? [O/N] : " );
    choice = getc(stdin);
    CleanConsole();

    return toupper(choice) == 'O' ? 1 : 0;
}

ResearchType AskResearchType()
{

    char choice;

    printf("\nSouhaitez-vous effectuer une recherche precise ou globale ? [P/G] : " );
    choice = getc(stdin);
    CleanConsole();

    return choice == 'P' ? precise : choice == 'G' ? global : 'i';
}

char AskCriterionResearch()
{
    char criterion;

    printf("Effectuer une recherche sur compte bancaire par jours/mois/annee [J/M/A] : ");
    criterion = getc(stdin);
    CleanConsole();

    return criterion;
}

t_date* AskResearchDate(char criterion)
{
    t_date* date = malloc(sizeof(t_date));

    if(date != NULL)
    {
        date->day = 0;
        date->month = 0;
        date->year = 0;
        switch(toupper(criterion))
        {
        case 'J': /* Recherche par jour */
            printf("\nJour de la recherche : ");
            scanf("%d",&(date->day));
            break;
        case 'M': // Mois
            printf("\nMois de la recherche : ");
            scanf("%d",&(date->month));
            break;
        case 'A': // Année
            printf("\nAnnee de la recherche : ");
            scanf("%d",&(date->year));
            break;
        default:
            printf("\n[Recherche par defaut] Jour de la recherche : ");
            scanf("%d",&(date->day));
            break;
        }
        ClearConsole();
        return date;
    }
    else
        printf("ERROR MALLOC AT << AskResearhDate >> ...");
    return NULL;
}

int AskSortType()
{
    char sortOrder;
    char informationOrder;

    printf("\nEffectuer un tri Croissant/Decroissant [C/D] : ");
    sortOrder = getchar();
    CleanConsole();
    printf("\nEffectuer un tri par rapport au nom du proprietaire des comptes ou aux soldes des comptes [N/S] : ");
    informationOrder = getchar();
    CleanConsole();
    if(sortOrder == 'C' && informationOrder == 'N')
        return 1; // trie croissant en fonction du champ owner.
    else if(sortOrder == 'C' && informationOrder == 'S')
        return 2; // trie croissant en fonction du champ balance.
    else if(sortOrder == 'D' && informationOrder == 'N')
        return 3; // trie décroissant en fonction du champ owner.
    else if (sortOrder == 'D' && informationOrder == 'S')
        return 4; // trie décroissant en fonction du champ balance.
    return 1;
}
