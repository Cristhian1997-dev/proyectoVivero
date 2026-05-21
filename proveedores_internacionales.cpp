#include <cstdlib>
#include <iostream>
#include <windows.h>

#include "consola.h"
#include "globales.h"
#include "proveedores_internacionales.h"

using namespace std;
NodoDoble* crearNodoProveedorInternacional(const Proveedor& prov) {
	NodoDoble* nuevo = new NodoDoble();
	nuevo->dato = prov;
	nuevo->siguiente = NULL;
	nuevo->anterior = NULL;
	return nuevo;
}
NodoDoble* buscarProveedorInternacionalPorID(ListaDoble& lista, int id) { //Buscar un proveedor internacional por ID (devuelve el nodo o NULL si no se encuentra)
	NodoDoble* aux = lista.cabeza;
	while (aux != NULL) {
		if (aux->dato.id == id) {
			return aux;
		}
		aux = aux->siguiente;
	}
	return NULL;
}
void ingresarProveedorInternacional(ListaDoble& lista) {
	//Codigo para ingresar proveedores internacionales al final de la lista
	::system("cls");
	Proveedor nuevoProv;//Variable temporal para almacenar los datos
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- INGRESAR UN NUEVO PROVEEDOR INTERNACIONAL ----" << endl;
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
	if (buscarProveedorInternacionalPorID(lista, nuevoProv.id) != NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 7); cout << "Ya existe un proveedor con ese ID." << endl;
		return;
	}
	cin.ignore();
	gotoxy(25, 6); cout << "Ingrese Nombre: "; getline(cin, nuevoProv.nombre);
	gotoxy(25, 7); cout << "Ingrese Tipo: "; getline(cin, nuevoProv.tipo);
	gotoxy(25, 8); cout << "Ingrese Telefono: ";
	while (!(cin >> nuevoProv.telefono)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permite numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 8); cout << "Ingresa Telefono: ";
	}
	cin.ignore();
	gotoxy(25, 8); cout << "Ingrese Contacto: "; getline(cin, nuevoProv.contacto);
	NodoDoble* nuevo = crearNodoProveedorInternacional(nuevoProv);
	if (lista.cabeza == NULL) {
		//Si la lista esta vacia, el nuevo nodo se convierte en la cabeza y cola
		lista.cabeza = nuevo;
		lista.cola = nuevo;
	}
	else {
		//Si la lista no esta vacia, agregamos el nuevo nodo al final y actualizamos los punteros
		nuevo->anterior = lista.cola;
		lista.cola->siguiente = nuevo;
		lista.cola = nuevo;
	}
	gotoxy(25, 12); cout << "Proveedor internacional agregado correctamente al final de la lista." << endl;
}
void ingresarProveedorInternacionalAlInicio(ListaDoble& lista) {
	//Codigo para ingresar proveedores internacionales al inicio de la lista
	::system("cls");
	Proveedor nuevoProv;//Variable temporal 
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- INGRESAR UN NUEVO PROVEEDOR INTERNACIONAL ----" << endl;
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
	if (buscarProveedorInternacionalPorID(lista, nuevoProv.id) != NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 7); cout << "Ya existe un proveedor con ese ID." << endl;
		return;
	}
	cin.ignore();
	gotoxy(25, 6); cout << "Ingrese Nombre: "; getline(cin, nuevoProv.nombre);
	gotoxy(25, 7); cout << "Ingrese Tipo: "; getline(cin, nuevoProv.tipo);
	gotoxy(25, 8); cout << "Ingrese Telefono: ";
	while (!(cin >> nuevoProv.telefono)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permite numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 8); cout << "Ingrese Telefono: ";
	}
	cin.ignore();
	gotoxy(25, 8); cout << "Ingrese Contacto: "; getline(cin, nuevoProv.contacto);
	//Crea el nuevo nodo con los datos ingresados
	NodoDoble* nuevo = crearNodoProveedorInternacional(nuevoProv);
	if (lista.cabeza == NULL) {
		//Si la lista esta vacia, el nuevo nodo se convierte en la cabeza y cola
		lista.cabeza = nuevo;
		lista.cola = nuevo;
	}
	else {
		//Si la lista no esta vacia, agregamos el nuevo nodo al inicio y actualizamos los punteros
		nuevo->siguiente = lista.cabeza;
		lista.cabeza->anterior = nuevo;
		lista.cabeza = nuevo;
	}
	gotoxy(25, 12); cout << "Proveedor internacional agregado correctamente al inicio de la lista." << endl;
}
void verProveedoresInternacionales(ListaDoble& lista) {
	//Codigo para ver proveedores internacionales
	::system("cls");
	NodoDoble* aux = lista.cabeza;//Apuntamos al primer nodo de la lista
	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No hay proveedores internacionales registrados." << endl;
		return;
	}
	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 3); cout << "---- PROVEEDORES INTERNACIONALES ----" << endl;
	while (aux != NULL) {//Recorremos la lista hasta el final
		gotoxy(25, 5); cout << "ID: " << aux->dato.id << endl;
		gotoxy(25, 6); cout << "Nombre: " << aux->dato.nombre << endl;
		gotoxy(25, 7); cout << "Tipo: " << aux->dato.tipo << endl;
		gotoxy(25, 8); cout << "Telefono: " << aux->dato.telefono << endl;
		gotoxy(25, 9); cout << "Contacto: " << aux->dato.contacto << endl;
		gotoxy(25, 10); cout << "------------------------" << endl;
		aux = aux->siguiente;
	}
}
void verReversaProveedoresInternacionales(ListaDoble& lista) {
	//Codigo para ver proveedores internacionales en orden reverso
	::system("cls");
	NodoDoble* aux = lista.cola;//Apuntamos al ultimo nodo de la lista
	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 3); cout << "No hay proveedores internacionales registrados." << endl;
		return;
	}
	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 3); cout << "---- PROVEEDORES INTERNACIONALES (ORDEN INVERSO) ----" << endl;
	while (aux != NULL) {//Recorremos la lista del final al inicio
		gotoxy(25, 4); cout << "ID: " << aux->dato.id << endl;
		gotoxy(25, 5); cout << "Nombre: " << aux->dato.nombre << endl;
		gotoxy(25, 6); cout << "Tipo: " << aux->dato.tipo << endl;
		gotoxy(25, 7); cout << "Telefono: " << aux->dato.telefono << endl;
		gotoxy(25, 8); cout << "Contacto: " << aux->dato.contacto << endl;
		gotoxy(25, 9); cout << "------------------------" << endl;
		aux = aux->anterior;
	}
}
void modificarProveedorInternacional(ListaDoble& lista) {
	//Codigo para modificar proveedores internacionales
	::system("cls");
	if (lista.cabeza == NULL) {//Validacion si la lista esta vacia
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No hay proveedores internacionales registrados para modificar." << endl;
		return;
	}
	int idBuscado;
	gotoxy(25, 3); cout << "---- MODIFICAR PROVEEDOR INTERNACIONAL ----" << endl;
	gotoxy(25, 5); cout << "Ingrese el ID del proveedor internacional a modificar: ";
	cin >> idBuscado;
	while (!(cin >> idBuscado)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permite numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 5); cout << "Ingrese el ID del proveedor internacional a modificar: ";
	}
	NodoDoble* aux = buscarProveedorInternacionalPorID(lista, idBuscado);
	if (aux == NULL) {
		gotoxy(25, 8); cout << "No se encontro el proveedor." << endl;
		return;
	}
	cin.ignore();
	gotoxy(25, 6); cout << "Nuevo nombre: "; getline(cin, aux->dato.nombre);
	gotoxy(25, 7); cout << "Nuevo tipo: "; getline(cin, aux->dato.tipo);
	gotoxy(25, 8); cout << "Nuevo telefono: ";
	while (!(cin >> aux->dato.telefono)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permite numeros." << endl;
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 8); cout << "Ingrese Telefono: ";
	}
	cin.ignore();
	gotoxy(25, 9); cout << "Nuevo contacto: ";
	getline(cin, aux->dato.contacto);
	gotoxy(25, 12); cout << "Proveedor internacional modificado correctamente." << endl;
}
void buscarProveedorInternacional(ListaDoble& lista) {
	//Codigo para buscar proveedores internacionales
	::system("cls");
	if (lista.cabeza == NULL) {//Verificar que la lista no este vacia
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No hay proveedores internacionales registrados para buscar." << endl;
		return;
	}
	int idBuscado;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- BUSCAR PROVEEDOR INTERNACIONAL ----" << endl;
	gotoxy(25, 5); cout << "Ingrese el ID del proveedor internacional: "; cin >> idBuscado;
	NodoDoble* aux = buscarProveedorInternacionalPorID(lista, idBuscado);
	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 8); cout << "No se encontro el proveedor internacional." << endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 2);
		gotoxy(25, 7); cout << "Proveedor internacional encontrado:" << endl;
		gotoxy(25, 8); cout << "ID: " << aux->dato.id << endl;
		gotoxy(25, 9); cout << "Nombre: " << aux->dato.nombre << endl;
		gotoxy(25, 10); cout << "Tipo: " << aux->dato.tipo << endl;
		gotoxy(25, 11); cout << "Telefono: " << aux->dato.telefono << endl;
		gotoxy(25, 12); cout << "Contacto: " << aux->dato.contacto << endl;
	}
}
void eliminarProveedorInternacional(ListaDoble& lista) {

	::system("cls");
	if (lista.cabeza == NULL) {//Validacion si la lista esta vacia
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No hay proveedores internacionales registrados para eliminar." << endl;
		return;
	}
	int idBuscado;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- ELIMINAR PROVEEDOR INTERNACIONAL ----" << endl;
	gotoxy(25, 5); cout << "Ingrese el ID del proveedor internacional a eliminar: "; cin >> idBuscado;
	NodoDoble* aux = buscarProveedorInternacionalPorID(lista, idBuscado);
	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 8); cout << "No se encontro el proveedor." << endl;
		return;
	}
	if (aux == lista.cabeza) {//Si el nodo a eliminar es el primero de la lista
		lista.cabeza = lista.cabeza->siguiente;//Movemos la cabeza al siguiente nodo
		if (lista.cabeza != NULL) {
			lista.cabeza->anterior = NULL;//Actualizamos el puntero anterior de la nueva cabeza
		}
		else {
			lista.cola = NULL;//Si la lista queda vacia, actualizamos la cola a NULL
		}
	}
	else if (aux == lista.cola) {//Si el nodo a eliminar es el ultimo de la lista
		lista.cola = lista.cola->anterior;//Movemos la cola al nodo anterior
		if (lista.cola != NULL) {
			lista.cola->siguiente = NULL;//Actualizamos el puntero siguiente de la nueva cola
		}
		else {
			lista.cabeza = NULL;//Si la lista queda vacia, actualizamos la cabeza a NULL
		}
	}
	else {
		aux->anterior->siguiente = aux->siguiente;//Si el nodo a eliminar esta en medio, actualizamos los punteros del nodo anterior y siguiente para saltar el nodo a eliminar
		aux->siguiente->anterior = aux->anterior;//Actualizamos el puntero anterior del nodo siguiente para saltar el nodo a eliminar
	}
	delete aux;
	gotoxy(25, 8); cout << "\nProveedor internacional eliminado correctamente." << endl;
}
void liberarListaDoble(ListaDoble& lista) {
	::system("cls");
	//Codigo para liberar memoria 
	NodoDoble* aux = lista.cabeza;//Apuntamos al primer nodo de la lista
	while (aux != NULL) {//Recorremos la lista hasta el final
		NodoDoble* temp = aux;
		aux = aux->siguiente;//Movemos el puntero al siguiente nodo antes de eliminar el nodo actual
		delete temp;//Eliminamos el nodo actual
	}
	//Actualizamos los punteros de cabeza y cola a NULL para indicar que la lista esta vacia
	lista.cabeza = NULL;
	lista.cola = NULL;
	gotoxy(25, 5); cout << "Memoria de la lista doble de proveedores internacionales liberada correctamente." << endl;
}

