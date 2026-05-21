#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>

#include "arbol_abb.h"
#include "cola_clientes.h"
#include "consola.h"
#include "globales.h"
#include "login.h"
#include "menu.h"
#include "pila_plantas.h"
#include "proveedores_circular.h"

using namespace std;
int main() {
	dibujo();
	string nombre;
	string contra;
	SetConsoleTextAttribute(hConsole, 3);
	gotoxy(45, 5); cout << "Bienvenidos a RAICES VERDES GT." << endl;
	gotoxy(47, 7); cout << "Ingrese su usuario: ";	cin >> nombre;
	gotoxy(47, 8); cout << "Ingrese su contrasena: "; cin >> contra;

	if (login(nombre, contra)) {
		menuPrincipal();
	}
	else {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(43, 10); cout << "Los datos ingresados son incorrectos." << endl;
		cout << "\n\n";
	}

	liberarPila();
	liberarCola();
	liberarListaCircular();
	liberarArbolABB(raizABB);

	system("pause");
	return 0;
}
