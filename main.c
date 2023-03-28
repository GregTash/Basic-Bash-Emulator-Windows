#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define MAXLINE 10000

char line[MAXLINE];

void GetCommand()
{
    char c;
    int llength = 0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD savedAttributes;

    //Save console attributes.
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    savedAttributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("user@windows:~$ ");
    SetConsoleTextAttribute(hConsole, savedAttributes);

    //Read input from user and put a null terminator at the end of their input.
    while((c = getchar()) != '\n' && llength < MAXLINE)
    {
        line[llength++] = c;
    }
    line[llength] = '\0';

    //Check if the input
    if(!strcmp(line, "exit\n"))
        exit(0);

    system(line);

    GetCommand();
    return;
}

int main()
{
    SetConsoleTitle("Bash Emulator");
    GetCommand();
}