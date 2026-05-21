#include <cstdlib>
#include <iostream>
#include <windows.h>

#include "consola.h"
#include "globales.h"
#include "modelos.h"
#include "proveedores_circular.h"

using namespace std;
void ingresarProveedor() {
	::system("cls");
	NodoProveedor* nuevo = new NodoProveedor;

	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "INGRESAR UN NUEVO PROVEEDOR";
	gotoxy(25, 5); cout << "Ingresar ID: "; cin >> nuevo->dato.id;
	cin.ignore();
	gotoxy(25, 6); cout << "Ingrese Nombre: "; getline(cin, nuevo->dato.nombre);
	gotoxy(25, 7); cout << "Ingrese Empresa: "; getline(cin, nuevo->dato.empresa);
	gotoxy(25, 8); cout << "Ingrese Telefono: "; cin >> nuevo->dato.telefono;

	if (inicioCircular == NULL) {
		inicioCircular = nuevo;
		finCircular = nuevo;
		nuevo->siguiente = inicioCircular; //Se apunta a si mismo
	}
	else {
		finCircular->siguiente = nuevo;
		nuevo->siguiente = inicioCircular; //Cierra el cÃ­rculo
		finCircular = nuevo;
	}

	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 10); cout << "Proveedor agregado correctamente.";
	cout << "\n\n";
}
void verProveedores() {
	::system("cls");
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 2); cout << "LISTA DE PROVEEDORES";

	if (inicioCircular == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "No hay proveedores registrados.";
		cout << "\n\n";
		return;
	}

	NodoProveedor* aux = inicioCircular;
	int y = 5;
	do {
		SetConsoleTextAttribute(hConsole, 11);
		gotoxy(25, y++); cout << "ID: " << aux->dato.id;
		gotoxy(25, y++); cout << "Nombre: " << aux->dato.nombre;
		gotoxy(25, y++); cout << "Empresa: " << aux->dato.empresa;
		gotoxy(25, y++); cout << "Telefono: " << aux->dato.telefono;
		gotoxy(25, y++); cout << "-----------------------------";
		aux = aux->siguiente;
	} while (aux != inicioCircular); //Se detiene uando da la vuelta
	cout << "\n";
}
void buscarProveedor() {
	::system("cls");
	int idBuscado;
	bool encontrado = false;
	gotoxy(25, 3); cout << "BUSCAR PROVEEDOR";
	gotoxy(25, 5); cout << "Ingrese ID: "; cin >> idBuscado;

	if (inicioCircular != NULL) {
		NodoProveedor* aux = inicioCircular;
		int y = 7;
		do {
			if (aux->dato.id == idBuscado) {
				SetConsoleTextAttribute(hConsole, 2);
				gotoxy(25, y++); cout << "Proveedor Encontrado: ";
				gotoxy(25, y++); cout << "Nombre: " << aux->dato.nombre;
				gotoxy(25, y++); cout << "Empresa: " << aux->dato.empresa;
				gotoxy(25, y++); cout << "Telefono: " << aux->dato.telefono;
				encontrado = true;
				break;
			}
			aux = aux->siguiente;
		} while (aux != inicioCircular);
	}
	if (!encontrado) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 7); cout << "No se encontro el proveedor.";
	}
	cout << "\n\n";
}
void eliminarProveedor() {
	::system("cls");
	gotoxy(25, 3); cout << "ELIMINAR PROVEEDOR";

	if (inicioCircular == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No hay proveedores para eliminar.";
		cout << "\n\n";
		return;
	}

	int idBuscado;
	gotoxy(25, 5); cout << "Ingrese ID a eliminar: "; cin >> idBuscado;

	NodoProveedor* actual = inicioCircular;
	NodoProveedor* anterior = finCircular;
	bool encontrado = false;

	do {
		if (actual->dato.id == idBuscado) {
			if (actual == inicioCircular && actual == finCircular) {
				inicioCircular = NULL;
				finCircular = NULL;
			}
			else if (actual == inicioCircular) {
				inicioCircular = inicioCircular->siguiente;
				finCircular->siguiente = inicioCircular;
			}
			else if (actual == finCircular) {
				finCircular = anterior;
				finCircular->siguiente = inicioCircular;
			}
			else {
				anterior->siguiente = actual->siguiente;
			}
			delete actual;
			encontrado = true;
			SetConsoleTextAttribute(hConsole, 2);
			gotoxy(25, 7); cout << "Proveedor eliminado.";
			break;
		}
		anterior = actual;
		actual = actual->siguiente;
	} while (actual != inicioCircular);

	if (!encontrado) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 7); cout << "Proveedor no encontrado.";
	}
	cout << "\n\n";
}


void liberarListaCircular() {
	if (inicioCircular != NULL) {
		NodoProveedor* aux = inicioCircular;
		NodoProveedor* sig;
		do {
			sig = aux->siguiente;
			delete aux;
			aux = sig;
		} while (aux != inicioCircular);
		inicioCircular = NULL;
		finCircular = NULL;
	}
}
