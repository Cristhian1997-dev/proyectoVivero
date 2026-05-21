#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>

#include "arbol_abb.h"
#include "consola.h"
#include "globales.h"

using namespace std;
NodoABB* crearNodoABB(Planta nuevaPlanta) {
	NodoABB* nuevo = new NodoABB;
	nuevo->dato = nuevaPlanta;
	nuevo->izquierda = NULL;
	nuevo->derecha = NULL;
	return nuevo;
}

bool insertarNodoABB(NodoABB*& raiz, Planta nuevaPlanta) {
	if (raiz == NULL) {
		raiz = crearNodoABB(nuevaPlanta);
		return true;
	}

	if (nuevaPlanta.id == raiz->dato.id) {
		return false; //No se permiten ID repetidos en el ABB
	}
	else if (nuevaPlanta.id < raiz->dato.id) {
		return insertarNodoABB(raiz->izquierda, nuevaPlanta);
	}
	else {
		return insertarNodoABB(raiz->derecha, nuevaPlanta);
	}
}

NodoABB* buscarNodoABB(NodoABB* raiz, int id) {
	if (raiz == NULL) {
		return NULL;
	}

	if (id == raiz->dato.id) {
		return raiz;
	}
	else if (id < raiz->dato.id) {
		return buscarNodoABB(raiz->izquierda, id);
	}
	else {
		return buscarNodoABB(raiz->derecha, id);
	}
}

void ingresarPlantaABB() {
	::system("cls");
	Planta nuevaPlanta;

	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- INSERTAR NODO EN ARBOL ABB ----" << endl;
	gotoxy(25, 5); cout << "Ingrese ID: ";
	while (!(cin >> nuevaPlanta.id)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros.";
		cin.clear();
		cin.ignore(1000, '\n');
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 5); cout << "Ingrese ID: ";
	}

	if (buscarNodoABB(raizABB, nuevaPlanta.id) != NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 7); cout << "ERROR: Ya existe un nodo con ese ID." << endl;
		return;
	}

	cin.ignore(1000, '\n');
	gotoxy(25, 6); cout << "Ingrese Nombre: "; getline(cin, nuevaPlanta.nombre);
	gotoxy(25, 7); cout << "Ingrese Tipo: "; getline(cin, nuevaPlanta.tipo);
	gotoxy(25, 8); cout << "Ingrese Color: "; getline(cin, nuevaPlanta.color);

	gotoxy(25, 9); cout << "Ingrese Precio: ";
	while (!(cin >> nuevaPlanta.precio)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros.";
		cin.clear();
		cin.ignore(1000, '\n');
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 9); cout << "Ingrese Precio: ";
	}

	gotoxy(25, 10); cout << "Ingrese Cantidad: ";
	while (!(cin >> nuevaPlanta.cantidad)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros.";
		cin.clear();
		cin.ignore(1000, '\n');
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 10); cout << "Ingrese Cantidad: ";
	}

	if (insertarNodoABB(raizABB, nuevaPlanta)) {
		SetConsoleTextAttribute(hConsole, 2);
		gotoxy(25, 12); cout << "Nodo insertado correctamente en el arbol ABB." << endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 12); cout << "No se pudo insertar el nodo." << endl;
	}
}

void imprimirPlantaABB(const Planta& planta, int& y) {
	gotoxy(25, y++); cout << "ID: " << planta.id;
	gotoxy(25, y++); cout << "Nombre: " << planta.nombre;
	gotoxy(25, y++); cout << "Tipo: " << planta.tipo;
	gotoxy(25, y++); cout << "Color: " << planta.color;
	gotoxy(25, y++); cout << "Precio: " << planta.precio;
	gotoxy(25, y++); cout << "Cantidad: " << planta.cantidad;
	gotoxy(25, y++); cout << "-----------------------------";
}

void buscarPlantaABB() {
	::system("cls");
	int idBuscado;

	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- BUSCAR NODO EN ARBOL ABB ----" << endl;
	if (raizABB == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "El arbol ABB esta vacio." << endl;
		return;
	}

	gotoxy(25, 5); cout << "Ingrese ID a buscar: ";
	while (!(cin >> idBuscado)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros.";
		cin.clear();
		cin.ignore(1000, '\n');
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 5); cout << "Ingrese ID a buscar: ";
	}

	NodoABB* encontrado = buscarNodoABB(raizABB, idBuscado);
	int y = 7;

	if (encontrado == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, y); cout << "No se encontro ningun nodo con ese ID." << endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 2);
		gotoxy(25, y++); cout << "Nodo encontrado:";
		imprimirPlantaABB(encontrado->dato, y);
	}
}

void preOrdenABB(NodoABB* raiz, int& y) {
	if (raiz != NULL) {
		imprimirPlantaABB(raiz->dato, y);
		preOrdenABB(raiz->izquierda, y);
		preOrdenABB(raiz->derecha, y);
	}
}

void inOrdenABB(NodoABB* raiz, int& y) {
	if (raiz != NULL) {
		inOrdenABB(raiz->izquierda, y);
		imprimirPlantaABB(raiz->dato, y);
		inOrdenABB(raiz->derecha, y);
	}
}

void posOrdenABB(NodoABB* raiz, int& y) {
	if (raiz != NULL) {
		posOrdenABB(raiz->izquierda, y);
		posOrdenABB(raiz->derecha, y);
		imprimirPlantaABB(raiz->dato, y);
	}
}

