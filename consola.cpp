#include <cstdlib>
#include <iostream>
#include <windows.h>

#include "consola.h"

using namespace std;

void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void dibujo() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	SetConsoleOutputCP(CP_UTF8);// Codigo para que reconozca caracteres unicos

	cout <<
		"     â–ˆâ–ˆ                     â–ˆâ–ˆ    \n"
		"     â–ˆ  â–ˆâ–ˆâ–ˆ             â–ˆâ–ˆâ–ˆ  â–ˆ    \n"
		"     â–ˆ     â–ˆ           â–ˆ     â–ˆ    \n"
		"     â–ˆ     â–ˆ           â–ˆ     â–ˆ    \n"
		"     â–ˆâ–ˆâ–ˆ    â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆ     â–ˆâ–ˆâ–ˆ   \n"
		"     â–ˆâ–ˆâ–ˆ                    â–ˆâ–ˆâ–ˆ   \n"
		"    â–ˆ       â–ˆ          â–ˆ      â–ˆ   \n"
		"    â–ˆ       â–ˆ          â–ˆ      â–ˆ   \n"
		"    â–ˆ       â–ˆ          â–ˆ      â–ˆ   \n"
		"    â–ˆ            â–ˆâ–ˆ           â–ˆ   \n"
		"    â–ˆ    â–ˆâ–ˆâ–ˆâ–ˆ          â–ˆâ–ˆâ–ˆâ–ˆ   â–ˆ   \n"
		"    â–ˆ           â–ˆâ–ˆâ–ˆâ–ˆ          â–ˆ   \n"
		"    â–ˆ    â–ˆâ–ˆâ–ˆâ–ˆ          â–ˆâ–ˆâ–ˆâ–ˆ   â–ˆ   \n"
		"     â–ˆ                       â–ˆ    \n"
		"      â–ˆ                     â–ˆ     \n"
		"       â–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆâ–ˆ      \n"
		"                                  \n"
		"          PROGRAMACION 3          \n";


	::system("pause");
	::system("cls");

}
