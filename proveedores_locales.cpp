#include <cstdlib>
#include <iostream>
#include <string>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "consola.h"
#include "globales.h"
#include "proveedores_locales.h"

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

static void mostrarMensajeLocal(const string& titulo,
	const string& mensaje,
	Color colorMensaje) {
	Element doc = vbox({
		text(titulo) | bold | color(Color::Yellow),
		separator(),
		text(mensaje) | color(colorMensaje),
		}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}
//Devolver la direccion de memoria del nodo
string direccionMemoriaProveedorLocal(NodoSimple* nodo) {
	stringstream ss;
	ss << "0x" << hex << reinterpret_cast<uintptr_t>(nodo);
	return ss.str();
}

NodoSimple* crearNodoProveedorLocal(Proveedor prov) {
	NodoSimple* nuevo = new NodoSimple;
	nuevo->dato = prov;
	nuevo->siguiente = NULL;
	return nuevo;
}
NodoSimple* buscarProveedorLocalPorId(NodoSimple* cabeza, int id) {
	NodoSimple* aux = cabeza;
	while (aux != NULL) {
		if (aux->dato.id == id) {
			return aux;
		}
		aux = aux->siguiente;
	}
	return NULL;
}
void ingresarProveedorLocalAlInicio(NodoSimple*& cabeza) {
	//Codigo para ingresar proveedores locales
	::system("cls");

	string idTexto, nombre, tipo, telefonoTexto, contacto, error;
	int id = 0, telefono = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto inputNombre = Input(&nombre, "Nombre");
		auto inputTipo = Input(&tipo, "Tipo");
		auto inputTelefono = Input(&telefonoTexto, "Telefono");
		auto inputContacto = Input(&contacto, "Contacto");

		auto contenedor = Container::Vertical({
			inputId, inputNombre, inputTipo, inputTelefono, inputContacto
			});

		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("---- INGRESAR UN NUEVO PROVEEDOR LOCAL ----") | bold | color(Color::Yellow),
				separator(),
				hbox(text("ID:        "), inputId->Render()),
				hbox(text("Nombre:    "), inputNombre->Render()),
				hbox(text("Tipo:      "), inputTipo->Render()),
				hbox(text("Telefono:  "), inputTelefono->Render()),
				hbox(text("Contacto:  "), inputContacto->Render()),
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

	//Verificar que no exista un proveedor con el mismo ID
	if (buscarProveedorLocalPorId(cabeza, id) != NULL) {
		::system("cls");
		mostrarMensajeLocal("---- INGRESAR UN NUEVO PROVEEDOR LOCAL ----", "Ya existe un proveedor con ese ID.", Color::Red);
		return;
	}

	Proveedor nuevoProv; //Variable temporal para almacenar los datos del nuevo proveedor
	nuevoProv.id = id;
	nuevoProv.nombre = nombre;
	nuevoProv.tipo = tipo;
	nuevoProv.telefono = telefono;
	nuevoProv.contacto = contacto;

	NodoSimple* nuevo = crearNodoProveedorLocal(nuevoProv);
	nuevo->siguiente = cabeza;
	cabeza = nuevo;

	::system("cls");
	mostrarMensajeLocal("---- INGRESAR UN NUEVO PROVEEDOR LOCAL ----", "Proveedor local agregado correctamente.", Color::Green);
}

void ingresarProveedorLocalAlFinal(NodoSimple*& cabeza) {
	//Codigo para ingresar proveedores locales al final de la lista
	::system("cls");

	string idTexto, nombre, tipo, telefonoTexto, contacto, error;
	int id = 0, telefono;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto inputNombre = Input(&nombre, "Nombre");
		auto inputTipo = Input(&tipo, "Tipo");
		auto inputTelefono = Input(&telefonoTexto, "Telefono");
		auto inputContacto = Input(&contacto, "Contacto");

		auto contenedor = Container::Vertical({
			inputId, inputNombre, inputTipo, inputTelefono, inputContacto
			});

		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("---- INGRESAR UN NUEVO PROVEEDOR LOCAL ----") | bold | color(Color::Yellow),
				separator(),
				hbox(text("ID:        "), inputId->Render()),
				hbox(text("Nombre:    "), inputNombre->Render()),
				hbox(text("Tipo:      "), inputTipo->Render()),
				hbox(text("Telefono:  "), inputTelefono->Render()),
				hbox(text("Contacto:  "), inputContacto->Render()),
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


	//Verificar que no exista un proveedor con el mismo ID
	if (buscarProveedorLocalPorId(cabeza, id) != NULL) {
		::system("cls");
		mostrarMensajeLocal("---- INGRESAR UN NUEVO PROVEEDOR LOCAL ----", "Ya existe un proveedor con ese ID.", Color::Red);
		return;
	}

	Proveedor nuevoProv;//Variable temporal para almacenar los datos del nuevo proveedor
	nuevoProv.id = id;
	nuevoProv.nombre = nombre;
	nuevoProv.tipo = tipo;
	nuevoProv.telefono = telefono;
	nuevoProv.contacto = contacto;

	NodoSimple* nuevo = crearNodoProveedorLocal(nuevoProv);
	if (cabeza == NULL) {
		//Si la lista esta vacia, el nuevo nodo se convierte en la cabeza
		cabeza = nuevo;
	}
	else {
		//Recorremos la lista hasta el ultimo nodo
		NodoSimple* aux = cabeza;
		while (aux->siguiente != NULL) {
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
	}

	::system("cls");
	mostrarMensajeLocal("---- INGRESAR UN NUEVO PROVEEDOR LOCAL ----", "Proveedor local agregado al final correctamente.", Color::Green);
}

void buscarProveedorLocal(NodoSimple* cabeza) {
	//Codigo para buscar proveedores locales
	::system("cls");

	string idTexto, error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("---- BUSCAR PROVEEDOR LOCAL ----") | bold | color(Color::Yellow),
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
	NodoSimple* aux = buscarProveedorLocalPorId(cabeza, idBuscado);
	::system("cls");

	if (aux == NULL) {
		mostrarMensajeLocal("---- BUSCAR PROVEEDOR LOCAL ----", "No se encontro el proveedor.", Color::Red);
		return;
	}

	Element doc = vbox({
		text("--- PROVEEDOR ENCONTRADO ---") | bold | color(Color::Yellow),
		separator(),
		text("ID:       " + to_string(aux->dato.id)),
		text("Nombre:   " + aux->dato.nombre),
		text("Tipo:     " + aux->dato.tipo),
		text("Telefono: " + to_string(aux->dato.telefono)),
		text("Contacto: " + aux->dato.contacto),
		text("Direccion de memoria: " + direccionMemoriaProveedorLocal(aux)) | dim,
		}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}

void verProveedoresLocales(NodoSimple*& cabeza) {
	//Codigo para ver proveedores locales
	::system("cls");

	Elements filas;
	filas.push_back(text("---- PROVEEDORES LOCALES ----") | bold | color(Color::Yellow));
	filas.push_back(separator());

	if (cabeza == NULL) {
		filas.push_back(text("No hay proveedores locales registrados.") | color(Color::Red));
	}
	else {
		NodoSimple* aux = cabeza;
		while (aux != NULL) {
			filas.push_back(vbox({
				text("ID:       " + to_string(aux->dato.id)),
				text("Nombre:   " + aux->dato.nombre),
				text("Tipo:     " + aux->dato.tipo),
				text("Telefono: " + to_string(aux->dato.telefono)),
				text("Contacto: " + aux->dato.contacto),
				text("Direccion de memoria: " + direccionMemoriaProveedorLocal(aux)) | dim,
				}) | border);
			aux = aux->siguiente;
		}
	}
	Element doc = vbox(filas) | border;
	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;

}

void modificarProveedorLocal(NodoSimple*& cabeza) {
	//Codigo para modificar proveedores locales
	::system("cls");

	string idTexto, error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("---- MODIFICAR PROVEEDOR LOCAL ----") | bold | color(Color::Yellow),
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

	NodoSimple* aux = buscarProveedorLocalPorId(cabeza, idBuscado);
	if (aux == NULL) {
		::system("cls");
		mostrarMensajeLocal("---- MODIFICAR PROVEEDOR LOCAL ----", "No se encontro el proveedor.", Color::Red);
		return;
	}

	string nombre = aux->dato.nombre;
	string tipo = aux->dato.tipo;
	string telefonoTexto = to_string(aux->dato.telefono);
	string contacto = aux->dato.contacto;
	int telefono = aux->dato.telefono;
	error.clear();

	while (true) {
		::system("cls");
		auto inputNombre = Input(&nombre, "Nombre");
		auto inputTipo = Input(&tipo, "Tipo");
		auto inputTelefono = Input(&telefonoTexto, "Telefono");
		auto inputContacto = Input(&contacto, "Contacto");

		auto contenedor = Container::Vertical({
			inputNombre, inputTipo, inputTelefono, inputContacto
			});

		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("---- MODIFICAR PROVEEDOR LOCAL ----") | bold | color(Color::Yellow),
				separator(),
				text("ID: " + to_string(aux->dato.id)),
				hbox(text("Nombre:    "), inputNombre->Render()),
				hbox(text("Tipo:      "), inputTipo->Render()),
				hbox(text("Telefono:  "), inputTelefono->Render()),
				hbox(text("Contacto:  "), inputContacto->Render()),
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
			error = "Entrada invelida. El telefono debe ser numerico.";
			continue;
		}
		break;
	}

	aux->dato.nombre = nombre;
	aux->dato.tipo = tipo;
	aux->dato.telefono = telefono;
	aux->dato.contacto = contacto;

	::system("cls");
	mostrarMensajeLocal("---- MODIFICAR PROVEEDOR LOCAL ----", "Proveedor modificado correctamente.", Color::Green);
}

void eliminarProveedorLocal(NodoSimple*& cabeza) {
	//Codigo para eliminar proveedores locales
	::system("cls");

	string idTexto, error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("---- ELIMINAR PROVEEDOR LOCAL ----") | bold | color(Color::Yellow),
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

	NodoSimple* aux = buscarProveedorLocalPorId(cabeza, idBuscado);
	if (aux == NULL) {
		::system("cls");
		mostrarMensajeLocal("---- ELIMINAR PROVEEDOR LOCAL ----", "No se encontro el proveedor.", Color::Red);
		return;
	}
	Proveedor eliminado = aux->dato;
	if (aux == cabeza) {//Si el nodo a eliminar es el primero de la lista
		cabeza = cabeza->siguiente;//Movemos la cabeza al siguiente nodo
	}
	else {
		NodoSimple* prev = cabeza;//Si el nodo a eliminar no es el primero, buscamos el nodo anterior a este
		while (prev->siguiente != aux) {
			prev = prev->siguiente;//Movemos el nodo anterior hasta que su siguiente sea el nodo a eliminar
		}
		prev->siguiente = aux->siguiente;
	}
	delete aux;
	::system("cls");

	Element doc = vbox({
		text("---- ELIMINAR PROVEEDOR LOCAL ----") | bold | color(Color::Yellow),
		separator(),
		text("Se elimino el siguiente proveedor:"),
		separator(),
		text("ID:       " + to_string(eliminado.id)),
		text("Nombre:   " + eliminado.nombre),
		text("Tipo:     " + eliminado.tipo),
		text("Telefono: " + to_string(eliminado.telefono)),
		text("Contacto: " + eliminado.contacto),
		text("Direccion de memoria: " + direccionMemoriaProveedorLocal(aux)) | dim,
		}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}

void liberarListaSimple(NodoSimple*& cabeza) {
	::system("cls");
	//Codigo para liberar memoria de la lista simple
	while (cabeza != NULL) {
		NodoSimple* aux = cabeza;
		cabeza = cabeza->siguiente;
		delete aux;
	}
	mostrarMensajeLocal("LISTA SIMPLE", "Memoria de la lista simple de proveedores locales liberada correctamente.", Color::Green);
}

//Funciones para la lista de proveedores internacionales (lista doblemente enlazada)