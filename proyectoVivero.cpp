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
	NodoCliente* siguiente;	
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
//Funciones para la cola de clientes
void ingresarCliente();
void verClientes();
void modificiarCliente();
void buscarCliente();
void eliminarCliente();


void menuPrincipal() {
	int opcion;
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


int main() {
	string nombre;
	string contra;
	string linea; // Variable temporal donde se almacenará usuario y contraseña
	string arreglo[2]; // Este arreglo servirá para separar el usuario y la contraseña
	size_t pos = 0; // Variable que contendrá la posición donde se encuentra la coma
	int contador = 0;
	string dato;
	int fin = 0;

	cout << "Bienvenidos a RAÍCES VERDES GT." << endl;
	cout << "Ingrese su usuario." << endl; cin >> nombre;
	cout << "Ingrese su contraseña." << endl; cin >> contra;

	fstream archivo("datos.txt");

	while (getline(archivo, linea) && fin == 0 ) {
		while ((pos = linea.find(",")) != string::npos) {
			dato = linea.substr(0, pos);
			arreglo[contador] = dato;
			linea.erase(0, pos + 1);
			contador++;
		}
		if (arreglo[0].find(nombre, 0) != string::npos) {
			fin = 1;
		}
		contador = 0;
	}

	if (nombre == arreglo[0] && contra == arreglo[1]) {
		menuPrincipal();
	}
	else {
		cout << "Los datos ingresados son incorrectos" << endl;
	}

	

	system("pause");
	return 0;
}