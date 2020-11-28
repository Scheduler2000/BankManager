/* [Fichier Bonus] : Ce fichier provient de mon github : https://github.com/Kratoc/InternetRelayChat */
#ifndef __CONSOLE_EXTENSION__
#define __CONSOLE_EXTENSION__

#ifdef _WIN32
	#include <windows.h>

#elif __linux__

	#include <termios.h>
	#include <unistd.h>
	#define BLACK    "\033[0;30m"
	#define RED      "\033[0;31m"
	#define GREEN    "\033[0;32m"
	#define YELLOW   "\033[0;33m"
	#define BLUE     "\033[0;34m"
	#define PURPLE   "\033[0;35m"
	#define GREY     "\033[0;37m"
	#define DEFAULT_COLOR "\033[0;m"
	#define Sleep(s) sleep(s)
#endif

void DisplayErrorMessage(char * message);
void DisplayBankMessage(char *message);
void SetCursorPosition(int line, int column);
int GetCursorPosition(char component);
 void GetConsoleCursorPosition_linux(int *y, int *x);
void ClearConsole();
void ClearConsoleLine(int line, int column);
void SetConsoleTextColor(int foreground);
void DisplayBank();
/* Rajout :  */
void CleanConsole(); // Nettoie le buffer de la console pour faciliter la saisie clavier.

#endif

/*
Windows :
0 : Noir
1 : Bleu foncé
2 : Vert foncé
3 : Turquoise
4 : Rouge foncé
5 : Violet
6 : Vert caca d'oie
7 : Gris clair
8 : Gris foncé
9 : Bleu fluo
10 : Vert fluo
11 : Turquoise
12 : Rouge fluo
13 : Violet 2
14 : Jaune
15 : Blanc
*/
