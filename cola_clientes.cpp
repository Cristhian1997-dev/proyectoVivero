#include <cstdlib>
#include <iostream>
#include <windows.h>

#include "cola_clientes.h"
#include "consola.h"
#include "globales.h"

using namespace std;
NodoCliente* buscarClientePorId(int id) {
	NodoCliente* aux = cola.frente;

	while (aux != NULL) {
		if (aux->dato.id == id) {
			return aux;
		}
		aux = aux->siguiente;
	}

	return NULL;
}
void ingresarCliente() {
	//Aqui va el cÃ³digo de ingresar colas
	::system("cls");
	NodoCliente* nuevo = new NodoCliente;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- INGRESAR UN NUEVO CLIENTE ----" << endl;
	gotoxy(25, 5); cout << "Ingrese ID: ";
	while (!(cin >> nuevo->dato.id)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permite numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 5); cout << "Ingresa ID: ";
	}

	//Verificar que no exista un cliente con el mismo ID
	if (buscarClientePorId(nuevo->dato.id) != NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 8); cout << "Ya existe un cliente con ese ID." << endl;
		delete nuevo;
		return;
	}

	cin.ignore();
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 6); cout << "Ingrese Nombre: ";	getline(cin, nuevo->dato.nombre);
	gotoxy(25, 7); cout << "Ingrese Direccion: "; getline(cin, nuevo->dato.direccion);
	gotoxy(25, 8); cout << "Ingrese Telefono: ";
	while (!(cin >> nuevo->dato.telefono)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 8); cout << "Ingrese Telefono: ";
	}
	nuevo->siguiente = NULL;

	if (cola.frente == NULL) {
		cola.frente = nuevo;
		cola.fincola = nuevo;
	}
	else {
		cola.fincola->siguiente = nuevo;
		cola.fincola = nuevo;
	}
	cola.cantidad++;
	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 9); cout << "Cliente agregado correctamente." << endl;
}
void verClientes() {
	::system("cls");
	NodoCliente* aux = cola.frente;

	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- LISTA DE CLIENTES ----" << endl;
	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No hay clientes registrados." << endl;
		return;
	}

	while (aux != NULL) {
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 4); cout << "\nID: " << aux->dato.id << endl;
		gotoxy(25, 5); cout << "Nombre: " << aux->dato.nombre << endl;
		gotoxy(25, 6); cout << "Direccion: " << aux->dato.direccion << endl;
		gotoxy(25, 7); cout << "Telefono: " << aux->dato.telefono << endl;
		gotoxy(25, 8); cout << "-----------------------------" << endl;
		aux = aux->siguiente;
	}

	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 9); cout << "Total de clientes en cola: " << cola.cantidad << endl;
}
void modificiarCliente() {
	::system("cls");

	int idBuscado;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- MODIFICAR CLIENTE ----" << endl;
	gotoxy(25, 4); cout << "Ingrese el ID del cliente a modificar: ";
	cin >> idBuscado;
	NodoCliente* aux = buscarClientePorId(idBuscado);

	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No se encontro el cliente." << endl;
		return;
	}

	cin.ignore();
	SetConsoleTextAttribute(hConsole, 11);
	gotoxy(25, 5); cout << "Nuevo nombre: "; getline(cin, aux->dato.nombre);
	gotoxy(25, 6); cout << "Nueva direccion: ";	getline(cin, aux->dato.direccion);
	gotoxy(25, 7); cout << "Nuevo telefono: ";	cin >> aux->dato.telefono;

	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 9); cout << "\nCliente modificado correctamente." << endl;
}
void buscarCliente() {
	int idBuscado;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- BUSCAR CLIENTE ----" << endl;
	gotoxy(25, 4); cout << "Ingrese el ID del cliente: "; cin >> idBuscado;
	NodoCliente* aux = buscarClientePorId(idBuscado);

	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 6); cout << "No se encontro el cliente." << endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 2);
		gotoxy(25, 6); cout << "\nCliente encontrado:" << endl;
		gotoxy(25, 7); cout << "ID: " << aux->dato.id << endl;
		gotoxy(25, 8); cout << "Nombre: " << aux->dato.nombre << endl;
		gotoxy(25, 9); cout << "Direccion: " << aux->dato.direccion << endl;
		gotoxy(25, 10); cout << "Telefono: " << aux->dato.telefono << endl;
	}
}
void eliminarCliente() {
	::system("cls");

	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- ELIMINAR CLIENTE ----" << endl;
	if (cola.frente == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No hay clientes para eliminar." << endl;
		return;
	}

	NodoCliente* aux = cola.frente;
	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(25, 5); cout << "Se eliminara el cliente al frente de la cola:" << endl;
	gotoxy(25, 6); cout << "ID: " << aux->dato.id << endl;
	gotoxy(25, 7); cout << "Nombre: " << aux->dato.nombre << endl;

	cola.frente = cola.frente->siguiente;

	if (cola.frente == NULL) {
		cola.fincola = NULL;
	}

	delete aux;
	cola.cantidad--;
	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 9); cout << "Cliente eliminado correctamente." << endl;
}


void liberarCola() {
	NodoCliente* aux;

	while (cola.frente != NULL) {
		aux = cola.frente;
		cola.frente = cola.frente->siguiente;
		delete aux;
	}

	cola.fincola = NULL;
}
