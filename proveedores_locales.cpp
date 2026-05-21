#include <cstdlib>
#include <iostream>
#include <windows.h>

#include "consola.h"
#include "globales.h"
#include "proveedores_locales.h"

using namespace std;
NodoSimple* crearNodoProveedorLocal(Proveedor prov) {
	NodoSimple* nuevo = new NodoSimple;
	nuevo->dato = prov;
	nuevo->siguiente = NULL;
	return nuevo;
}
NodoSimple* buscarProveedorLocalPorId(NodoSimple* cabeza, int id) {
	NodoSimple* aux = cabeza;
	while (aux != NULL) {
		if (aux->dato.id == id) {
			return aux;
		}
		aux = aux->siguiente;
	}
	return NULL;
}
void ingresarProveedorLocalAlInicio(NodoSimple*& cabeza) {
	//Codigo para ingresar proveedores locales
	::system("cls");
	Proveedor nuevoProv;//Variable temporal para almacenar los datos del nuevo proveedor
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- INGRESAR UN NUEVO PROVEEDOR LOCAL ----" << endl;
	gotoxy(25, 5); cout << "Ingrese ID: ";
	while (!(cin >> nuevoProv.id)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permite numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 5); cout << "Ingresa ID: ";
	}

	//Verificar que no exista un proveedor con el mismo ID
	if (buscarProveedorLocalPorId(cabeza, nuevoProv.id) != NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 6); cout << "Ya existe un proveedor con ese ID." << endl;
		return;
	}

	cin.ignore();
	gotoxy(25, 6); cout << "Ingrese Nombre: ";
	getline(cin, nuevoProv.nombre);

	gotoxy(25, 7); cout << "Ingrese Tipo: ";
	getline(cin, nuevoProv.tipo);

	gotoxy(25, 8); cout << "Ingrese Telefono: ";
	while (!(cin >> nuevoProv.telefono)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 8); cout << "Ingrese Telefono: ";
	}

	cin.ignore();
	gotoxy(25, 9); cout << "Ingrese Contacto: ";
	getline(cin, nuevoProv.contacto);

	NodoSimple* nuevo = crearNodoProveedorLocal(nuevoProv);
	nuevo->siguiente = cabeza;
	cabeza = nuevo;
	gotoxy(25, 13); cout << "Proveedor local agregado correctamente." << endl;
}
void ingresarProveedorLocalAlFinal(NodoSimple*& cabeza) {
	//Codigo para ingresar proveedores locales al final de la lista
	::system("cls");
	Proveedor nuevoProv;//Variable temporal para almacenar los datos del nuevo proveedor
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- INGRESAR UN NUEVO PROVEEDOR LOCAL ----" << endl;
	gotoxy(25, 5); cout << "Ingrese ID: ";
	while (!(cin >> nuevoProv.id)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permite numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 5); cout << "Ingresa ID: ";
	}

	//Verificar que no exista un proveedor con el mismo ID
	if (buscarProveedorLocalPorId(cabeza, nuevoProv.id) != NULL) {
		gotoxy(25, 6); cout << "Ya existe un proveedor con ese ID." << endl;
		return;
	}

	cin.ignore();
	gotoxy(25, 6); cout << "Ingrese Nombre: "; getline(cin, nuevoProv.nombre);

	gotoxy(25, 7); cout << "Ingrese Tipo: "; getline(cin, nuevoProv.tipo);

	gotoxy(25, 8); cout << "Ingrese Telefono: ";
	while (!(cin >> nuevoProv.telefono)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 8); cout << "Ingrese Telefono: ";
	}

	cin.ignore();
	gotoxy(25, 9); cout << "Ingrese Contacto: "; getline(cin, nuevoProv.contacto);

	NodoSimple* nuevo = crearNodoProveedorLocal(nuevoProv);
	if (cabeza == NULL) {
		//Si la lista esta vacia, el nuevo nodo se convierte en la cabeza
		cabeza = nuevo;
	}
	else {
		//Recorremos la lista hasta el ultimo nodo
		NodoSimple* aux = cabeza;
		while (aux->siguiente != NULL) {
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
	}

	gotoxy(25, 9); cout << "Proveedor local agregado correctamente al final de la lista." << endl;
}
void buscarProveedorLocal(NodoSimple* cabeza) {
	//Codigo para buscar proveedores locales
	::system("cls");
	int idBuscado;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- BUSCAR PROVEEDOR LOCAL ----" << endl;
	gotoxy(25, 5); cout << "Ingrese el ID del proveedor local: ";
	cin >> idBuscado;
	NodoSimple* aux = buscarProveedorLocalPorId(cabeza, idBuscado);

	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 6); cout << "No se encontro el proveedor local." << endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 2);
		gotoxy(25, 6); cout << "\nProveedor local encontrado:" << endl;
		gotoxy(25, 7); cout << "ID: " << aux->dato.id << endl;
		gotoxy(25, 8); cout << "Nombre: " << aux->dato.nombre << endl;
		gotoxy(25, 9); cout << "Tipo: " << aux->dato.tipo << endl;
		gotoxy(25, 10); cout << "Telefono: " << aux->dato.telefono << endl;
		gotoxy(25, 11); cout << "Contacto: " << aux->dato.contacto << endl;
	}
}
void verProveedoresLocales(NodoSimple*& cabeza) {
	//Codigo para ver proveedores locales
	::system("cls");
	NodoSimple* aux = cabeza;
	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No hay proveedores locales registrados." << endl;
		return;
	}

	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 3); cout << "---- PROVEEDORES LOCALES ----" << endl;
	while (aux != NULL) {
		gotoxy(25, 5); cout << "ID: " << aux->dato.id << endl;
		gotoxy(25, 6); cout << "Nombre: " << aux->dato.nombre << endl;
		gotoxy(25, 7); cout << "Tipo: " << aux->dato.tipo << endl;
		gotoxy(25, 8); cout << "Telefono: " << aux->dato.telefono << endl;
		gotoxy(25, 9); cout << "Contacto: " << aux->dato.contacto << endl;
		gotoxy(25, 10); cout << "------------------------" << endl;
		aux = aux->siguiente;
	}
}
void modificarProveedorLocal(NodoSimple*& cabeza) {
	//Codigo para modificar proveedores locales
	::system("cls");
	int idBuscado;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- MODIFICAR PROVEEDOR LOCAL ----" << endl;
	gotoxy(25, 5); cout << "Ingrese el ID del proveedor local a modificar: ";
	cin >> idBuscado;
	NodoSimple* aux = buscarProveedorLocalPorId(cabeza, idBuscado);
	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 7); cout << "No se encontro el proveedor." << endl;
		return;
	}

	cin.ignore();
	gotoxy(25, 6); cout << "Nuevo nombre: ";
	getline(cin, aux->dato.nombre);
	gotoxy(25, 7); cout << "Nuevo tipo: ";
	getline(cin, aux->dato.tipo);
	gotoxy(25, 8); cout << "Nuevo telefono: ";
	while (!(cin >> aux->dato.telefono)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 8); cout << "Ingrese Telefono: ";
	}
	cin.ignore();
	gotoxy(25, 9); cout << "Nuevo contacto: ";
	getline(cin, aux->dato.contacto);

	gotoxy(25, 12); cout << "Proveedor local modificado correctamente." << endl;
}
void eliminarProveedorLocal(NodoSimple*& cabeza) {
	//Codigo para eliminar proveedores locales
	::system("cls");
	int idBuscado;
	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(25, 3); cout << "---- ELIMINAR PROVEEDOR LOCAL ----" << endl;
	gotoxy(25, 5); cout << "Ingrese el ID del proveedor local a eliminar: "; cin >> idBuscado;
	NodoSimple* aux = buscarProveedorLocalPorId(cabeza, idBuscado);
	if (aux == NULL) {
		gotoxy(25, 7); cout << "No se encontro el proveedor." << endl;
		return;
	}
	if (aux == cabeza) {//Si el nodo a eliminar es el primero de la lista
		cabeza = cabeza->siguiente;//Movemos la cabeza al siguiente nodo
	}
	else {
		NodoSimple* prev = cabeza;//Si el nodo a eliminar no es el primero, buscamos el nodo anterior a este
		while (prev->siguiente != aux) {
			prev = prev->siguiente;//Movemos el nodo anterior hasta que su siguiente sea el nodo a eliminar
		}
		prev->siguiente = aux->siguiente;
	}
	delete aux;
	gotoxy(25, 7); cout << "\nProveedor local eliminado correctamente." << endl;
}
void liberarListaSimple(NodoSimple*& cabeza) {
	::system("cls");
	//Codigo para liberar memoria de la lista simple
	while (cabeza != NULL) {
		NodoSimple* aux = cabeza;
		cabeza = cabeza->siguiente;
		delete aux;
	}
	gotoxy(25, 12); cout << "Memoria de la lista simple de proveedores locales liberada correctamente." << endl;
}

//Funciones para la lista de proveedores internacionales (lista doblemente enlazada)
