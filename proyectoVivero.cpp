#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <windows.h>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//Función para centrar el texto
void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

struct Planta {
	int id;
	string nombre;
	string tipo;
	string color;
	int precio;
	int cantidad;

};
struct Cliente {
	int id;
	string nombre;
	string direccion;
	int telefono;
};
struct NodoPlanta {
	Planta dato;
	NodoPlanta* siguiente;
};
struct NodoCliente {//Estructura de nodos para la cola
	Cliente dato;
	NodoCliente* siguiente;
};
//Struct para la controlar la cola (clientes)
struct Cola {
	int cantidad;//Opcional, para llevar el conteo de clientes en la cola
	NodoCliente* frente;
	NodoCliente* fincola;

	//Iniciar la cola vacía
	Cola() {
		cantidad = 0;
		frente = NULL;
		fincola = NULL;
	}
};
//Lista SIMPLE CIRCULAR PROVEEDORES
struct Proveedor {
	int id;
	string nombre;
	string empresa;
	int telefono;
};
struct NodoProveedor
{
	Proveedor dato;
	NodoProveedor* siguiente;
};

//Variables globales 
NodoPlanta* cima = NULL; //PILA
Cola cola;

//Punteros que serviran en la Lista Circular
NodoProveedor* inicioCircular = NULL;
NodoProveedor* finCircular = NULL;


//Prototipos de funciones
void menuPrincipal();
void PilaPlantas();
void ColaClientes();
void ListaCircularProveedor();
int menuConFlecha(string opcion[], int total, string encabezado, int startY);

//Prototipo para la pila de plantas
void ingresarPlanta();
void verPlantas();
void modificarPlanta();
void buscarPlanta();
void eliminarPlanta();

//Prototipo para la cola de clientes
void ingresarCliente();
void verClientes();
void modificiarCliente();
void buscarCliente();
void eliminarCliente();
NodoCliente* buscarClientePorId(int id);
bool login(string nombre, string contra);
void liberarPila();
void liberarCola();
void liberarListaCircular();

//Prototipo Lista Circular
void ingresarProveedor();
void verProveedores();
void buscarProveedor();
void eliminarProveedor();


int menuConFlecha(string opciones[], int total, string encabezado, int startY) {
	int seleccion = 0;
	int tecla;

	do {
		system("cls");
		SetConsoleTextAttribute(hConsole, 13);
		gotoxy(20, startY); cout << encabezado << endl;
		gotoxy(20, startY + 3); cout << " ----------- CREADORES ------------- ";
		gotoxy(20, startY + 4); cout << "[ Cristhian Mucun | 2290-17-17851   ]";
		gotoxy(20, startY + 5); cout << "[ Bryan Anleu     | 2290-20-23001   ]";
		gotoxy(20, startY + 6); cout << "[ David Hernandez | 2290-24-10427   ]";
		gotoxy(20, startY + 7); cout << " ----------------------------------- ";
		gotoxy(20, startY + 8); cout << "Use Flecha Arriba, Flecha Abajo y Enter.";

		for (int i = 0; i < total; i++) {
			gotoxy(25, startY + 10 + i); //Centramos las opciones dinámicamente
			if (i == seleccion) {
				SetConsoleTextAttribute(hConsole, 14); //Amarillo para resaltar
				cout << " -> " << opciones[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hConsole, 15); //BLanco para el resto
				cout << "    " << opciones[i] << endl;
			}
		}
		tecla = _getch();

		if (tecla == 0 || tecla == 224) {
			tecla = _getch();
			if (tecla == 72) {
				seleccion--;
				if (seleccion < 0) seleccion = total - 1;
			}
			else if (tecla == 80) {
				seleccion++;
				if (seleccion >= total)	seleccion = 0;

			}
		}
	} while (tecla != 13);
	return seleccion + 1;
}

