#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>

using namespace std;


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77



void Mouse(float XX, float YY){
    POINT(point);
    GetCursorPos(&point);
    YY = point.y;
    XX = point.x;
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}


void gotoxy(int x, int y){
    COORD point;
    point.X = x;
    point.Y = y;
    SetConsoleCursorPosition(GetStdHandle (STD_OUTPUT_HANDLE), point);
}

void Pressed(){
    if(kbhit())
        getch();
}



//Cores
const unsigned short WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const unsigned short DARK_GREEN = FOREGROUND_GREEN;
const unsigned short BRIGHT_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const unsigned short BRIGHT_RED = FOREGROUND_INTENSITY | FOREGROUND_RED;

void setConsoleColour(unsigned short colour)            //Colocar cores;
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    SetConsoleTextAttribute(hOut, colour);
}

void PT(){
    setlocale(LC_ALL, "Portuguese");
}

void Cls(){
    system("cls");
}

void Pause(){
    system("pause");
}

void Flush(){
    cout.flush();
}
