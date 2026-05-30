#define NOMINMAX
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "consola.h"
#include "globales.h"
#include "pila_plantas.h"

using namespace ftxui;
using namespace std;

static bool convertirEntero(const string& texto, int& valor) {
	try {
		size_t posicion = 0;
		valor = stoi(texto, &posicion);
		return posicion == texto.size();
	}
	catch (...) {
		return false;
	}
}

static void mostrarMensajePila(const string& titulo, const string& mensaje, Color colorMensaje) {
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
	::system("cls");

	string idTexto;
	string nombre;
	string tipo;
	string colorPlanta;
	string precioTexto;
	string cantidadTexto;
	string error;
	int id = 0;
	int precio = 0;
	int cantidad = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto inputNombre = Input(&nombre, "Nombre");
		auto inputTipo = Input(&tipo, "Tipo");
		auto inputColor = Input(&colorPlanta, "Color");
		auto inputPrecio = Input(&precioTexto, "Precio");
		auto inputCantidad = Input(&cantidadTexto, "Cantidad");

		auto contenedor = Container::Vertical({
			inputId,
			inputNombre,
			inputTipo,
			inputColor,
			inputPrecio,
			inputCantidad,
		});

		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("INGRESAR UNA NUEVA PLANTA") | bold | color(Color::Green),
				separator(),
				hbox(text("ID:       "), inputId->Render()),
				hbox(text("Nombre:   "), inputNombre->Render()),
				hbox(text("Tipo:     "), inputTipo->Render()),
				hbox(text("Color:    "), inputColor->Render()),
				hbox(text("Precio:   "), inputPrecio->Render()),
				hbox(text("Cantidad: "), inputCantidad->Render()),
				separator(),
				text("Use Tab para moverse y Enter para guardar."),
			};

			if (!error.empty()) {
				filas.push_back(text(error) | color(Color::Red));
			}

			return vbox(filas) | border;
		});

		componente = CatchEvent(componente, [&](Event evento) {
			if (evento == Event::Return) {
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
		if (!convertirEntero(precioTexto, precio)) {
			::system("cls");
			error = "Entrada invalida. El precio debe ser numerico.";
			continue;
		}
		if (!convertirEntero(cantidadTexto, cantidad)) {
			::system("cls");
			error = "Entrada invalida. La cantidad debe ser numerica.";
			continue;
		}

		break;
	}

	if (buscarPlantaPorId(id) != NULL) {
		::system("cls");
		mostrarMensajePila("INGRESAR UNA NUEVA PLANTA", "ERROR: ID ya existe.", Color::Red);
		return;
	}

	NodoPlanta* nuevo = new NodoPlanta;
	nuevo->dato.id = id;
	nuevo->dato.nombre = nombre;
	nuevo->dato.tipo = tipo;
	nuevo->dato.color = colorPlanta;
	nuevo->dato.precio = precio;
	nuevo->dato.cantidad = cantidad;
	nuevo->siguiente = cima;
	cima = nuevo;

	::system("cls");
	mostrarMensajePila("INGRESAR UNA NUEVA PLANTA", "Planta agregada correctamente.", Color::Green);
}
void verPlantas() {
	::system("cls");

	NodoPlanta* aux = cima;
	Elements filas;
	filas.push_back(text("INVENTARIO DE PLANTAS") | bold | color(Color::Green));
	filas.push_back(separator());

	if (aux == NULL) {
		filas.push_back(text("No hay plantas registradas.") | color(Color::Red));
	}
	else {
		while (aux != NULL) {
			Element tarjeta = vbox({
				text("ID: " + to_string(aux->dato.id)),
				text("Nombre: " + aux->dato.nombre),
				text("Tipo: " + aux->dato.tipo),
				text("Color: " + aux->dato.color),
				text("Precio: " + to_string(aux->dato.precio)),
				text("Cantidad: " + to_string(aux->dato.cantidad)),
			}) | border;

			filas.push_back(tarjeta);
			aux = aux->siguiente;
		}
	}

	Element documento = vbox(filas) | border;
	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(documento));
	Render(pantalla, documento);
	pantalla.Print();
	cout << endl;
}
void modificarPlanta() {
	::system("cls");

	string idTexto;
	string error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("MODIFICAR PLANTA") | bold | color(Color::Green),
				separator(),
				hbox(text("ID de la planta: "), inputId->Render()),
				separator(),
				text("Presione Enter para buscar."),
			};

			if (!error.empty()) {
				filas.push_back(text(error) | color(Color::Red));
			}

			return vbox(filas) | border;
		});

		componente = CatchEvent(componente, [&](Event evento) {
			if (evento == Event::Return) {
				pantalla.ExitLoopClosure()();
				return true;
			}
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

	NodoPlanta* aux = buscarPlantaPorId(idBuscado);

	if (aux == NULL) {
		::system("cls");
		mostrarMensajePila("MODIFICAR PLANTA", "No se encontro la planta.", Color::Red);
		return;
	}

	string nombre = aux->dato.nombre;
	string tipo = aux->dato.tipo;
	string colorPlanta = aux->dato.color;
	string precioTexto = to_string(aux->dato.precio);
	string cantidadTexto = to_string(aux->dato.cantidad);
	int precio = aux->dato.precio;
	int cantidad = aux->dato.cantidad;
	error.clear();

	while (true) {
		::system("cls");
		auto inputNombre = Input(&nombre, "Nombre");
		auto inputTipo = Input(&tipo, "Tipo");
		auto inputColor = Input(&colorPlanta, "Color");
		auto inputPrecio = Input(&precioTexto, "Precio");
		auto inputCantidad = Input(&cantidadTexto, "Cantidad");

		auto contenedor = Container::Vertical({
			inputNombre,
			inputTipo,
			inputColor,
			inputPrecio,
			inputCantidad,
		});

		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("MODIFICAR PLANTA") | bold | color(Color::Green),
				separator(),
				text("ID: " + to_string(aux->dato.id)),
				hbox(text("Nombre:   "), inputNombre->Render()),
				hbox(text("Tipo:     "), inputTipo->Render()),
				hbox(text("Color:    "), inputColor->Render()),
				hbox(text("Precio:   "), inputPrecio->Render()),
				hbox(text("Cantidad: "), inputCantidad->Render()),
				separator(),
				text("Use Tab para moverse y Enter para guardar."),
			};

			if (!error.empty()) {
				filas.push_back(text(error) | color(Color::Red));
			}

			return vbox(filas) | border;
		});

		componente = CatchEvent(componente, [&](Event evento) {
			if (evento == Event::Return) {
				pantalla.ExitLoopClosure()();
				return true;
			}
			return false;
		});

		pantalla.Loop(componente);

		if (!convertirEntero(precioTexto, precio)) {
			::system("cls");
			error = "Entrada invalida. El precio debe ser numerico.";
			continue;
		}
		if (!convertirEntero(cantidadTexto, cantidad)) {
			::system("cls");
			error = "Entrada invalida. La cantidad debe ser numerica.";
			continue;
		}

		break;
	}

	aux->dato.nombre = nombre;
	aux->dato.tipo = tipo;
	aux->dato.color = colorPlanta;
	aux->dato.precio = precio;
	aux->dato.cantidad = cantidad;

	::system("cls");
	mostrarMensajePila("MODIFICAR PLANTA", "Planta modificada correctamente.", Color::Green);
}
void buscarPlanta() {
	::system("cls");

	string idTexto;
	string error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("BUSCAR PLANTA") | bold | color(Color::Green),
				separator(),
				hbox(text("ID de la planta: "), inputId->Render()),
				separator(),
				text("Presione Enter para buscar."),
			};

			if (!error.empty()) {
				filas.push_back(text(error) | color(Color::Red));
			}

			return vbox(filas) | border;
		});

		componente = CatchEvent(componente, [&](Event evento) {
			if (evento == Event::Return) {
				pantalla.ExitLoopClosure()();
				return true;
			}
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

	NodoPlanta* aux = buscarPlantaPorId(idBuscado);

	if (aux == NULL) {
		::system("cls");
		mostrarMensajePila("BUSCAR PLANTA", "No se encontro la planta.", Color::Red);
		return;
	}

	::system("cls");
	Element documento = vbox({
		text("PLANTA ENCONTRADA") | bold | color(Color::Green),
		separator(),
		text("ID: " + to_string(aux->dato.id)),
		text("Nombre: " + aux->dato.nombre),
		text("Tipo: " + aux->dato.tipo),
		text("Color: " + aux->dato.color),
		text("Precio: " + to_string(aux->dato.precio)),
		text("Cantidad: " + to_string(aux->dato.cantidad)),
	}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(documento));
	Render(pantalla, documento);
	pantalla.Print();
	cout << endl;
}
void eliminarPlanta() {
	::system("cls");

	if (cima == NULL) {
		::system("cls");
		mostrarMensajePila("ELIMINAR PLANTA", "No hay plantas en el inventario para eliminar.", Color::Red);
		return;
	}

	NodoPlanta* aux = cima;
	Planta plantaEliminada = aux->dato;

	cima = cima->siguiente;
	delete aux;

	::system("cls");
	Element documento = vbox({
		text("ELIMINAR PLANTA") | bold | color(Color::Green),
		separator(),
		text("Se elimino la planta en la sima de la pila:"),
		separator(),
		text("ID: " + to_string(plantaEliminada.id)),
		text("Nombre: " + plantaEliminada.nombre),
		text("Tipo: " + plantaEliminada.tipo),
		text("Color: " + plantaEliminada.color),
		text("Precio: " + to_string(plantaEliminada.precio)),
		text("Cantidad: " + to_string(plantaEliminada.cantidad)),
	}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(documento));
	Render(pantalla, documento);
	pantalla.Print();
	cout << endl;
}


void liberarPila() {
	NodoPlanta* aux;

	while (cima != NULL) {
		aux = cima;
		cima = cima->siguiente;
		delete aux;
	}
}