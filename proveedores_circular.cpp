#include <cstdlib>
#include <iostream>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "consola.h"
#include "globales.h"
#include "modelos.h"
#include "proveedores_circular.h"

using namespace ftxui;
using namespace std;

static bool convertirEntero(const string& texto, int& valor) {
	try {
		size_t pos = 0;
		valor = stoi(texto, &pos);
		return pos == texto.size();
	}
	catch (...) {
		return false;
	}
}

static void mostrarMensajeCircular(const string& titulo,
	const string& mensaje,
	Color colorMensaje) {
	Element doc = vbox({
		text(titulo) | bold | color(Color::Cyan),
		separator(),
		text(mensaje) | color(colorMensaje),
		}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}
//Funcion para devolver la direccion de memoria
string direccionMemoriaProveedorCircular(NodoProveedor* nodo) {
	stringstream ss;
	ss << "0x" << hex << reinterpret_cast<uintptr_t>(nodo);
	return ss.str();
}

void ingresarProveedor() {
	::system("cls");

	string idTexto, nombre, empresa, telefonoTexto, error;
	int id = 0, telefono = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto inputNombre = Input(&nombre, "Nombre");
		auto inputEmpresa = Input(&empresa, "Empresa");
		auto inputTelefono = Input(&telefonoTexto, "Telefono");

		auto contenedor = Container::Vertical({
			inputId, inputNombre, inputEmpresa, inputTelefono
			});

		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("INGRESAR UN NUEVO PROVEEDOR") | bold | color(Color::Cyan),
				separator(),
				hbox(text("ID:       "), inputId->Render()),
				hbox(text("Nombre:   "), inputNombre->Render()),
				hbox(text("Empresa:  "), inputEmpresa->Render()),
				hbox(text("Telefono: "), inputTelefono->Render()),
				separator(),
				text("Use Tab para moverse y Enter para guardar."),
			};
			if (!error.empty())
				filas.push_back(text(error) | color(Color::Red));
			return vbox(filas) | border;
			});

		componente = CatchEvent(componente, [&](Event e) {
			if (e == Event::Return) { pantalla.ExitLoopClosure()(); return true; }
			return false;
			});

		pantalla.Loop(componente);

		if (!convertirEntero(idTexto, id)) {
			::system("cls");
			error = "Entrada invalida. El ID debe ser numerico.";
			continue;
		}
		if (!convertirEntero(telefonoTexto, telefono)) {
			::system("cls");
			error = "Entrada invalida. El telefono debe ser numerico.";
			continue;
		}
		break;
	}

	NodoProveedor* nuevo = new NodoProveedor;
	nuevo->dato.id = id;
	nuevo->dato.nombre = nombre;
	nuevo->dato.empresa = empresa;
	nuevo->dato.telefono = telefono;

	if (inicioCircular == NULL) {
		inicioCircular = nuevo;
		finCircular = nuevo;
		nuevo->siguiente = inicioCircular; //Se apunta a si mismo
	}
	else {
		finCircular->siguiente = nuevo;
		nuevo->siguiente = inicioCircular; //Cierra el cÃ­rculo
		finCircular = nuevo;
	}

	::system("cls");
	mostrarMensajeCircular("INGRESAR PROVEEDOR", "Proveedor agregado correctamente.", Color::Green);
}

void verProveedores() {
	::system("cls");

	Elements filas;
	filas.push_back(text("LISTA DE PROVEEDORES") | bold | color(Color::Cyan));
	filas.push_back(separator());

	if (inicioCircular == NULL) {
		filas.push_back(text("No hay proveedores registrados.") | color(Color::Red));
	}
	else {

		NodoProveedor* aux = inicioCircular;
		int y = 5;
		do {
			filas.push_back(vbox({
					text("ID:       " + to_string(aux->dato.id)),
					text("Nombre:   " + aux->dato.nombre),
					text("Empresa:  " + aux->dato.empresa),
					text("Telefono: " + to_string(aux->dato.telefono)),
					text("Direccion de memoria: " + direccionMemoriaProveedorCircular(aux)) | dim,
				}) | border);
			aux = aux->siguiente;
		} while (aux != inicioCircular); //Se detiene uando da la vuelta
	}
	Element doc = vbox(filas) | border;
	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}

void buscarProveedor() {
	::system("cls");

	string idTexto, error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("BUSCAR PROVEEDOR") | bold | color(Color::Cyan),
				separator(),
				hbox(text("ID del proveedor: "), inputId->Render()),
				separator(),
				text("Presione Enter para buscar."),
			};
			if (!error.empty())
				filas.push_back(text(error) | color(Color::Red));
			return vbox(filas) | border;
			});

		componente = CatchEvent(componente, [&](Event e) {
			if (e == Event::Return) { pantalla.ExitLoopClosure()(); return true; }
			return false;
			});

		pantalla.Loop(componente);

		if (!convertirEntero(idTexto, idBuscado)) {
			::system("cls");
			error = "Entrada invalida. El ID debe ser numerico.";
			continue;
		}
		break;
	}

	::system("cls");

	if (inicioCircular == NULL) {
		mostrarMensajeCircular("BUSCAR PROVEEDOR", "No hay proveedores registrados.", Color::Red);
		return;
	}

	NodoProveedor* aux = inicioCircular;
	bool encontrado = false;

	do {
		if (aux->dato.id == idBuscado) {
			encontrado = true;
			break;
		}
		aux = aux->siguiente;
	} while (aux != inicioCircular);

	if (!encontrado) {
		mostrarMensajeCircular("BUSCAR PROVEEDOR", "No se encontro el proveedor.", Color::Red);
		return;
	}

	Element doc = vbox({
		text("PROVEEDOR ENCONTRADO") | bold | color(Color::Cyan),
		separator(),
		text("ID:       " + to_string(aux->dato.id)),
		text("Nombre:   " + aux->dato.nombre),
		text("Empresa:  " + aux->dato.empresa),
		text("Telefono: " + to_string(aux->dato.telefono)),
		text("Direccion de memoria: " + direccionMemoriaProveedorCircular(aux)) | dim,
		}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}

void eliminarProveedor() {
	::system("cls");

	if (inicioCircular == NULL) {
		mostrarMensajeCircular("ELIMINAR PROVEEDOR",
			"No hay proveedores para eliminar.", Color::Red);
		return;
	}

	string idTexto, error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("ELIMINAR PROVEEDOR") | bold | color(Color::Cyan),
				separator(),
				hbox(text("ID del proveedor: "), inputId->Render()),
				separator(),
				text("Presione Enter para eliminar."),
			};
			if (!error.empty())
				filas.push_back(text(error) | color(Color::Red));
			return vbox(filas) | border;
			});

		componente = CatchEvent(componente, [&](Event e) {
			if (e == Event::Return) { pantalla.ExitLoopClosure()(); return true; }
			return false;
			});

		pantalla.Loop(componente);

		if (!convertirEntero(idTexto, idBuscado)) {
			::system("cls");
			error = "Entrada invalida. El ID debe ser numerico.";
			continue;
		}
		break;
	}

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
			break;
		}
		anterior = actual;
		actual = actual->siguiente;
	} while (actual != inicioCircular);

	::system("cls");

	if (encontrado) {
		mostrarMensajeCircular("ELIMINAR PROVEEDOR",
			"Proveedor eliminado correctamente.", Color::Green);
	}
	else {
		mostrarMensajeCircular("ELIMINAR PROVEEDOR",
			"No se encontro el proveedor.", Color::Red);
	}
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
