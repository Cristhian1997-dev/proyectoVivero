#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "arbol_abb.h"
#include "cola_clientes.h"
#include "consola.h"
#include "globales.h"
#include "menu.h"
#include "menu_arboles.h"
#include "pila_plantas.h"
#include "proveedores_circular.h"
#include "proveedores_internacionales.h"
#include "proveedores_locales.h"

using namespace std;
using namespace ftxui;
static void mostrarMensajeMenu(const string& titulo, const string& mensaje, Color colorMensaje) {
	::system("cls");
	Element documento = vbox({
		text(titulo) | bold | color(Color::Green),
		separator(),
		text(mensaje) | color(colorMensaje),
	}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(documento));
	Render(pantalla, documento);
	pantalla.Print();
	cout << endl;
}
void menuPrincipal() {
	int opcion;

	string opciones[] = {
		"Menu de plantas (Pila)",
		"Menu de cliente (Cola)",
		"Menu de proveedores locales (Lista Simple)",
		"Menu de proveedores internacionales (Lista Doble)",
		"Modulo de proveedores (Lista Circular)",
		"Arboles Binarios de Busqueda",
		"Salir"
	};


	string encabezado = "BIENVENIDO AL SISTEMA DE RAICES VERDES GT";

	do {
		opcion = menuConFlecha(opciones, 7, encabezado, 2);

		switch (opcion) {
		case 1: PilaPlantas(); break;
		case 2: ColaClientes(); break;
		case 3: ProveedoresLocales(); break;
		case 4: ProveedoresInternacionales(); break;
		case 5: ListaCircularProveedor(); break;
		case 6: MenuArbolesBinarios(); break;
		case 7:
			mostrarMensajeMenu("SISTEMA", "Saliendo del sistema, gracias por visitarnos.", Color::Green);
			break;
		}
	} while (opcion != 7);
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
		case 1:	ingresarPlanta(); ::system("pause"); break;
		case 2: verPlantas(); ::system("pause"); break;
		case 3:	modificarPlanta(); ::system("pause");	break;
		case 4:	buscarPlanta();	::system("pause"); break;
		case 5:	eliminarPlanta(); ::system("pause"); break;
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
		case 1:	ingresarCliente(); ::system("pause"); break;
		case 2: verClientes(); ::system("pause"); break;
		case 3: modificiarCliente(); ::system("pause"); break;
		case 4: buscarCliente(); ::system("pause"); break;
		case 5: eliminarCliente(); ::system("pause"); break;
		case 6:	break;
		}


	} while (op != 6);
}
void ProveedoresLocales() {
	int op;
	string opciones[] = {
		"1. Ingrese un nuevo proveedor local al inicio",
		"2. Ingrese un nuevo proveedor local al final",
		"3. Ver lista de proveedores locales",
		"4. Modificar un proveedor local",
		"5. Buscar un proveedor local",
		"6. Eliminar un proveedor local",
		"7. Limpiar toda la lista de proveedores locales",
		"8. Regresar al menu principal"
	};
	do {
		op = menuConFlecha(opciones, 8, "MODULO DE PROVEEDORES LOCALES - LISTA SIMPLE", 3);
		switch (op) {
		case 1: ingresarProveedorLocalAlInicio(cabeza); ::system("pause"); break;
		case 2: ingresarProveedorLocalAlFinal(cabeza); ::system("pause"); break;
		case 3:	verProveedoresLocales(cabeza); ::system("pause"); break;
		case 4:	modificarProveedorLocal(cabeza); ::system("pause"); break;
		case 5: buscarProveedorLocal(cabeza); ::system("pause"); break;
		case 6: eliminarProveedorLocal(cabeza); ::system("pause"); break;
		case 7: liberarListaSimple(cabeza); ::system("pause"); break;
		case 8: break;
		}
	} while (op != 8);
}
void ProveedoresInternacionales() {
	ListaDoble listaInternacional; //Lista para manejar los proveedores internacionales
	int op;
	string opciones[] = {
		"1. Ingrese un nuevo proveedor internacional al final",
		"2. Ingrese un nuevo proveedor internacional al inicio",
		"3. Ver lista de proveedores internacionales",
		"4. Ver lista de proveedores internacionales en orden reverso",
		"5. Modificar un proveedor internacional",
		"6. Buscar un proveedor internacional",
		"7. Eliminar un proveedor internacional",
		"8. Limpiar toda la lista de proveedores internacionales",
		"9. Regresar al menu principal"
	};
	do {
		op = menuConFlecha(opciones, 9, "MODULO DE PROVEEDORES INTERNACIONALES - LISTA DOBLE", 3);
		switch (op) {
		case 1: ingresarProveedorInternacional(listaInternacional); ::system("pause"); break;
		case 2: ingresarProveedorInternacionalAlInicio(listaInternacional); ::system("pause"); break;
		case 3: verProveedoresInternacionales(listaInternacional); ::system("pause"); break;
		case 4: verReversaProveedoresInternacionales(listaInternacional); ::system("pause"); break;
		case 5: modificarProveedorInternacional(listaInternacional); ::system("pause"); break;
		case 6: buscarProveedorInternacional(listaInternacional); ::system("pause"); break;
		case 7: eliminarProveedorInternacional(listaInternacional); ::system("pause"); break;
		case 8: liberarListaDoble(listaInternacional); ::system("pause"); break;
		case 9: break;
		}
	} while (op != 9);
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
		case 1: ingresarProveedor(); ::system("pause"); break;
		case 2: verProveedores(); ::system("pause"); break;
		case 3: buscarProveedor(); ::system("pause"); break;
		case 4: eliminarProveedor(); ::system("pause"); break;
		case 5: break;
		}
	} while (op != 5);
}
void ArbolABBPlantas() {
	int op;
	string opciones[] = {
		"1. Insertar nodo en el arbol ABB",
		"2. Buscar nodo en el arbol ABB",
		"3. Recorrer estructura Pre/In/Pos",
		"4. Eliminar nodo del arbol ABB",
		"5. Mostrar arbol en forma vertical",
		"6. Regresar al menu principal"
	};

	do {
		op = menuConFlecha(opciones, 6, "MODULO DE PLANTAS - ARBOL ABB", 3);
		switch (op) {
		case 1: ingresarPlantaABB(); ::system("pause"); break;
		case 2: buscarPlantaABB(); ::system("pause"); break;
		case 3: recorrerArbolABB(); ::system("pause"); break;
		case 4: eliminarPlantaABB(); ::system("pause"); break;
		case 5: mostrarArbolABBVertical(); ::system("pause"); break;
		case 6: break;
		}
	} while (op != 6);
}


