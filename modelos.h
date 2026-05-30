#pragma once

#include <string>

struct Planta {
	int id;
	std::string nombre;
	std::string tipo;
	std::string color;
	int precio;
	int cantidad;
};

struct Cliente {
	int id;
	std::string nombre;
	std::string direccion;
	int telefono;
};

struct NodoPlanta {
	Planta dato;
	NodoPlanta* siguiente;
	NodoPlanta* izquierdo;
	NodoPlanta* derecho;

	NodoPlanta() : dato(), siguiente(NULL), izquierdo(NULL), derecho(NULL) {}
	NodoPlanta(const Planta& planta) : dato(planta), siguiente(NULL), izquierdo(NULL), derecho(NULL) {}
};

struct NodoCliente {
	Cliente dato;
	NodoCliente* siguiente;
};

struct Cola {
	int cantidad;
	NodoCliente* frente;
	NodoCliente* fincola;

	Cola() {
		cantidad = 0;
		frente = NULL;
		fincola = NULL;
	}
};

struct Proveedor {
	int id;
	std::string nombre;
	std::string tipo;
	std::string empresa;
	int telefono;
	std::string contacto;
};

struct NodoSimple {
	Proveedor dato;
	NodoSimple* siguiente;
};

struct NodoDoble {
	Proveedor dato;
	NodoDoble* siguiente;
	NodoDoble* anterior;
};

struct ListaDoble {
	int cantidad;
	NodoDoble* cabeza;
	NodoDoble* cola;

	ListaDoble() : cabeza(NULL), cola(NULL), cantidad(0) {}
};

struct NodoProveedor {
	Proveedor dato;
	NodoProveedor* siguiente;
};

struct NodoABB {
	Planta dato;
	NodoABB* izquierda;
	NodoABB* derecha;
};

