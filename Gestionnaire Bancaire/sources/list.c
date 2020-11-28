#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../includes/list.h"
#include "../includes/ConsoleExtension.h"
#define TAILLE_MAX_BANK 15

t_list* InitializeBank()
{
    t_list* list = malloc(sizeof(t_list));

    if(list == NULL)
        DisplayErrorMessage("Malloc failed at InitializeBank() ...");
    list->first = NULL;
    list->last = NULL;
    list->length = 0;

    return list;
}

void PushBankAccount(t_list* list, char* owner, float balance, t_date* openingDate)
{
    t_node* node = CreateNode(owner,balance,openingDate);
    t_node* duplicate = FetchBankAccount(list,owner);

    if(list == NULL || node == NULL)
        DisplayErrorMessage("Malloc failed at PushBankAccount() ...");
    else if (duplicate != NULL)
        DisplayErrorMessage("You already have a bank account, you can not open two accounts at the same time ...");
    else if(list->length >= TAILLE_MAX_BANK)
    {
        DisplayBankMessage("The bank is overloaded, you can not add an other bank account !\n");
        return;
    }
    else if(list->length == 0)
    {
        list->first = node;
        list->last = node;
    }
    else
    {
        list->last->next = node;
        node->previous = list->last;
        list->last = node;
    }
    list->length++;
    DisplayBankMessage("Account added to bank.");
}

void RemoveBankAccount(t_list* list, char* owner)
{
    t_node* node = FetchBankAccount(list,owner);
    if(list == NULL)
        DisplayErrorMessage("You must initialize the bank with InitializeBank(), before using it.");
    else if(node == NULL)
    {
        DisplayBankMessage("The request to terminate the account failed.");
        return;
    }
    else
    {
        if(list->first == node)
        {
            node->next->previous = NULL;
            list->first = node->next;
        }
        else if(list->last == node)
        {
            node->previous->next = NULL;
            list->last = node->previous;
        }
        else
        {
            node->previous->next = node->next;
            node->next->previous = node->previous;
        }
    }
    free(node);
    list->length--;
    DisplayBankMessage("The request to terminate the account is done.");
}

void DisplayBankAccounts(t_list* list)
{
    int i;
    t_node* node = NULL;

    if(list == NULL || list->length == 0)
    {
        DisplayBankMessage("There are no bank accounts to display ...");
        return;
    }
    node = list->first;
    for(i = 0; i < list->length; i++)
    {
        DisplayBankAccount(node);
        node = node->next;
    }
    printf("\n\n");
    Sleep(500 * i);
}

void ModifyBankAccount(t_node* account, char* newOwner, float newBalance)
{
    if(account == NULL)
        return;
    account->balance = (account->balance != newBalance && newBalance != -1) ? newBalance: account->balance; /* si newBalance = -1(valeur arbitraire), on ne modifie pas le solde bancaire. */
    if(strcmp(newOwner,"\0") != 0) /* si la valeur  '\0' n'est pas passé en argument de la fonction pour newOwner, on modifie le champ account->owner. */
        strcpy(account->owner,newOwner);
    DisplayBankMessage("The request to modify bank account is done.");
}

void DisplayBankAccount(t_node* node)
{
    int dd = 0,mm =0,yy= 0;
    if(node == NULL)
    {
        DisplayBankMessage("Impossible to display the bank account, it does not exist.");
        return;
    }
    dd = node->openingDate->day;
    mm = node->openingDate->month;
    yy = node->openingDate->year;
    printf("\n\t Owner : %s | Balance : %.2f $ | Opening Date : %02d/%02d/%d.",node->owner,node->balance,dd,mm,yy);
}

