#include <cstdlib>
#include <iostream>
#include <String>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "cola_clientes.h"
#include "consola.h"
#include "globales.h"

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

static void mostrarMensajeCola(const string& titulo,
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
//Funcion para devolver la direccion de memoria del nodo
string direccionMemoriaCliente(NodoCliente* nodo) {
	stringstream ss;
	ss << "0x" << hex << reinterpret_cast<uintptr_t>(nodo);
	return ss.str();
}

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
	//Aqui va el codigo de ingresar colas
	::system("cls");

	string idTexto, nombre, direccion, telefonoTexto, error;
	int id = 0, telefono = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto inputNombre = Input(&nombre, "Nombre");
		auto inputDireccion = Input(&direccion, "Direccion");
		auto inputTelefono = Input(&telefonoTexto, "Telefono");

		auto contenedor = Container::Vertical({
			inputId, inputNombre, inputDireccion, inputTelefono
			});

		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("---- INGRESAR UN NUEVO CLIENTE ----") | bold | color(Color::Cyan),
				separator(),
				hbox(text("ID:         "), inputId->Render()),
				hbox(text("Nombre:     "), inputNombre->Render()),
				hbox(text("Direccion:  "), inputDireccion->Render()),
				hbox(text("Telefono:   "), inputTelefono->Render()),
				separator(),
				text("Use Tab para moverse y Enter para guardar."),
			};
			if (!error.empty())
				filas.push_back(text(error) | color(Color::Red));
			return vbox(filas) | border;
			});

		componente = CatchEvent(componente, [&](Event e) {
			if (e == Event::Return) {
				pantalla.ExitLoopClosure()();
				return true;
			}
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

	//Verificar que no exista un cliente con el mismo ID
	if (buscarClientePorId(id) != NULL) {
		::system("cls");
		mostrarMensajeCola("INGRESAR CLIENTE", "ERROR: Ya existe un cliente con ese ID.", Color::Red);
		return;
	}

	NodoCliente* nuevo = new NodoCliente;
	nuevo->dato.id = id;
	nuevo->dato.nombre = nombre;
	nuevo->dato.direccion = direccion;
	nuevo->dato.telefono = telefono;
	nuevo->siguiente = NULL;

	if (cola.frente == NULL) {
		cola.frente = cola.fincola = nuevo;
	}
	else {
		cola.fincola->siguiente = nuevo;
		cola.fincola = nuevo;
	}
	cola.cantidad++;

	::system("cls");
	mostrarMensajeCola("INGRESAR CLIENTE", "Cliente agregado correctamente.", Color::Green);
}

void verClientes() {
	::system("cls");
	NodoCliente* aux = cola.frente;

	Elements filas;
	filas.push_back(text("---- LISTA DE CLIENTES ----") | bold | color(Color::Cyan));
	filas.push_back(separator());

	if (aux == NULL) {
		filas.push_back(text("No hay clientes registrados.") | color(Color::Red));
	}
	else {
		while (aux != NULL) {
			filas.push_back(vbox({
				text("ID:        " + to_string(aux->dato.id)),
				text("Nombre:    " + aux->dato.nombre),
				text("Direccion: " + aux->dato.direccion),
				text("Telefono:  " + to_string(aux->dato.telefono)),
				text("Direccion de memoria: " + direccionMemoriaCliente(aux)) | dim,
				}) | border);
			aux = aux->siguiente;
		}
		filas.push_back(
			text("Total en cola: " + to_string(cola.cantidad)) | color(Color::Green)
		);
	}

	Element doc = vbox(filas) | border;
	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}

void modificiarCliente() {
	::system("cls");

	string idTexto, error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("---- MODIFICAR CLIENTE ----") | bold | color(Color::Cyan),
				separator(),
				hbox(text("Ingrese el ID del cliente a modificar: "), inputId->Render()),
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

	NodoCliente* aux = buscarClientePorId(idBuscado);
	if (aux == NULL) {
		::system("cls");
		mostrarMensajeCola("---- MODIFICAR CLIENTE ----", "No se encontro el cliente.", Color::Red);
		return;
	}

	string nombre = aux->dato.nombre;
	string direccion = aux->dato.direccion;
	string telefonoTexto = to_string(aux->dato.telefono);
	int telefono = aux->dato.telefono;
	error.clear();

	while (true) {
		::system("cls");
		auto inputNombre = Input(&nombre, "Nombre");
		auto inputDireccion = Input(&direccion, "Direccion");
		auto inputTelefono = Input(&telefonoTexto, "Telefono");

		auto contenedor = Container::Vertical({
			inputNombre, inputDireccion, inputTelefono
			});

		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("---- MODIFICAR CLIENTE ----") | bold | color(Color::Cyan),
				separator(),
				text("ID: " + to_string(aux->dato.id)),
				hbox(text("Nombre:     "), inputNombre->Render()),
				hbox(text("Direccion:  "), inputDireccion->Render()),
				hbox(text("Telefono:   "), inputTelefono->Render()),
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

		if (!convertirEntero(telefonoTexto, telefono)) {
			::system("cls");
			error = "Entrada invalida. El telefono debe ser numerico.";
			continue;
		}
		break;
	}

	aux->dato.nombre = nombre;
	aux->dato.direccion = direccion;
	aux->dato.telefono = telefono;

	::system("cls");
	mostrarMensajeCola("---- MODIFICAR CLIENTE ----", "Cliente modificado correctamente.", Color::Green);
}

void buscarCliente() {
	::system("cls");

	string idTexto, error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("---- BUSCAR CLIENTE ----") | bold | color(Color::Cyan),
				separator(),
				hbox(text("Ingrese el ID del cliente: "), inputId->Render()),
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

	NodoCliente* aux = buscarClientePorId(idBuscado);
	::system("cls");

	if (aux == NULL) {
		mostrarMensajeCola("---- BUSCAR CLIENTE ----", "No se encontro el cliente.", Color::Red);
		return;
	}

	Element doc = vbox({
		text("CLIENTE ENCONTRADO") | bold | color(Color::Cyan),
		separator(),
		text("ID:        " + to_string(aux->dato.id)),
		text("Nombre:    " + aux->dato.nombre),
		text("Direccion: " + aux->dato.direccion),
		text("Telefono:  " + to_string(aux->dato.telefono)),
		text("Direccion de memoria: " + direccionMemoriaCliente(aux)) | dim,
		}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}

void eliminarCliente() {
	::system("cls");

	if (cola.frente == NULL) {
		mostrarMensajeCola("---- ELIMINAR CLIENTE ----", "No hay clientes para eliminar.", Color::Red);
		return;
	}

	NodoCliente* aux = cola.frente;
	Cliente clienteEliminado = aux->dato;

	cola.frente = cola.frente->siguiente;
	if (cola.frente == NULL) cola.fincola = NULL;
	delete aux;
	cola.cantidad--;

	Element doc = vbox({
		text("---- ELIMINAR CLIENTE ----") | bold | color(Color::Cyan),
		separator(),
		text("Se elimino el cliente al frente de la cola:"),
		separator(),
		text("ID:        " + to_string(clienteEliminado.id)),
		text("Nombre:    " + clienteEliminado.nombre),
		text("Direccion: " + clienteEliminado.direccion),
		text("Telefono:  " + to_string(clienteEliminado.telefono)),
		text("Direccion de memoria: " + direccionMemoriaCliente(aux)) | dim,
		}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
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