void menuPrincipal() {
	int opcion;

	string opciones[] = {
		"Menu de plantas (Pila)",
		"Menu de cliente (Cola)",
		"Modulo de proveedores (Lista Circular)",
		"Salir"
	};


	string encabezado = "BIENVENIDO AL SISTEMA DE RAICES VERDES GT";

	do {
		opcion = menuConFlecha(opciones, 4, encabezado, 2);

		switch (opcion) {
		case 1: PilaPlantas(); break;
		case 2: ColaClientes(); break;
		case 3: ListaCircularProveedor(); break;
		case 4:
			SetConsoleTextAttribute(hConsole, 2);
			gotoxy(25, 20); cout << "Saliendo del sistema, gracias por visitarnos." << endl;
			break;
		}

	} while (opcion != 4);
}
void PilaPlantas() {
	int op;

	string opciones[]{
		"1. Ingrese una nueva planta.",
		"2. Ver inventario de plantas.",
		"3. Modificar una planta.",
		"4. Buscar una planta.",
		"5. Eliminar una planta.",
		"6. Regresar al menu principal."
	};

	do
	{
		op = menuConFlecha(opciones, 6, "MODULO DE PLANTAS - PILA", 3);

		switch (op) {
		case 1:	ingresarPlanta(); system("pause"); break;
		case 2: verPlantas(); system("pause"); break;
		case 3:	modificarPlanta(); system("pause");	break;
		case 4:	buscarPlanta();	system("pause"); break;
		case 5:	eliminarPlanta(); system("pause"); break;
		case 6:	break;
		}

	} while (op != 6);
}
void ColaClientes() {
	int op;
	string opciones[] = {
		"1. Ingresar un nuevo cliente",
		"2. Ver lista de clientes",
		"3. Modificar un cliente",
		"4. Buscar un cliente",
		"5. Eliminar un cliente",
		"6. Regresar al menu principal"
	};
	do {
		op = menuConFlecha(opciones, 6, "MODULO DE CLIENTES - COLA", 3);
		switch (op) {
		case 1:	ingresarCliente(); system("pause"); break;
		case 2: verClientes(); system("pause"); break;
		case 3: modificiarCliente(); system("pause"); break;
		case 4: buscarCliente(); system("pause"); break;
		case 5: eliminarCliente(); system("pause"); break;
		case 6:	break;
		}


	} while (op != 6);
}
void ListaCircularProveedor() {
	int op;
	string opciones[] = {
		"1. Ingresar un nuevo Proveedor.",
		"2. Ver lista de Proveedores.",
		"3. Buscar un Proveedor.",
		"4. Eliminar un Proveedor.",
		"5. Regresar al menu principal."
	};
	string encabezado = "PROVEEDORES - LISTA CIRCULAR";

	do {
		op = menuConFlecha(opciones, 5, encabezado, 3);
		switch (op) {
		case 1: ingresarProveedor(); system("pause"); break;
		case 2: verProveedores(); system("pause"); break;
		case 3: buscarProveedor(); system("pause"); break;
		case 4: eliminarProveedor(); system("pause"); break;
		case 5: break;
		}
	} while (op != 5);
}
void dibujo() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	SetConsoleOutputCP(CP_UTF8);// Codigo para que reconozca caracteres unicos

	cout <<
		"     ██                     ██    \n"
		"     █  ███             ███  █    \n"
		"     █     █           █     █    \n"
		"     █     █           █     █    \n"
		"     ███    ███████████     ███   \n"
		"     ███                    ███   \n"
		"    █       █          █      █   \n"
		"    █       █          █      █   \n"
		"    █       █          █      █   \n"
		"    █            ██           █   \n"
		"    █    ████          ████   █   \n"
		"    █           ████          █   \n"
		"    █    ████          ████   █   \n"
		"     █                       █    \n"
		"      █                     █     \n"
		"       █████████████████████      \n"
		"                                  \n"
		"          PROGRAMACION 3          \n";
	

	system("pause");
	system("cls");

}

