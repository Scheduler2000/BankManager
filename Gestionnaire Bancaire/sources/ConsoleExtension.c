
#include <stdio.h>
#include <stdlib.h>
#include "../includes/ConsoleExtension.h"

void ClearConsole()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    printf("\033[H\033[J");
#endif
}

void ClearConsoleLine(int line, int column)
{
    int currentLine = GetCursorPosition('x');
    int currentColumn = GetCursorPosition('y');
    SetCursorPosition(line, column);
    printf("                                                                                                                          ");
    SetCursorPosition(currentLine, currentColumn);
}

void SetConsoleTextColor(int foreground)
{
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground);
#elif __linux__
    switch (foreground)
    {
    case 0:
        printf(BLACK);
        break;
    case 4:
        printf(RED);
        break;
    case 2:
        printf(GREEN);
        break;
    case 14:
        printf(YELLOW);
        break;
    case 3:
        printf(BLUE);
        break;
    case 5:
        printf(PURPLE);
        break;
    case 8:
        printf(GREY);
        break;
    case 15:
        printf(DEFAULT_COLOR);
        break;
    default:
        printf(DEFAULT_COLOR);
        break;
    }
#endif
}

void SetCursorPosition(int line, int column)
{
#ifdef _WIN32
    COORD position;
    position.X = line;
    position.Y = column;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
#elif __linux__
    printf("\033[%d;%dH", (line), (column));
#endif
}

int GetCursorPosition(char component)
{
#ifdef _WIN32
    int pos = 0;

    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenInfo);
    switch (component)
    {
    case 'x':
        return screenInfo.dwCursorPosition.X;
    case 'y':
        return screenInfo.dwCursorPosition.Y;
    }
#elif __linux__
    int x;
    int y;

    GetConsoleCursorPosition_linux(&y, &x);
    switch (component)
    {
    case 'x':
        return x;
    case 'y':
        return y;
        break;
    }
#endif
    return pos;
}

void GetConsoleCursorPosition_linux(int *y, int *x)
{
    printf("\033[6n");
    scanf("\033[%d;%dR", x, y);
}

void DisplayErrorMessage(char *message)
{
    SetConsoleTextColor(4);
    printf("[-] Error : %s\n", message);
    SetConsoleTextColor(15);
    exit(EXIT_FAILURE);
}

void DisplayBankMessage(char *message)
{
    SetConsoleTextColor(2);
    printf("[+] Bank : %s\n", message);
    SetConsoleTextColor(15);
}

void CleanConsole()
{

    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void DisplayBank()
{
#ifdef _WIN32
    system("mode con lines=30 cols=130");
#elif __linux__
    printf("\e[8;[50];[100];t");
#endif
    SetConsoleTextColor(2);
    SetCursorPosition(40, 0);
    printf("########::::::::'###:::::::'##::: ##::::'##:::'##:\n");
    SetCursorPosition(40, 1);
    printf("##.... ##::::::'## ##:::::: ###:: ##:::: ##::'##::\n");
    SetCursorPosition(40, 2);
    SetConsoleTextColor(15);
    printf("##:::: ##:::::'##:. ##::::: ####: ##:::: ##:'##:::\n");
    SetCursorPosition(40, 3);
    printf("########:::::'##:::. ##:::: ## ## ##:::: #####::::\n");
    SetCursorPosition(40, 4);
    printf("##.... ##:::: #########:::: ##. ####:::: ##. ##:::\n");
    SetCursorPosition(40, 5);
    SetConsoleTextColor(4);
    printf("##:::: ##:::: ##.... ##:::: ##:. ###:::: ##:. ##::\n");
    SetCursorPosition(40, 6);
    printf("########::::: ##:::: ##:::: ##::. ##:::: ##::. ##:\n");
    SetConsoleTextColor(15);
}