void recorrerArbolABB() {
	::system("cls");
	if (raizABB == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "El arbol ABB esta vacio." << endl;
		return;
	}

	int op;
	string opciones[] = {
		"1. Recorrido PreOrden",
		"2. Recorrido InOrden",
		"3. Recorrido PosOrden",
		"4. Mostrar los tres recorridos",
		"5. Regresar"
	};

	op = menuConFlecha(opciones, 5, "RECORRIDOS DEL ARBOL ABB", 3);
	::system("cls");
	int y = 4;
	SetConsoleTextAttribute(hConsole, 11);

	switch (op) {
	case 1:
		gotoxy(25, 2); cout << "RECORRIDO PREORDEN: RAIZ - IZQUIERDA - DERECHA";
		preOrdenABB(raizABB, y);
		break;
	case 2:
		gotoxy(25, 2); cout << "RECORRIDO INORDEN: IZQUIERDA - RAIZ - DERECHA";
		inOrdenABB(raizABB, y);
		break;
	case 3:
		gotoxy(25, 2); cout << "RECORRIDO POSORDEN: IZQUIERDA - DERECHA - RAIZ";
		posOrdenABB(raizABB, y);
		break;
	case 4:
		gotoxy(25, y++); cout << "PREORDEN:";
		preOrdenABB(raizABB, y);
		y++;
		gotoxy(25, y++); cout << "INORDEN:";
		inOrdenABB(raizABB, y);
		y++;
		gotoxy(25, y++); cout << "POSORDEN:";
		posOrdenABB(raizABB, y);
		break;
	case 5:
		break;
	}
}

NodoABB* encontrarMinimoABB(NodoABB* raiz) {
	while (raiz != NULL && raiz->izquierda != NULL) {
		raiz = raiz->izquierda;
	}
	return raiz;
}

bool eliminarNodoABB(NodoABB*& raiz, int id) {
	if (raiz == NULL) {
		return false;
	}

	if (id < raiz->dato.id) {
		return eliminarNodoABB(raiz->izquierda, id);
	}
	else if (id > raiz->dato.id) {
		return eliminarNodoABB(raiz->derecha, id);
	}
	else {
		NodoABB* aux = raiz;

		//Caso 1: nodo hoja, sin hijos
		if (raiz->izquierda == NULL && raiz->derecha == NULL) {
			raiz = NULL;
			delete aux;
			return true;
		}

		//Caso 2: nodo con solo hijo derecho
		if (raiz->izquierda == NULL) {
			raiz = raiz->derecha;
			delete aux;
			return true;
		}

		//Caso 2: nodo con solo hijo izquierdo
		if (raiz->derecha == NULL) {
			raiz = raiz->izquierda;
			delete aux;
			return true;
		}

		//Caso 3: nodo con dos hijos. Se reemplaza por el menor del subarbol derecho.
		NodoABB* sucesor = encontrarMinimoABB(raiz->derecha);
		raiz->dato = sucesor->dato;
		return eliminarNodoABB(raiz->derecha, sucesor->dato.id);
	}
}

void eliminarPlantaABB() {
	::system("cls");
	int idEliminar;

	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- ELIMINAR NODO DEL ARBOL ABB ----" << endl;
	if (raizABB == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "El arbol ABB esta vacio." << endl;
		return;
	}

	gotoxy(25, 5); cout << "Ingrese ID a eliminar: ";
	while (!(cin >> idEliminar)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros.";
		cin.clear();
		cin.ignore(1000, '\n');
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 5); cout << "Ingrese ID a eliminar: ";
	}

	if (eliminarNodoABB(raizABB, idEliminar)) {
		SetConsoleTextAttribute(hConsole, 2);
		gotoxy(25, 7); cout << "Nodo eliminado correctamente del arbol ABB." << endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 7); cout << "No se encontro un nodo con ese ID." << endl;
	}
}

void imprimirArbolVertical(NodoABB* raiz, int nivel, string rama, int& y) {
	if (raiz == NULL) {
		return;
	}

	string espacios = "";
	for (int i = 0; i < nivel; i++) {
		espacios += "    ";
	}

	gotoxy(10, y++);
	cout << espacios << rama << " -> ID: " << raiz->dato.id << " | " << raiz->dato.nombre;

	if (raiz->izquierda != NULL) {
		imprimirArbolVertical(raiz->izquierda, nivel + 1, "Izquierda", y);
	}
	if (raiz->derecha != NULL) {
		imprimirArbolVertical(raiz->derecha, nivel + 1, "Derecha", y);
	}
}

void mostrarArbolABBVertical() {
	::system("cls");
	SetConsoleTextAttribute(hConsole, 11);
	gotoxy(25, 2); cout << "ARBOL ABB EN FORMA VERTICAL";
	gotoxy(25, 3); cout << "No se muestra horizontal ni rotado; baja de raiz hacia hijos.";

	if (raizABB == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "El arbol ABB esta vacio." << endl;
		return;
	}

	int y = 6;
	imprimirArbolVertical(raizABB, 0, "Raiz", y);
	cout << "\n\n";
}

void liberarArbolABB(NodoABB*& raiz) {
	if (raiz != NULL) {
		liberarArbolABB(raiz->izquierda);
		liberarArbolABB(raiz->derecha);
		delete raiz;
		raiz = NULL;
	}
}