NodoPlanta* buscarPlantaPorId(int id) {
	NodoPlanta* aux = cima;

	while (aux != NULL) {
		if (aux->dato.id == id) {
			return aux;
		}
		aux = aux->siguiente;
	}

	return NULL;
}
void ingresarPlanta() {
	system("cls");
	NodoPlanta* nuevo = new NodoPlanta;

	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "--- INGRESAR UNA NUEVA PLANTA ---";
	gotoxy(25, 5); cout << "Ingrese ID: ";
	while (!(cin >> nuevo->dato.id)) {
		system("cls");
		gotoxy(25, 3); cout << "--- INGRESAR UNA NUEVA PLANTA ---";
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numero." << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 5); cout << "Ingrese ID: ";
	}

	if (buscarPlantaPorId(nuevo->dato.id) != NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 7); cout << "ERROR: ID ya existe." << endl;
		delete nuevo;
		return;
	}

	cin.ignore();
	gotoxy(25, 6); cout << "Ingrese Nombre: "; getline(cin, nuevo->dato.nombre);
	gotoxy(25, 7); cout << "Ingrese Tipo: "; getline(cin, nuevo->dato.tipo);
	gotoxy(25, 8); cout << "Ingrese Color: "; getline(cin, nuevo->dato.color);
	gotoxy(25, 9); cout << "Ingrese Precio: ";
	while (!(cin >> nuevo->dato.precio)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros.";
		cin.clear();
		cin.ignore(1000, '\n');
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 9); cout << "Ingrese Precio: ";
	}
	gotoxy(25, 10); cout << "Ingrese Cantidad: ";
	while (!(cin >> nuevo->dato.cantidad)) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "Entrada invalida. Solo se permiten numeros.";
		cin.clear();
		cin.ignore(1000, '\n');
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, 10); cout << "Ingrese Cantidad: ";
	}


	nuevo->siguiente = cima;
	cima = nuevo;

	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 12); cout << "Planta agregada correctamente." << endl;
}
void verPlantas() {
	system("cls");

	NodoPlanta* aux = cima;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 2); cout << "INVENTARIO DE PLANTAS." << endl;

	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 4); cout << "No hay plantas registradas." << endl;
		return;
	}
	int y = 5;
	while (aux != NULL) {
		SetConsoleTextAttribute(hConsole, 9);
		gotoxy(25, y++); cout << "ID: " << aux->dato.id << endl;
		gotoxy(25, y++); cout << "Nombre: " << aux->dato.nombre << endl;
		gotoxy(25, y++); cout << "Tipo: " << aux->dato.tipo << endl;
		gotoxy(25, y++); cout << "Color: " << aux->dato.color << endl;
		gotoxy(25, y++); cout << "Precio: " << aux->dato.precio << endl;
		gotoxy(25, y++); cout << "Cantidad: " << aux->dato.cantidad << endl;
		gotoxy(25, y++); cout << "-----------------------------" << endl;

		aux = aux->siguiente;
	}
}
void modificarPlanta() {
	system("cls");

	int idBuscado;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "MODIFICAR PLANTA" << endl;
	gotoxy(25, 5); cout << "Ingrese el ID de la planta a modificar: ";
	cin >> idBuscado;

	NodoPlanta* aux = buscarPlantaPorId(idBuscado);

	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 6); cout << "No se encontro la planta." << endl;
		return;
	}

	int y = 6;
	cin.ignore();
	SetConsoleTextAttribute(hConsole, 11);
	gotoxy(25, y++); cout << "Nuevo nombre: "; getline(cin, aux->dato.nombre);
	gotoxy(25, y++); cout << "Nuevo tipo: ";	getline(cin, aux->dato.tipo);
	gotoxy(25, y++); cout << "Nuevo color: "; getline(cin, aux->dato.color);
	gotoxy(25, y++); cout << "Nuevo precio: "; cin >> aux->dato.precio;
	gotoxy(25, y++); cout << "Nueva cantidad: "; cin >> aux->dato.cantidad;

	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, y++); cout << "Planta modificada correctamente." << endl;
}
void buscarPlanta() {
	system("cls");

	int idBuscado;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "--- BUSCAR PLANTA ---" << endl;
	gotoxy(25, 4); cout << "Ingrese el ID de la planta: "; cin >> idBuscado;
	NodoPlanta* aux = buscarPlantaPorId(idBuscado);

	int y = 5;
	if (aux == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No se encontro la planta." << endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 2);
		gotoxy(25, y++); cout << "Planta encontrada:" << endl;
		gotoxy(25, y++); cout << "ID: " << aux->dato.id << endl;
		gotoxy(25, y++); cout << "Nombre: " << aux->dato.nombre << endl;
		gotoxy(25, y++); cout << "Tipo: " << aux->dato.tipo << endl;
		gotoxy(25, y++); cout << "Color: " << aux->dato.color << endl;
		gotoxy(25, y++); cout << "Precio: " << aux->dato.precio << endl;
		gotoxy(25, y++); cout << "Cantidad: " << aux->dato.cantidad << endl;
	}
}
void eliminarPlanta() {
	system("cls");

	//1. Validacion si la pila esta vacia
	if (cima == NULL) {
		SetConsoleTextAttribute(hConsole, 4);
		gotoxy(25, 5); cout << "No hay plantas en el inventario para eliminar." << endl;
		return;
	}

	//Apuntamos al nodo de la sima
	NodoPlanta* aux = cima;

	//Mostramos que se va a eliminar
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- ELIMINAR PLANTA ----" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(25, 4); cout << "Se eliminara la planta en la sima de la pila:" << endl;
	gotoxy(25, 5); cout << "ID: " << aux->dato.id << endl;
	gotoxy(25, 5); cout << "Nombre: " << aux->dato.nombre << endl;

	//Movemos la sima al siguiente nodo debajo de ella
	cima = cima->siguiente;

	delete aux;
	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 7); cout << "---- Panta eliminada correctamente. ----" << endl;
}

