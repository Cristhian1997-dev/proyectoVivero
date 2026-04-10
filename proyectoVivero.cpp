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

struct NodoCliente {
	Cliente dato;
<<<<<<< HEAD
	NodoCliente* siguiente;	
=======
	NodoCliente* siguiente;
>>>>>>> ccda8aa (Modulo de filas)
};
//Variables globales 
NodoPlanta* cima = NULL; //PILA
NodoCliente* frente = NULL; //COLA
NodoCliente* fincola = NULL; //COLA

//Prototipos de funciones
void menuPrincipal();
void PilaPlantas();
void ColaClientes();
//Funciones para la pila de plantas
void ingresarPlanta();
void verPlantas();
void modificarPlanta();
void buscarPlanta();
void eliminarPlanta();
<<<<<<< HEAD
=======
NodoPlanta* buscarPlantaPorId(int id);

>>>>>>> ccda8aa (Modulo de filas)
//Funciones para la cola de clientes
void ingresarCliente();
void verClientes();
void modificiarCliente();
void buscarCliente();
void eliminarCliente();
<<<<<<< HEAD
=======
NodoCliente* buscarClientePorId(int id);

bool login(string nombre, string contra);
void liberarPila();
void liberarCola();
>>>>>>> ccda8aa (Modulo de filas)


void menuPrincipal() {
	int opcion;
<<<<<<< HEAD
	do{
	cout << "\nBIENVENIDO AL SISTEMA DE RAÍCES VERDES GT" << endl;
	cout << "1. Menu de plantas (Pila)" << endl;
	cout << "2. Menu de clientes (Cola)" << endl;
	cout << "3. Salir" << endl;
	cout << "Ingrese una opcion valida: "; cin >> opcion;
	} while (opcion != 3);

	switch(opcion){
	case 1:
		PilaPlantas();
		break;
	case 2:
		ColaClientes();
		break;
	case 3:
		break;
	}

	}
=======
	do {
		system("cls");
		cout << "\nBIENVENIDO AL SISTEMA DE RAÍCES VERDES GT" << endl;
		cout << "1. Menu de plantas (Pila)" << endl;
		cout << "2. Menu de clientes (Cola)" << endl;
		cout << "3. Salir" << endl;
		cout << "Ingrese una opcion valida: "; cin >> opcion;
	

		switch (opcion) {
		case 1:
			PilaPlantas();
			system("pause");
			break;
		case 2:
			ColaClientes();
			system("pause");
			break;
		case 3:
			cout << "\nSaliendo del sistema, Gracias por visitarnos." << endl;
			break;
		default:
			cout << "\nERROR.. Opcion no validad." << endl;
			system("pause");
			break;
		}
	} while (opcion != 3);
}
>>>>>>> ccda8aa (Modulo de filas)

void PilaPlantas() {
	int op;
	do
	{
		system("cls");
		cout << "\nMODULO DE PLANTAS - PILA" << endl;
		cout << "1. Ingrese una nueva planta." << endl;
		cout << "2. Ver inventario de plantas." << endl;
		cout << "3. Modificar una planta." << endl;
		cout << "4. Buscar una planta." << endl;
		cout << "5. Eliminar una planta." << endl;
		cout << "6. Regresar al menu principal." << endl;
		cout << "Ingrese una opcion valida: "; cin >> op;

		switch(op) {
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
			cout << "\nERROR.. Opcion no validad." << endl;
			system("pause");
			break;
		}

	} while (op != 6);
}
void ColaClientes(){
	int op;
	do
	{
		system("cls");
		cout << "\nMODULO DE PLANTAS - PILA" << endl;
		cout << "1. Ingrese un nuevo cliente." << endl;
		cout << "2. Ver lista de clientes." << endl;
		cout << "3. Modificar un cliente." << endl;
		cout << "4. Buscar un cliente." << endl;
		cout << "5. Eliminar un cliente." << endl;
		cout << "6. Regresar al menu principal." << endl;
		cout << "Ingrese una opcion valida: "; cin >> op;

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
			cout << "\nERROR.. Opcion no validad." << endl;
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
	cin >> nuevo->dato.id;

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
	cin >> nuevo->dato.precio;

	cout << "Ingrese Cantidad: ";
	cin >> nuevo->dato.cantidad;

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

	int idBuscado;
	cout << "\n--- ELIMINAR PLANTA ---" << endl;
	cout << "Ingrese el ID de la planta a eliminar: ";
	cin >> idBuscado;

	NodoPlanta* actual = cima;
	NodoPlanta* anterior = NULL;

	while (actual != NULL && actual->dato.id != idBuscado) {
		anterior = actual;
		actual = actual->siguiente;
	}

	if (actual == NULL) {
		cout << "No se encontro la planta." << endl;
		return;
	}

	if (anterior == NULL) {
		cima = actual->siguiente;
	}
	else {
		anterior->siguiente = actual->siguiente;
	}

	delete actual;
	cout << "Planta eliminada correctamente." << endl;
}

/* FUNCION DE COLA */
NodoCliente* buscarClientePorId(int id) {
	NodoCliente* aux = frente;

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
}
void verClientes() {

}
void modificiarCliente() {

}
void buscarCliente() {

}
void eliminarCliente() {

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

	while (frente != NULL) {
		aux = frente;
		frente = frente->siguiente;
		delete aux;
	}

	fincola = NULL;
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