t_node* FetchBankAccount(t_list* list, char* owner)
{
    t_node* node = NULL;
    int i = 0;

    if(list == NULL || list->length == 0)
        return NULL;
    node = list->first;
    for(i = 0; i < list->length; i++)
    {
        if(strcmp(node->owner,owner) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}

t_list* FetchBankAccounts(t_list* list, t_date* date, char criterion)
{
    t_list* accounts = InitializeBank();
    t_node* node = NULL;
    int i;

    if(list == NULL || list->length == 0)
        return NULL;
    node = list->first;
    switch(toupper(criterion))
    {
    case 'J': /* Recherche tous les comptes ayant le même jour d'ouverture. */
        for(i = 0; i < list->length; i++)
        {
            if(node->openingDate->day == date->day)
                PushBankAccount(accounts,node->owner,node->balance,node->openingDate);
            node = node->next;
        }
        break;
    case 'M': /* Recherche tous les comptes ayant le même mois d'ouverture. */
        for(i = 0; i < list->length; i++)
        {
            if(node->openingDate->month == date->month)
                PushBankAccount(accounts,node->owner,node->balance,node->openingDate);
            node = node->next;
        }
        break;
    case 'A': /* Recherche tous les comptes ayant la même année d'ouverture. */
        for(i = 0; i < list->length; i++)
        {
            if(node->openingDate->year == date->year)
                PushBankAccount(accounts,node->owner,node->balance,node->openingDate);
            node = node->next;
        }
        break;
    default:
        return NULL;
    }
    return accounts->length == 0 ? NULL : accounts; /* Si taille de 'accounts' = 0 alors retourner NULL sinon on retourne la sub liste. */
}

t_list* SortAscendingOrderByOwnerName(t_list* list)
{
    char* tmpOwner;
    float tmpBalance;
    t_date* tmpDate;
    t_node* pPrevious;
    t_node* pElement;
    int i;

    if(list != NULL && list->length != 0)
    {
        pPrevious = list->first;
        pElement = pPrevious->next;
        tmpDate = malloc(sizeof(t_date));
        for(i = 0; i < list->length; i++)
        {
            pElement = pPrevious->next;
            while(pElement != NULL)
            {
                if(strcmp(pPrevious->owner,pElement->owner) > 0)
                {
                    tmpOwner = malloc(sizeof(char) * strlen(pPrevious->owner));
                    strcpy(tmpOwner,pPrevious->owner);
                    pPrevious->owner = malloc(sizeof(char) * strlen(pElement->owner));
                    strcpy(pPrevious->owner,pElement->owner);
                    pElement->owner = malloc(sizeof(char)* strlen(tmpOwner));
                    strcpy(pElement->owner,tmpOwner);

                    tmpBalance = pElement->balance;
                    pElement->balance = pPrevious->balance;
                    pPrevious->balance = tmpBalance;

                    tmpDate = pPrevious->openingDate;
                    pPrevious->openingDate = pElement->openingDate;
                    pElement->openingDate = tmpDate;
                }
                pElement = pElement->next;
            }
            pPrevious = pPrevious->next;
        }
    }
    DisplayBankMessage("bank accounts sorted in ascending order according to the names of the owners.");
    return list;
}

t_list* SortDescendingOrderByOwnerName(t_list* list)
{
    t_list* ret = InitializeBank();
    t_node* pNode;
    int i = 0;

    if(list == NULL || list->length == 0)
        return ret;
    SortAscendingOrderByOwnerName(list);
    pNode = list->last;
    for(i = 0; i < list->length; i++)
    {
        PushBankAccount(ret,pNode->owner,pNode->balance,pNode->openingDate);
        pNode = pNode->previous;
    }
    DisplayBankMessage("bank accounts sorted in descending order according to the names of the owners.");
    return ret;
}

t_list* SortAscendingOrderByBalance(t_list* list)
{
    char* tmpOwner;
    float tmpBalance;
    t_date* tmpDate;
    t_node* pPrevious;
    t_node* pElement;
    int i;

    if(list != NULL && list->length != 0)
    {
        pPrevious = list->first;
        pElement = pPrevious->next;
        tmpDate = malloc(sizeof(t_date));
        for(i = 0; i < list->length; i++)
        {
            pElement = pPrevious->next;
            while(pElement != NULL)
            {
                if(pPrevious->balance > pElement->balance)
                {
                    tmpOwner = malloc(sizeof(char) * strlen(pPrevious->owner));
                    strcpy(tmpOwner,pPrevious->owner);
                    pPrevious->owner = malloc(sizeof(char) * strlen(pElement->owner));
                    strcpy(pPrevious->owner,pElement->owner);
                    pElement->owner = malloc(sizeof(char)* strlen(tmpOwner));
                    strcpy(pElement->owner,tmpOwner);

                    tmpBalance = pElement->balance;
                    pElement->balance = pPrevious->balance;
                    pPrevious->balance = tmpBalance;

                    tmpDate = pPrevious->openingDate;
                    pPrevious->openingDate = pElement->openingDate;
                    pElement->openingDate = tmpDate;
                }
                pElement = pElement->next;
            }
            pPrevious = pPrevious->next;
        }
    }
    DisplayBankMessage("bank accounts sorted in ascending order according to the balance.");
    return list;
}

t_list* SortDescendingOrderByBalance(t_list* list)
{
    t_list* ret = InitializeBank();
    t_node* pNode;
    int i = 0;

    if(list == NULL || list->length == 0)
        return ret;
    SortAscendingOrderByBalance(list);
    pNode = list->last;
    for(i = 0; i < list->length; i++)
    {
        PushBankAccount(ret,pNode->owner,pNode->balance,pNode->openingDate);
        pNode = pNode->previous;
    }
    DisplayBankMessage("bank accounts sorted in descending order according to the balance.");
    return ret;
}

t_node* CreateNode(char* owner, float balance, t_date* openingDate)
{
    t_node* node = malloc(sizeof(t_node));
    node->owner = malloc(sizeof(char) * (strlen(owner) + 1));
    node->openingDate = malloc(sizeof(t_date));

    if(node == NULL || node->owner == NULL || node->openingDate == NULL)
        return NULL;
    strcpy(node->owner,owner);
    node->balance = balance;
    node->openingDate = openingDate;
    node->next = NULL;
    node->previous = NULL;

    return node;
}
