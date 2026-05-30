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
#include "proveedores_internacionales.h"

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

static void mostrarMensajeInternacional(const string& titulo, const string& mensaje, Color colorMensaje) {
	Element doc = vbox({
		text(titulo) | bold | color(Color::Magenta),
		separator(),
		text(mensaje) | color(colorMensaje),
		}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}

NodoDoble* crearNodoProveedorInternacional(const Proveedor& prov) {
	NodoDoble* nuevo = new NodoDoble();
	nuevo->dato = prov;
	nuevo->siguiente = NULL;
	nuevo->anterior = NULL;
	return nuevo;
}
NodoDoble* buscarProveedorInternacionalPorID(ListaDoble& lista, int id) { //Buscar un proveedor internacional por ID (devuelve el nodo o NULL si no se encuentra)
	NodoDoble* aux = lista.cabeza;
	while (aux != NULL) {
		if (aux->dato.id == id) {
			return aux;
		}
		aux = aux->siguiente;
	}
	return NULL;
}

void ingresarProveedorInternacional(ListaDoble& lista) {
	//Codigo para ingresar proveedores internacionales al final de la lista
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
				text("---- INGRESAR UN NUEVO PROVEEDOR INTERNACIONAL ----") | bold | color(Color::Magenta),
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
	if (buscarProveedorInternacionalPorID(lista, id) != NULL) {
		::system("cls");
		mostrarMensajeInternacional("---- INGRESAR UN NUEVO PROVEEDOR INTERNACIONAL ----", "Ya existe un proveedor con ese ID.", Color::Red);
		return;
	}

	Proveedor nuevoProv;//Variable temporal para almacenar los datos
	nuevoProv.id = id;
	nuevoProv.nombre = nombre;
	nuevoProv.tipo = tipo;
	nuevoProv.telefono = telefono;
	nuevoProv.contacto = contacto;
	NodoDoble* nuevo = crearNodoProveedorInternacional(nuevoProv);
	if (lista.cabeza == NULL) {
		//Si la lista esta vacia, el nuevo nodo se convierte en la cabeza y cola
		lista.cabeza = nuevo;
		lista.cola = nuevo;
	}
	else {
		//Si la lista no esta vacia, agregamos el nuevo nodo al final y actualizamos los punteros
		nuevo->anterior = lista.cola;
		lista.cola->siguiente = nuevo;
		lista.cola = nuevo;
	}
	::system("cls");
	mostrarMensajeInternacional("---- INGRESAR UN NUEVO PROVEEDOR INTERNACIONAL ----", "Proveedor agregado al final correctamente.", Color::Green);
}

void ingresarProveedorInternacionalAlInicio(ListaDoble& lista) {
	//Codigo para ingresar proveedores internacionales al inicio de la lista
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
				text("---- INGRESAR UN NUEVO PROVEEDOR INTERNACIONAL ----") | bold | color(Color::Magenta),
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
	if (buscarProveedorInternacionalPorID(lista, id) != NULL) {
		::system("cls");
		mostrarMensajeInternacional("---- INGRESAR UN NUEVO PROVEEDOR INTERNACIONAL ----", "Ya existe un proveedor con ese ID.", Color::Red);
		return;
	}

	Proveedor nuevoProv;//Variable temporal 
	nuevoProv.id = id;
	nuevoProv.nombre = nombre;
	nuevoProv.tipo = tipo;
	nuevoProv.telefono = telefono;
	nuevoProv.contacto = contacto;
	//Crea el nuevo nodo con los datos ingresados
	NodoDoble* nuevo = crearNodoProveedorInternacional(nuevoProv);
	if (lista.cabeza == NULL) {
		//Si la lista esta vacia, el nuevo nodo se convierte en la cabeza y cola
		lista.cabeza = nuevo;
		lista.cola = nuevo;
	}
	else {
		//Si la lista no esta vacia, agregamos el nuevo nodo al inicio y actualizamos los punteros
		nuevo->siguiente = lista.cabeza;
		lista.cabeza->anterior = nuevo;
		lista.cabeza = nuevo;
	}
	::system("cls");
	mostrarMensajeInternacional("---- INGRESAR UN NUEVO PROVEEDOR INTERNACIONAL ----", "Proveedor agregado al inicio correctamente.", Color::Green);

}

void verProveedoresInternacionales(ListaDoble& lista) {
	//Codigo para ver proveedores internacionales
	::system("cls");

	Elements filas;
	filas.push_back(text("---- PROVEEDORES INTERNACIONALES ----") | bold | color(Color::Magenta));
	filas.push_back(separator());

	if (lista.cabeza == NULL) {
		filas.push_back(text("No hay proveedores internacionales registrados.") | color(Color::Red));
	}
	else {
		NodoDoble* aux = lista.cabeza;//Apuntamos al primer nodo de la lista
		while (aux != NULL) {//Recorremos la lista hasta el final
			filas.push_back(vbox({
				text("ID:       " + to_string(aux->dato.id)),
				text("Nombre:   " + aux->dato.nombre),
				text("Tipo:     " + aux->dato.tipo),
				text("Telefono: " + to_string(aux->dato.telefono)),
				text("Contacto: " + aux->dato.contacto),
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

void verReversaProveedoresInternacionales(ListaDoble& lista) {
	//Codigo para ver proveedores internacionales en orden reverso
	::system("cls");

	Elements filas;
	filas.push_back(text("---- PROVEEDORES INTERNACIONALES ----") | bold | color(Color::Magenta));
	filas.push_back(separator());

	if (lista.cabeza == NULL) {
		filas.push_back(text("No hay proveedores internacionales registrados.") | color(Color::Red));
	}
	else {
		NodoDoble* aux = lista.cabeza;//Apuntamos al primer nodo de la lista
		while (aux != NULL) {//Recorremos la lista hasta el final
			filas.push_back(vbox({
				text("ID:       " + to_string(aux->dato.id)),
				text("Nombre:   " + aux->dato.nombre),
				text("Tipo:     " + aux->dato.tipo),
				text("Telefono: " + to_string(aux->dato.telefono)),
				text("Contacto: " + aux->dato.contacto),
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

void modificarProveedorInternacional(ListaDoble& lista) {
	//Codigo para modificar proveedores internacionales
	::system("cls");
	if (lista.cabeza == NULL) {//Validacion si la lista esta vacia
		mostrarMensajeInternacional("---- MODIFICAR PROVEEDOR INTERNACIONAL ----", "No hay proveedores registrados para modificar.", Color::Red);
		return;
	}

	string idTexto, error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("---- MODIFICAR PROVEEDOR INTERNACIONAL ----") | bold | color(Color::Magenta),
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

	NodoDoble* aux = buscarProveedorInternacionalPorID(lista, idBuscado);
	if (aux == NULL) {
		::system("cls");
		mostrarMensajeInternacional("---- MODIFICAR PROVEEDOR INTERNACIONAL ----", "No se encontro el proveedor.", Color::Red);
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
				text("---- MODIFICAR PROVEEDOR INTERNACIONAL ----") | bold | color(Color::Magenta),
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
			error = "Entrada invalida. El telefono debe ser numerico.";
			continue;
		}
		break;
	}

	aux->dato.nombre = nombre;
	aux->dato.tipo = tipo;
	aux->dato.telefono = telefono;
	aux->dato.contacto = contacto;

	::system("cls");
	mostrarMensajeInternacional("---- MODIFICAR PROVEEDOR INTERNACIONAL ----", "Proveedor modificado correctamente.", Color::Green);
}

void buscarProveedorInternacional(ListaDoble& lista) {
	//Codigo para buscar proveedores internacionales
	::system("cls");

	if (lista.cabeza == NULL) {//Verificar que la lista no este vacia
		mostrarMensajeInternacional("---- BUSCAR PROVEEDOR INTERNACIONAL ----", "No hay proveedores registrados para buscar.", Color::Red);
		return;
	}

	string idTexto, error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("---- BUSCAR PROVEEDOR INTERNACIONAL ----") | bold | color(Color::Magenta),
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

	NodoDoble* aux = buscarProveedorInternacionalPorID(lista, idBuscado);
	::system("cls");
	if (aux == NULL) {
		mostrarMensajeInternacional("---- BUSCAR PROVEEDOR INTERNACIONAL ----", "No se encontro el proveedor.", Color::Red);
		return;
	}

	Element doc = vbox({
		text("PROVEEDOR ENCONTRADO") | bold | color(Color::Magenta),
		separator(),
		text("ID:       " + to_string(aux->dato.id)),
		text("Nombre:   " + aux->dato.nombre),
		text("Tipo:     " + aux->dato.tipo),
		text("Telefono: " + to_string(aux->dato.telefono)),
		text("Contacto: " + aux->dato.contacto),
		}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}

void eliminarProveedorInternacional(ListaDoble& lista) {

	::system("cls");
	if (lista.cabeza == NULL) {//Validacion si la lista esta vacia
		mostrarMensajeInternacional("---- ELIMINAR PROVEEDOR INTERNACIONAL ----", "No hay proveedores registrados para eliminar.", Color::Red);
		return;
	}

	string idTexto, error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto pantalla = ScreenInteractive::TerminalOutput();
		auto componente = Renderer(inputId, [&] {
			Elements filas = {
				text("---- ELIMINAR PROVEEDOR INTERNACIONAL ----") | bold | color(Color::Magenta),
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

	NodoDoble* aux = buscarProveedorInternacionalPorID(lista, idBuscado);
	if (aux == NULL) {
		::system("cls");
		mostrarMensajeInternacional("---- ELIMINAR PROVEEDOR INTERNACIONAL ----", "No se encontro el proveedor.", Color::Red);
		return;
	}

	Proveedor eliminado = aux->dato;
	if (aux == lista.cabeza) {//Si el nodo a eliminar es el primero de la lista
		lista.cabeza = lista.cabeza->siguiente;//Movemos la cabeza al siguiente nodo
		if (lista.cabeza != NULL) {
			lista.cabeza->anterior = NULL;//Actualizamos el puntero anterior de la nueva cabeza
		}
		else {
			lista.cola = NULL;//Si la lista queda vacia, actualizamos la cola a NULL
		}
	}
	else if (aux == lista.cola) {//Si el nodo a eliminar es el ultimo de la lista
		lista.cola = lista.cola->anterior;//Movemos la cola al nodo anterior
		if (lista.cola != NULL) {
			lista.cola->siguiente = NULL;//Actualizamos el puntero siguiente de la nueva cola
		}
		else {
			lista.cabeza = NULL;//Si la lista queda vacia, actualizamos la cabeza a NULL
		}
	}
	else {
		aux->anterior->siguiente = aux->siguiente;//Si el nodo a eliminar esta en medio, actualizamos los punteros del nodo anterior y siguiente para saltar el nodo a eliminar
		aux->siguiente->anterior = aux->anterior;//Actualizamos el puntero anterior del nodo siguiente para saltar el nodo a eliminar
	}
	delete aux;

	::system("cls");
	Element doc = vbox({
		text("---- ELIMINAR PROVEEDOR INTERNACIONAL ----") | bold | color(Color::Magenta),
		separator(),
		text("Se elimino el siguiente proveedor:"),
		separator(),
		text("ID:       " + to_string(eliminado.id)),
		text("Nombre:   " + eliminado.nombre),
		text("Tipo:     " + eliminado.tipo),
		text("Telefono: " + to_string(eliminado.telefono)),
		text("Contacto: " + eliminado.contacto),
		}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(pantalla, doc);
	pantalla.Print();
	cout << endl;
}

void liberarListaDoble(ListaDoble& lista) {
	::system("cls");
	//Codigo para liberar memoria 
	NodoDoble* aux = lista.cabeza;//Apuntamos al primer nodo de la lista
	while (aux != NULL) {//Recorremos la lista hasta el final
		NodoDoble* temp = aux;
		aux = aux->siguiente;//Movemos el puntero al siguiente nodo antes de eliminar el nodo actual
		delete temp;//Eliminamos el nodo actual
	}
	//Actualizamos los punteros de cabeza y cola a NULL para indicar que la lista esta vacia
	lista.cabeza = NULL;
	lista.cola = NULL;
	mostrarMensajeInternacional("LISTA DOBLE", "Memoria de la lista doble de proveedores internacionales liberada correctamente.", Color::Blue);
}
