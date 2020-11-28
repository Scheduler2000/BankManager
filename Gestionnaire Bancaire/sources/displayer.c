#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/displayer.h"
#include "../includes/inputManager.h"

void DisplayMenu(t_list* bank)
{
    char choice = '\0';
    char criterion = '\0';
    char owner[30] = "\0";
    float balance = 0.0;
    t_node* node = NULL;
    t_list* subAccounts = NULL;

    while(1)
    {
        DisplayBank();
        strcpy(owner,"\0");
        DisplayFeatures();
        choice = getchar();
        CleanConsole();
        switch(choice)
        {
        case '1':
            node = AskAccountInformation();
            PushBankAccount(bank,node->owner, node->balance, node->openingDate);
            break;

        case '2':
            strcpy(owner,AskAccountHolder());
            RemoveBankAccount(bank, owner);
            break;

        case '3':
            strcpy(owner,AskAccountHolder());
            node = FetchBankAccount(bank,owner);
            if(node == NULL)
            {
                DisplayBankMessage("Bank account does not exist.");
                continue;
            }
            /* On modifie le nom du propriétaire. ? */
            if(AskModifyAccountHolder() == 1)
            {
                strcpy(owner,AskAccountHolder());   /* Nouveau nom. */
            }
            else strcpy(owner,"\0"); /* Si owner = NULL alors on modifie pas le champ owner du maillon, voir ModifyBankAccount(); */
            if(AskModifyBalanceAccount() == 1)
            {
                balance = AskBalanceAccount();
            }
            else balance = -1;
            ModifyBankAccount(node,owner,balance);
            break;

        case '4':
            switch(AskResearchType())
            {
            case precise :
                strcpy(owner,AskAccountHolder());
                node = FetchBankAccount(bank,owner);
                if(node == NULL) continue;
                DisplayBankAccount(node);
                break;
            case global:
                criterion = AskCriterionResearch();
                subAccounts = FetchBankAccounts(bank,AskResearchDate(criterion),criterion);
                DisplayBankAccounts(subAccounts);
                free(subAccounts);
                break;
            default: printf("Type de recherche inconnu ..."); break;
            }
            break;

        case '5':
            switch(AskSortType())
            {
            case 1: bank = SortAscendingOrderByOwnerName(bank); break;
            case 2: bank = SortAscendingOrderByOwnerName(bank); break;
            case 3: bank = SortDescendingOrderByOwnerName(bank); break;
            case 4: bank = SortDescendingOrderByBalance(bank); break;
            }
            break;

        case '6': DisplayBankAccounts(bank); break;
        case '7': SaveBankAccounts(bank); break;
        case '8': exit(EXIT_SUCCESS); break;
        default: ClearConsole(); continue;
        }
        Sleep(2500);
    }
}

static void DisplayFeatures()
{
    printf("\n\n\n");
    printf("Menu :\n\n");
    printf("\t1. Ajouter un nouveau compte bancaire.\n");
    printf("\t2. Supprimer un compte bancaire.\n");
    printf("\t3. Modifier un compte compte bancaire.\n");
    printf("\t4. Effectuer une recherche en banque.\n");
    printf("\t5. Trier les comptes bancaires.\n");
    printf("\t6. Afficher les comptes en banque.\n");
    printf("\t7. Sauvegarder la banque.\n");
    printf("\t8. Sortir du gestionnaire de compte bancaire.\n\nChoix : ");
}
