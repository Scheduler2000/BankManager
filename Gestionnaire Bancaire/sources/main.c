#include <stdio.h>
#include <stdlib.h>
#include "../includes/list.h"
#include "../includes/file.h"
#include "../includes/displayer.h"

int main(int argc, char const *argv[])
{
	t_list* list = LoadBankAccounts("CompteBancaire.txt");
    DisplayMenu(list);
	return 0;
}
