#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;


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

//Variables globales 
NodoPlanta* cima = NULL; //PILA
Cola cola; //Cola global para manejar los clientes


//Prototipos de funciones
void menuPrincipal();
void PilaPlantas();
void ColaClientes();
int menuConFlecha(string opcion[], int total, string encabezado);

//Funciones para la pila de plantas
void ingresarPlanta();
void verPlantas();
void modificarPlanta();
void buscarPlanta();
void eliminarPlanta();
NodoPlanta* buscarPlantaPorId(int id);

//Funciones para la cola de clientes
void ingresarCliente();
void verClientes();
void modificiarCliente();
void buscarCliente();
void eliminarCliente();
NodoCliente* buscarClientePorId(int id);
bool login(string nombre, string contra);
void liberarPila();
void liberarCola();

int menuConFlecha(string opciones[], int total, string encabezado) {
	int seleccion = 0;
	int tecla;

	do {
		system("cls");
		cout << encabezado << endl;
		cout <<"\t" << "\nUse Flecha Arriba, Flecha Abajo y Enter.\n\n";

		for (int i = 0; i < total; i++) {
			if (i == seleccion) {
				cout << " -> " << opciones[i] << endl;
			}
			else {
				cout << "    " << opciones[i] << endl;
			}
		}
		tecla = _getch();

		if (tecla == 0 || tecla == 224) {
			tecla = _getch();
			if (tecla == 72) {
				seleccion--;
				if (seleccion < 0) {
					seleccion = total - 1;
				}
			}
			else if (tecla == 80) {
				seleccion++;
				if (seleccion >= total) {
					seleccion = 0;
				}
			}
		}
	} while (tecla != 13);
	return seleccion + 1;
}

