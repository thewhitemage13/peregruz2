#include <iostream>
#include <ctime> 
#include <Windows.h> 
#include <conio.h> 
#include <string>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 

//1
void SetCursor(int x, int y, int color, string text)
{
    COORD position;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, color);
    cout << text;
    cout << (char)178;
}

void SetCursor(int y, int color, string text, int a)
{
    COORD position;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X = 0;
    position.Y = y;
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, color);
    cout << text;
    cout << (char)a;
}

void SetCursor(string text)
{
    COORD position;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X = 0;
    position.Y = 2;
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, 12);
    cout << " ";
    cout << (char)1;
}
//
void System(const char* str)
{
    system(str);
}

void Console()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100; // 1...100
    SetConsoleCursorInfo(h, &info);
}
//2
void Message(LPCSTR text, LPCSTR text2)
{
    MessageBoxA(0, text, text2, MB_OK);
}

void Message(HWND a, LPCSTR text, LPCSTR text2)
{
    MessageBoxA(a, text, text2, MB_OK);
}

void Message(HWND a, LPCSTR text, LPCSTR text2)
{
    MessageBoxA(a, text, text2, MB_OK);
}

void Message(HWND a, LPCSTR text, LPCSTR text2, UINT A)
{
    MessageBoxA(a, text, text2, A);
}

void Finish()
{
    system("cls");
    main();
    Sleep(INFINITE);
}