/* FUNCION DE COLA */
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
	//Aqui va el código de ingresar colas
	system("cls");
	NodoCliente* nuevo = new NodoCliente;
	SetConsoleTextAttribute(hConsole, 9);
	gotoxy(25, 3); cout << "---- INGRESAR UN NUEVO CLIENTE ----" << endl;;
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
	system("cls");
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
	system("cls");

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
	system("cls");

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

//Lista Circular
void ingresarProveedor() {
	system("cls");
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
		nuevo->siguiente = inicioCircular; //Cierra el círculo
		finCircular = nuevo;
	}

	SetConsoleTextAttribute(hConsole, 2);
	gotoxy(25, 10); cout << "Proveedor agregado correctamente.";
	cout << "\n\n";
}
void verProveedores() {
	system("cls");
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
	system("cls");
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
	system("cls");
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

bool login(string nombre, string contra) {
	string linea;
	string usuarioArchivo;
	string contraArchivo;
	size_t pos;

	fstream archivo("datos.txt", ios::in);

	if (!archivo) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "No se pudo abrir el archivo datos.txt" << endl;
		return false;
	}
	while (getline(archivo, linea)) {
		pos = linea.find(",");

		if (pos != string::npos) {
			usuarioArchivo = linea.substr(0, pos);
			contraArchivo = linea.substr(pos + 1);

			if (nombre == usuarioArchivo && contra == contraArchivo) {
				archivo.close();
				return true;
			}
		}
	}
	archivo.close();
	return false;
}

void liberarPila() {
	NodoPlanta* aux;

	while (cima != NULL) {
		aux = cima;
		cima = cima->siguiente;
		delete aux;
	}
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

	system("pause");
	return 0;
}