void menuPrincipal() {
	int opcion;

	string opciones[] = {
		"\tMenu de plantas (Pila)",
		"\tMenu de cliente (Cola)",
		"\tSalir"
	};

	
	string encabezado =
		"\t--------------------o--------------------\n"
		"\tBIENVENIDO AL SISTEMA DE RAICES VERDES GT\n"
		"\t--------------------o--------------------\n"
		"\t        INTEGRANTES DEL GRUPO\n"
		"\t[ Cristian Mucun  | 2290-17-17851   ]\n"
		"\t[ Bryan Anleu     | 2290-20-23001   ]\n"
		"\t[ David Hernandez | 2290-24-10427   ]\n"
		"\t--------------------o--------------------";

	do {
		opcion = menuConFlecha(opciones, 3, encabezado);

		switch (opcion) {
		case 1:
			PilaPlantas();
			break;
		case 2:
			ColaClientes();
			break;
		case 3:
			cout << "\nSaliendo del sistema, gracias por visitarnos." << endl;
			break;
		default:
			cout << "\nERROR.. Opcion no valida." << endl;
			system("pause");
			break;
		}

	} while (opcion != 3);
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

	string encabezado =
		"\nMODULO DE PLANTAS - PILA\n"
		"----------------------------";

	do
	{
		op = menuConFlecha(opciones, 6, encabezado);

		switch (op) {
		case 1:
			ingresarPlanta();
			system("pause");
			break;
		case 2:
			verPlantas();
			system("pause");
			break;
		case 3:
			modificarPlanta();
			system("pause");
			break;
		case 4:
			buscarPlanta();
			system("pause");
			break;
		case 5:
			eliminarPlanta();
			system("pause");
			break;
		case 6:
			break;
		default:
			cout << "\nERROR.. Opcion no valida." << endl;
			system("pause");
			break;
		}

	} while (op != 6);
}
void ColaClientes() {
	int op;

	string opciones[] = {
		"Ingrese un nuevo cliente",
		"Ver lista de clientes",
		"Modificar un cliente",
		"Buscar un cliente",
		"Eliminar un cliente",
		"Regresar al menu principal"
	};

	string encabezado =
		"\nMODULO DE CLIENTES - COLA\n"
		"-----------------------------";

	do {
		op = menuConFlecha(opciones, 6, encabezado);

		switch (op) {
		case 1:
			ingresarCliente();
			system("pause");
			break;
		case 2:
			verClientes();
			system("pause");
			break;
		case 3:
			modificiarCliente();
			system("pause");
			break;
		case 4:
			buscarCliente();
			system("pause");
			break;
		case 5:
			eliminarCliente();
			system("pause");
			break;
		case 6:
			break;
		default:
			cout << "\nERROR.. Opcion no valida." << endl;
			system("pause");
			break;
		}


	} while (op != 6);
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

	cout << "\nINGRESAR UNA NUEVA PLANTA." << endl;
	cout << "Ingrese ID: ";
	while (!(cin >> nuevo->dato.id)) {
		cout << "Entrada invalida. Solo se permiten numero." << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Ingrese ID: ";
	}

	if (buscarPlantaPorId(nuevo->dato.id) != NULL) {
		cout << "Ya existe una planta con ese ID." << endl;
		delete nuevo;
		return;
	}

	cin.ignore();
	cout << "Ingrese Nombre: ";
	getline(cin, nuevo->dato.nombre);

	cout << "Ingrese Tipo: ";
	getline(cin, nuevo->dato.tipo);

	cout << "Ingrese Color: ";
	getline(cin, nuevo->dato.color);

	cout << "Ingrese Precio: ";
	while (!(cin >> nuevo->dato.precio)) {
		cout << "Entrada invalida. Solo se permiten numeros." << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Ingrese Precio: ";
	}

	cout << "Ingrese Cantidad: ";
	while (!(cin >> nuevo->dato.cantidad)) {
		cout << "Entrada invalida. Solo se permiten numeros." << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Ingrese Cantidad: ";
	}
	

	nuevo->siguiente = cima;
	cima = nuevo;

	cout << "\nPlanta agregada correctamente." << endl;
}
void verPlantas() {
	system("cls");

	NodoPlanta* aux = cima;
	cout << "\nINVENTARIO DE PLANTAS." << endl;

	if (aux == NULL) {
		cout << "No hay plantas registradas." << endl;
		return;
	}
	while (aux != NULL) {
		cout << "\nID: " << aux->dato.id << endl;
		cout << "Nombre: " << aux->dato.nombre << endl;
		cout << "Tipo: " << aux->dato.tipo << endl;
		cout << "Color: " << aux->dato.color << endl;
		cout << "Precio: " << aux->dato.precio << endl;
		cout << "Cantidad: " << aux->dato.cantidad << endl;
		cout << "-----------------------------" << endl;

		aux = aux->siguiente;
	}
}
void modificarPlanta() {
	system("cls");

	int idBuscado;
	cout << "\nMODIFICAR PLANTA" << endl;
	cout << "Ingrese el ID de la planta a modificar: ";
	cin >> idBuscado;

	NodoPlanta* aux = buscarPlantaPorId(idBuscado);

	if (aux == NULL) {
		cout << "No se encontro la planta." << endl;
		return;
	}

	cin.ignore();
	cout << "Nuevo nombre: ";
	getline(cin, aux->dato.nombre);

	cout << "Nuevo tipo: ";
	getline(cin, aux->dato.tipo);

	cout << "Nuevo color: ";
	getline(cin, aux->dato.color);

	cout << "Nuevo precio: ";
	cin >> aux->dato.precio;

	cout << "Nueva cantidad: ";
	cin >> aux->dato.cantidad;

	cout << "\nPlanta modificada correctamente." << endl;
}
void buscarPlanta() {
	system("cls");

	int idBuscado;
	cout << "\n--- BUSCAR PLANTA ---" << endl;
	cout << "Ingrese el ID de la planta: ";
	cin >> idBuscado;

	NodoPlanta* aux = buscarPlantaPorId(idBuscado);

	if (aux == NULL) {
		cout << "No se encontro la planta." << endl;
	}
	else {
		cout << "\nPlanta encontrada:" << endl;
		cout << "ID: " << aux->dato.id << endl;
		cout << "Nombre: " << aux->dato.nombre << endl;
		cout << "Tipo: " << aux->dato.tipo << endl;
		cout << "Color: " << aux->dato.color << endl;
		cout << "Precio: " << aux->dato.precio << endl;
		cout << "Cantidad: " << aux->dato.cantidad << endl;
	}
}
void eliminarPlanta() {
	system("cls");

	//1. Validacion si la pila esta vacia
	if (cima == NULL) {
		cout << "\nNo hay plantas en el inventario para eliminar." << endl;
		return;
	}

	//Apuntamos al nodo de la sima
	NodoPlanta* aux = cima;

	//Mostramos que se va a eliminar
	cout << "\nELIMINAR PLANTA" << endl;
	cout << "Se eliminara la planta en la sima de la pila:" << endl;
	cout << "ID: " << aux->dato.id << endl;
	cout << "Nombre: " << aux->dato.nombre << endl;

	//Movemos la sima al siguiente nodo debajo de ella
	cima = cima->siguiente;

	delete aux;
	cout << "\nPanta eliminada correctamente." << endl;

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
	cout << "\nINGRESAR UN NUEVO CLIENTE." << endl;
	cout << "Ingrese ID: ";
	while (!(cin >> nuevo->dato.id)) {
		cout << "Entrada invalida. Solo se permite numeros." << endl;
		cin.clear();
		cin.ignore();
		cout << "Ingresa ID: ";
	}

	//Verificar que no exista un cliente con el mismo ID
	if (buscarClientePorId(nuevo->dato.id) != NULL) {
		cout << "Ya existe un cliente con ese ID." << endl;
		delete nuevo;
		return;
	}

	cin.ignore();
	cout << "Ingrese Nombre: ";
	getline(cin, nuevo->dato.nombre);

	cout << "Ingrese Direccion: ";
	getline(cin, nuevo->dato.direccion);

	cout << "Ingrese Telefono: ";
	while (!(cin >> nuevo->dato.telefono)) {
		cout << "Entrada invalida. Solo se permiten numeros." << endl;
		cin.clear();
		cin.ignore();
		cout << "Ingrese Telefono: ";
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
	cout << "\nCliente agregado correctamente." << endl;
}
void verClientes() {
	system("cls");
	NodoCliente* aux = cola.frente;

	cout << "\nLISTA DE CLIENTES." << endl;
	if (aux == NULL) {
		cout << "No hay clientes registrados." << endl;
		return;
	}

	while (aux != NULL) {
		cout << "\nID: " << aux->dato.id << endl;
		cout << "Nombre: " << aux->dato.nombre << endl;
		cout << "Direccion: " << aux->dato.direccion << endl;
		cout << "Telefono: " << aux->dato.telefono << endl;
		cout << "-----------------------------" << endl;
		aux = aux->siguiente;
	}

	cout << "Total de clientes en cola: " << cola.cantidad << endl;
}
void modificiarCliente() {
	system("cls");

	int idBuscado;
	cout << "\nMODIFICAR CLIENTE" << endl;
	cout << "Ingrese el ID del cliente a modificar: ";
	cin >> idBuscado;

	NodoCliente* aux = buscarClientePorId(idBuscado);

	if (aux == NULL) {
		cout << "No se encontro el cliente." << endl;
		return;
	}

	cin.ignore();
	cout << "Nuevo nombre: ";
	getline(cin, aux->dato.nombre);

	cout << "Nueva direccion: ";
	getline(cin, aux->dato.direccion);

	cout << "Nuevo telefono: ";
	cin >> aux->dato.telefono;

	cout << "\nCliente modificado correctamente." << endl;
}
void buscarCliente() {
	//Misma logica y estructura que buscarPlanta(); pero con clientes
	int idBuscado;
	cout << "\n--- BUSCAR CLIENTE ---" << endl;
	cout << "Ingrese el ID del cliente: ";
	cin >> idBuscado;

	NodoCliente* aux = buscarClientePorId(idBuscado);

	if (aux == NULL) {
		cout << "No se encontro el cliente." << endl;
	}
	else {
		cout << "\nCliente encontrado:" << endl;
		cout << "ID: " << aux->dato.id << endl;
		cout << "Nombre: " << aux->dato.nombre << endl;
		cout << "Direccion: " << aux->dato.direccion << endl;
		cout << "Telefono: " << aux->dato.telefono << endl;
	}
}
void eliminarCliente() {
	system("cls");

	if (cola.frente == NULL) {
		cout << "No hay clientes para eliminar." << endl;
		return;
	}

	NodoCliente* aux = cola.frente;
	cout << "\nSe eliminara el cliente al frente de la cola:" << endl;
	cout << "ID: " << aux->dato.id << endl;
	cout << "Nombre: " << aux->dato.nombre << endl;

	cola.frente = cola.frente->siguiente;

	if (cola.frente == NULL) {
		cola.fincola = NULL;
	}

	delete aux;
	cola.cantidad--;
	cout << "Cliente eliminado correctamente." << endl;
}

bool login(string nombre, string contra) {
	string linea;
	string usuarioArchivo;
	string contraArchivo;
	size_t pos;

	fstream archivo("datos.txt", ios::in);

	if (!archivo) {
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

int main() {
	string nombre;
	string contra;

	cout << "Bienvenidos a RAICES VERDES GT." << endl;
	cout << "Ingrese su usuario: ";
	cin >> nombre;
	cout << "Ingrese su contrasena: ";
	cin >> contra;

	if (login(nombre, contra)) {
		menuPrincipal();
	}
	else {
		cout << "Los datos ingresados son incorrectos." << endl;
	}

	liberarPila();
	liberarCola();

	system("pause");
	return 0;
}