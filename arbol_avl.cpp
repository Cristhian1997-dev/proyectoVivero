#include "arbol_avl.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "consola.h"

using namespace ftxui;
using namespace std;

static NodoAVL* raizAVL = NULL;
static void mostrarArbolAVLCanvasResaltado(NodoAVL* nodoResaltado);

static bool convertirEnteroAVL(const string& texto, int& valor) {
	try {
		size_t posicion = 0;
		valor = stoi(texto, &posicion);
		return posicion == texto.size();
	}
	catch (...) {
		return false;
	}
}

static void mostrarMensajeAVL(const string& titulo, const string& mensaje, Color colorMensaje = Color::Yellow) {
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

NodoAVL* crearNodoAVL(Planta planta) {
	NodoAVL* nuevo = new NodoAVL;
	nuevo->dato = planta;
	nuevo->izquierda = NULL;
	nuevo->derecha = NULL;
	nuevo->altura = 1;
	return nuevo;
}

int obtenerAlturaAVL(NodoAVL* nodo) {
	if (nodo == NULL) {
		return 0;
	}
	return nodo->altura;
}

int obtenerBalanceAVL(NodoAVL* nodo) {
	if (nodo == NULL) {
		return 0;
	}
	return obtenerAlturaAVL(nodo->izquierda) - obtenerAlturaAVL(nodo->derecha);
}

static void actualizarAlturaAVL(NodoAVL* nodo) {
	if (nodo != NULL) {
		nodo->altura = 1 + max(obtenerAlturaAVL(nodo->izquierda), obtenerAlturaAVL(nodo->derecha));
	}
}

NodoAVL* rotarDerechaAVL(NodoAVL* y) {
	NodoAVL* x = y->izquierda;
	NodoAVL* subarbol = x->derecha;

	x->derecha = y;
	y->izquierda = subarbol;

	actualizarAlturaAVL(y);
	actualizarAlturaAVL(x);

	return x;
}

NodoAVL* rotarIzquierdaAVL(NodoAVL* x) {
	NodoAVL* y = x->derecha;
	NodoAVL* subarbol = y->izquierda;

	y->izquierda = x;
	x->derecha = subarbol;

	actualizarAlturaAVL(x);
	actualizarAlturaAVL(y);

	return y;
}

static NodoAVL* insertarRecursivoAVL(NodoAVL* nodo, Planta planta, bool& insertado) {
	if (nodo == NULL) {
		insertado = true;
		return crearNodoAVL(planta);
	}

	if (planta.id == nodo->dato.id) {
		insertado = false;
		return nodo;
	}

	if (planta.id < nodo->dato.id) {
		nodo->izquierda = insertarRecursivoAVL(nodo->izquierda, planta, insertado);
	}
	else {
		nodo->derecha = insertarRecursivoAVL(nodo->derecha, planta, insertado);
	}

	if (!insertado) {
		return nodo;
	}

	actualizarAlturaAVL(nodo);
	int balance = obtenerBalanceAVL(nodo);

	if (balance > 1 && planta.id < nodo->izquierda->dato.id) {
		return rotarDerechaAVL(nodo);
	}

	if (balance < -1 && planta.id > nodo->derecha->dato.id) {
		return rotarIzquierdaAVL(nodo);
	}

	if (balance > 1 && planta.id > nodo->izquierda->dato.id) {
		nodo->izquierda = rotarIzquierdaAVL(nodo->izquierda);
		return rotarDerechaAVL(nodo);
	}

	if (balance < -1 && planta.id < nodo->derecha->dato.id) {
		nodo->derecha = rotarDerechaAVL(nodo->derecha);
		return rotarIzquierdaAVL(nodo);
	}

	return nodo;
}

bool insertarNodoAVL(NodoAVL*& raiz, Planta planta) {
	bool insertado = false;
	raiz = insertarRecursivoAVL(raiz, planta, insertado);
	return insertado;
}

void ingresarPlantaAVL() {
	::system("cls");

	string idTexto;
	string nombre;
	string tipo;
	string colorPlanta;
	string precioTexto;
	string cantidadTexto;
	string error;
	Planta planta;

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
				text("INSERTAR NODO AVL") | bold | color(Color::Green),
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

		if (!convertirEnteroAVL(idTexto, planta.id)) {
			::system("cls");
			error = "Entrada invalida. El ID debe ser numerico.";
			continue;
		}
		if (!convertirEnteroAVL(precioTexto, planta.precio)) {
			::system("cls");
			error = "Entrada invalida. El precio debe ser numerico.";
			continue;
		}
		if (!convertirEnteroAVL(cantidadTexto, planta.cantidad)) {
			::system("cls");
			error = "Entrada invalida. La cantidad debe ser numerica.";
			continue;
		}

		break;
	}

	planta.nombre = nombre;
	planta.tipo = tipo;
	planta.color = colorPlanta;

	if (insertarNodoAVL(raizAVL, planta)) {
		mostrarMensajeAVL("ARBOL AVL", "Nodo AVL insertado correctamente.", Color::Green);
	}
	else {
		mostrarMensajeAVL("ARBOL AVL", "ERROR: Ya existe un nodo con ese ID.", Color::Red);
	}
}


static string obtenerDireccionNodoAVL(NodoAVL* nodo) {
	ostringstream direccion;
	direccion << static_cast<const void*>(nodo);
	return direccion.str();
}

NodoAVL* buscarNodoAVL(NodoAVL* raiz, int idBuscado) {
	if (raiz == NULL) {
		return NULL;
	}

	if (idBuscado == raiz->dato.id) {
		return raiz;
	}

	if (idBuscado < raiz->dato.id) {
		return buscarNodoAVL(raiz->izquierda, idBuscado);
	}

	return buscarNodoAVL(raiz->derecha, idBuscado);
}

static void mostrarResultadoBusquedaAVL(NodoAVL* nodoEncontrado) {
	::system("cls");

	if (nodoEncontrado == NULL) {
		mostrarMensajeAVL("BUSCAR NODO AVL", "No se encontro ningun nodo con ese ID.", Color::Red);
		return;
	}

	Planta planta = nodoEncontrado->dato;
	Element documento = vbox({
		text("NODO AVL ENCONTRADO") | bold | color(Color::Green),
		separator(),
		text("ID: " + to_string(planta.id)),
		text("Nombre: " + planta.nombre),
		text("Tipo: " + planta.tipo),
		text("Color: " + planta.color),
		text("Precio: " + to_string(planta.precio)),
		text("Cantidad: " + to_string(planta.cantidad)),
		text("Direccion de memoria: " + obtenerDireccionNodoAVL(nodoEncontrado)) | color(Color::Cyan),
	}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(documento));
	Render(pantalla, documento);
	pantalla.Print();
	cout << endl;
}

void buscarAVL() {
	::system("cls");

	if (raizAVL == NULL) {
		mostrarMensajeAVL("BUSCAR NODO AVL", "El arbol AVL esta vacio.", Color::Red);
		::system("pause");
		return;
	}

	string idTexto;
	string error;
	int idBuscado = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto contenedor = Container::Vertical({ inputId });
		auto pantalla = ScreenInteractive::TerminalOutput();

		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("BUSCAR NODO AVL") | bold | color(Color::Green),
				separator(),
				hbox(text("ID a buscar: "), inputId->Render()),
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

		if (!convertirEnteroAVL(idTexto, idBuscado)) {
			::system("cls");
			error = "Entrada invalida. El ID debe ser numerico.";
			continue;
		}

		break;
	}

	NodoAVL* encontrado = buscarNodoAVL(raizAVL, idBuscado);
	mostrarResultadoBusquedaAVL(encontrado);
	::system("pause");

	if (encontrado != NULL) {
		mostrarArbolAVLCanvasResaltado(encontrado);
	}
}
void recorrerPreOrdenAVL(NodoAVL* raiz, vector<NodoAVL*>& resultado) {
	if (raiz == NULL) {
		return;
	}

	resultado.push_back(raiz);
	recorrerPreOrdenAVL(raiz->izquierda, resultado);
	recorrerPreOrdenAVL(raiz->derecha, resultado);
}

void recorrerInOrdenAVL(NodoAVL* raiz, vector<NodoAVL*>& resultado) {
	if (raiz == NULL) {
		return;
	}

	recorrerInOrdenAVL(raiz->izquierda, resultado);
	resultado.push_back(raiz);
	recorrerInOrdenAVL(raiz->derecha, resultado);
}

void recorrerPosOrdenAVL(NodoAVL* raiz, vector<NodoAVL*>& resultado) {
	if (raiz == NULL) {
		return;
	}

	recorrerPosOrdenAVL(raiz->izquierda, resultado);
	recorrerPosOrdenAVL(raiz->derecha, resultado);
	resultado.push_back(raiz);
}

static Element crearTarjetaRecorridoAVL(NodoAVL* nodo, int numero) {
	Planta planta = nodo->dato;
	string direccion = obtenerDireccionNodoAVL(nodo);
	if (direccion.size() > 14) {
		direccion = "..." + direccion.substr(direccion.size() - 10);
	}

	return vbox({
		text("Nodo " + to_string(numero)) | bold | color(Color::Green),
		separator(),
		text("ID: " + to_string(planta.id)),
		text("Nombre: " + planta.nombre),
		text("Tipo: " + planta.tipo),
		text("Color: " + planta.color),
		text("Precio: " + to_string(planta.precio)),
		text("Cantidad: " + to_string(planta.cantidad)),
		text("Dir: " + direccion) | color(Color::Cyan),
	}) | border | size(WIDTH, EQUAL, 38);
}

void mostrarRecorridoAVL(const vector<NodoAVL*>& resultado, const string& titulo) {
	::system("cls");

	if (resultado.empty()) {
		mostrarMensajeAVL(titulo, "No hay nodos para mostrar.", Color::Red);
		::system("pause");
		return;
	}

	Elements tarjetas;
	int numero = 1;
	for (NodoAVL* nodo : resultado) {
		tarjetas.push_back(crearTarjetaRecorridoAVL(nodo, numero));
		numero++;
	}

	int focoX = 0;
	int focoY = 0;
	auto pantalla = ScreenInteractive::Fullscreen();

	auto componente = Renderer([&] {
		Element tarjetasEnLinea = hbox(tarjetas) | focusPosition(focoX, focoY) | frame | flex;
		return vbox({
			text(titulo) | bold | color(Color::Green),
			text("Flechas: mover vista  |  PageUp/PageDown: mover rapido  |  Enter/Esc/Q: regresar") | color(Color::Yellow),
			separator(),
			tarjetasEnLinea,
		}) | border;
	});

	componente = CatchEvent(componente, [&](Event evento) {
		const int pasoHorizontal = 40;
		const int pasoVertical = 8;
		const int pasoPagina = 120;
		int maximoX = max(0, static_cast<int>(resultado.size()) * 42);

		if (evento == Event::Return || evento == Event::Escape || evento == Event::Character('q') || evento == Event::Character('Q')) {
			pantalla.ExitLoopClosure()();
			return true;
		}
		if (evento == Event::ArrowLeft) {
			focoX = max(0, focoX - pasoHorizontal);
			return true;
		}
		if (evento == Event::ArrowRight) {
			focoX = min(maximoX, focoX + pasoHorizontal);
			return true;
		}
		if (evento == Event::ArrowUp) {
			focoY = max(0, focoY - pasoVertical);
			return true;
		}
		if (evento == Event::ArrowDown) {
			focoY += pasoVertical;
			return true;
		}
		if (evento == Event::PageUp) {
			focoX = max(0, focoX - pasoPagina);
			return true;
		}
		if (evento == Event::PageDown) {
			focoX = min(maximoX, focoX + pasoPagina);
			return true;
		}
		return false;
	});

	pantalla.Loop(componente);
}

void menuRecorridosAVL() {
	if (raizAVL == NULL) {
		mostrarMensajeAVL("RECORRIDOS AVL", "El arbol AVL esta vacio.", Color::Red);
		::system("pause");
		return;
	}

	int op;
	string opciones[] = {
		"1. PreOrden",
		"2. InOrden",
		"3. PosOrden",
		"4. Regresar al menu AVL"
	};

	do {
		op = menuConFlecha(opciones, 4, "RECORRIDOS AVL", 3);
		vector<NodoAVL*> resultado;

		switch (op) {
		case 1:
			recorrerPreOrdenAVL(raizAVL, resultado);
			mostrarRecorridoAVL(resultado, "RECORRIDO AVL - PREORDEN");
			break;
		case 2:
			recorrerInOrdenAVL(raizAVL, resultado);
			mostrarRecorridoAVL(resultado, "RECORRIDO AVL - INORDEN");
			break;
		case 3:
			recorrerPosOrdenAVL(raizAVL, resultado);
			mostrarRecorridoAVL(resultado, "RECORRIDO AVL - POSORDEN");
			break;
		case 4:
			break;
		}
	} while (op != 4);
}
NodoAVL* encontrarMinimoAVL(NodoAVL* nodo) {
	NodoAVL* actual = nodo;
	while (actual != NULL && actual->izquierda != NULL) {
		actual = actual->izquierda;
	}
	return actual;
}

static NodoAVL* rebalancearDespuesEliminarAVL(NodoAVL* nodo) {
	if (nodo == NULL) {
		return NULL;
	}

	actualizarAlturaAVL(nodo);
	int balance = obtenerBalanceAVL(nodo);

	if (balance > 1 && obtenerBalanceAVL(nodo->izquierda) >= 0) {
		return rotarDerechaAVL(nodo);
	}

	if (balance > 1 && obtenerBalanceAVL(nodo->izquierda) < 0) {
		nodo->izquierda = rotarIzquierdaAVL(nodo->izquierda);
		return rotarDerechaAVL(nodo);
	}

	if (balance < -1 && obtenerBalanceAVL(nodo->derecha) <= 0) {
		return rotarIzquierdaAVL(nodo);
	}

	if (balance < -1 && obtenerBalanceAVL(nodo->derecha) > 0) {
		nodo->derecha = rotarDerechaAVL(nodo->derecha);
		return rotarIzquierdaAVL(nodo);
	}

	return nodo;
}

NodoAVL* eliminarNodoAVL(NodoAVL* raiz, int idEliminar, bool& eliminado) {
	if (raiz == NULL) {
		return NULL;
	}

	if (idEliminar < raiz->dato.id) {
		raiz->izquierda = eliminarNodoAVL(raiz->izquierda, idEliminar, eliminado);
	}
	else if (idEliminar > raiz->dato.id) {
		raiz->derecha = eliminarNodoAVL(raiz->derecha, idEliminar, eliminado);
	}
	else {
		eliminado = true;

		if (raiz->izquierda == NULL || raiz->derecha == NULL) {
			NodoAVL* hijo = (raiz->izquierda != NULL) ? raiz->izquierda : raiz->derecha;
			delete raiz;
			return hijo;
		}

		NodoAVL* sucesor = encontrarMinimoAVL(raiz->derecha);
		raiz->dato = sucesor->dato;
		bool sucesorEliminado = false;
		raiz->derecha = eliminarNodoAVL(raiz->derecha, sucesor->dato.id, sucesorEliminado);
	}

	return rebalancearDespuesEliminarAVL(raiz);
}

void eliminarAVL() {
	::system("cls");

	if (raizAVL == NULL) {
		mostrarMensajeAVL("ELIMINAR NODO AVL", "El arbol AVL esta vacio.", Color::Red);
		::system("pause");
		return;
	}

	string idTexto;
	string error;
	int idEliminar = 0;

	while (true) {
		auto inputId = Input(&idTexto, "ID");
		auto contenedor = Container::Vertical({ inputId });
		auto pantalla = ScreenInteractive::TerminalOutput();

		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("ELIMINAR NODO AVL") | bold | color(Color::Green),
				separator(),
				hbox(text("ID a eliminar: "), inputId->Render()),
				separator(),
				text("Presione Enter para eliminar."),
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

		if (!convertirEnteroAVL(idTexto, idEliminar)) {
			::system("cls");
			error = "Entrada invalida. El ID debe ser numerico.";
			continue;
		}

		break;
	}

	bool eliminado = false;
	raizAVL = eliminarNodoAVL(raizAVL, idEliminar, eliminado);

	if (!eliminado) {
		mostrarMensajeAVL("ELIMINAR NODO AVL", "No se encontro ningun nodo con ese ID.", Color::Red);
		::system("pause");
		return;
	}

	mostrarMensajeAVL("ELIMINAR NODO AVL", "Nodo AVL eliminado correctamente.", Color::Green);
	::system("pause");

	if (raizAVL == NULL) {
		mostrarMensajeAVL("ARBOL AVL", "El arbol AVL quedo vacio.", Color::Yellow);
		::system("pause");
		return;
	}

	mostrarArbolAVLCanvas();
}
struct PosicionNodoAVL {
	NodoAVL* nodo;
	int x;
	int y;
};

static int contarNodosAVL(NodoAVL* raiz) {
	if (raiz == NULL) {
		return 0;
	}
	return 1 + contarNodosAVL(raiz->izquierda) + contarNodosAVL(raiz->derecha);
}

static int alturaAVL(NodoAVL* raiz) {
	if (raiz == NULL) {
		return 0;
	}
	return 1 + max(alturaAVL(raiz->izquierda), alturaAVL(raiz->derecha));
}

static int calcularAnchoCanvasAVL(int altura) {
	const int anchoNodo = 34;
	const int margen = 40;
	const int alturaLimitada = min(altura, 12);
	int hojasEstimadas = 1;
	for (int i = 1; i < alturaLimitada; i++) {
		hojasEstimadas *= 2;
	}
	return max(160, hojasEstimadas * (anchoNodo + 22) + margen * 2);
}

static int calcularAltoCanvasAVL(int altura) {
	const int margenSuperior = 8;
	const int margenInferior = 28;
	const int separacionVertical = 30;
	const int altoNodo = 22;
	return max(90, margenSuperior + altura * separacionVertical + altoNodo + margenInferior);
}

static void asignarPosicionesDinamicasAVL(NodoAVL* raiz, int xCentro, int profundidad, int separacionHorizontal, vector<PosicionNodoAVL>& posiciones) {
	if (raiz == NULL) {
		return;
	}

	const int anchoNodo = 34;
	const int margenSuperior = 8;
	const int separacionVertical = 30;
	const int separacionMinima = anchoNodo + 18;

	PosicionNodoAVL posicion;
	posicion.nodo = raiz;
	posicion.x = xCentro - anchoNodo / 2;
	posicion.y = margenSuperior + profundidad * separacionVertical;
	posiciones.push_back(posicion);

	int siguienteSeparacion = max(separacionMinima, separacionHorizontal / 2);
	if (raiz->izquierda != NULL) {
		asignarPosicionesDinamicasAVL(raiz->izquierda, xCentro - separacionHorizontal, profundidad + 1, siguienteSeparacion, posiciones);
	}
	if (raiz->derecha != NULL) {
		asignarPosicionesDinamicasAVL(raiz->derecha, xCentro + separacionHorizontal, profundidad + 1, siguienteSeparacion, posiciones);
	}
}

static void ajustarPosicionesYLienzoAVL(vector<PosicionNodoAVL>& posiciones, int& anchoCanvas) {
	if (posiciones.empty()) {
		return;
	}

	const int anchoNodo = 34;
	const int margen = 20;
	int minimoX = posiciones[0].x;
	int maximoX = posiciones[0].x + anchoNodo;

	for (const PosicionNodoAVL& posicion : posiciones) {
		minimoX = min(minimoX, posicion.x);
		maximoX = max(maximoX, posicion.x + anchoNodo);
	}

	if (minimoX < margen) {
		int desplazamiento = margen - minimoX;
		for (PosicionNodoAVL& posicion : posiciones) {
			posicion.x += desplazamiento;
		}
		maximoX += desplazamiento;
	}

	anchoCanvas = max(anchoCanvas, maximoX + margen);
}

static PosicionNodoAVL obtenerPosicionAVL(NodoAVL* nodo, const vector<PosicionNodoAVL>& posiciones) {
	for (const PosicionNodoAVL& posicion : posiciones) {
		if (posicion.nodo == nodo) {
			return posicion;
		}
	}

	return { NULL, 0, 0 };
}

static void dibujarCajaNodoAVL(Canvas& canvasAVL, const PosicionNodoAVL& posicion, NodoAVL* nodoResaltado) {
	const int ancho = 34;
	const int alto = 22;
	int x = posicion.x;
	int y = posicion.y;

	Color colorBorde = (posicion.nodo == nodoResaltado) ? Color::Red : Color::Green;

	canvasAVL.DrawPointLine(x, y, x + ancho, y, colorBorde);
	canvasAVL.DrawPointLine(x, y + alto, x + ancho, y + alto, colorBorde);
	canvasAVL.DrawPointLine(x, y, x, y + alto, colorBorde);
	canvasAVL.DrawPointLine(x + ancho, y, x + ancho, y + alto, colorBorde);

	string id = "ID: " + to_string(posicion.nodo->dato.id);
	string nombre = posicion.nodo->dato.nombre;
	if (nombre.size() > 14) {
		nombre = nombre.substr(0, 14);
	}

	string direccion = obtenerDireccionNodoAVL(posicion.nodo);
	if (direccion.size() > 10) {
		direccion = "->" + direccion.substr(direccion.size() - 8);
	}
	direccion = "Dir:" + direccion;

	canvasAVL.DrawText(x + 4, y + 4, id, (posicion.nodo == nodoResaltado) ? Color::Red : Color::White);
	canvasAVL.DrawText(x + 4, y + 9, nombre, Color::Yellow);
	canvasAVL.DrawText(x + 4, y + 14, direccion, Color::Cyan);
}

static void dibujarRamasAVL(Canvas& canvasAVL, NodoAVL* raiz, const vector<PosicionNodoAVL>& posiciones) {
	if (raiz == NULL) {
		return;
	}

	const int ancho = 34;
	const int alto = 22;
	PosicionNodoAVL padre = obtenerPosicionAVL(raiz, posiciones);
	int padreX = padre.x + ancho / 2;
	int padreY = padre.y + alto;

	if (raiz->izquierda != NULL) {
		PosicionNodoAVL hijo = obtenerPosicionAVL(raiz->izquierda, posiciones);
		canvasAVL.DrawPointLine(padreX, padreY, hijo.x + ancho / 2, hijo.y, Color::Blue);
		dibujarRamasAVL(canvasAVL, raiz->izquierda, posiciones);
	}

	if (raiz->derecha != NULL) {
		PosicionNodoAVL hijo = obtenerPosicionAVL(raiz->derecha, posiciones);
		canvasAVL.DrawPointLine(padreX, padreY, hijo.x + ancho / 2, hijo.y, Color::Blue);
		dibujarRamasAVL(canvasAVL, raiz->derecha, posiciones);
	}
}

static void mostrarArbolAVLCanvasResaltado(NodoAVL* nodoResaltado) {
	::system("cls");

	if (raizAVL == NULL) {
		mostrarMensajeAVL("ARBOL AVL", "El arbol AVL esta vacio.", Color::Red);
		return;
	}

	int altura = alturaAVL(raizAVL);
	int anchoCanvas = calcularAnchoCanvasAVL(altura);
	int altoCanvas = calcularAltoCanvasAVL(altura);
	int separacionInicial = max(52, anchoCanvas / 4);

	vector<PosicionNodoAVL> posiciones;
	asignarPosicionesDinamicasAVL(raizAVL, anchoCanvas / 2, 0, separacionInicial, posiciones);
	ajustarPosicionesYLienzoAVL(posiciones, anchoCanvas);

	Canvas canvasAVL(anchoCanvas, altoCanvas);
	dibujarRamasAVL(canvasAVL, raizAVL, posiciones);
	for (const PosicionNodoAVL& posicion : posiciones) {
		dibujarCajaNodoAVL(canvasAVL, posicion, nodoResaltado);
	}

	NodoAVL* nodoFoco = (nodoResaltado != NULL) ? nodoResaltado : raizAVL;
	PosicionNodoAVL focoPosicion = obtenerPosicionAVL(nodoFoco, posiciones);
	int focoX = focoPosicion.x + 17;
	int focoY = focoPosicion.y;
	auto pantalla = ScreenInteractive::Fullscreen();

	auto componente = Renderer([&] {
		Element vistaArbol = canvas(canvasAVL) | focusPosition(focoX, focoY) | frame | flex;
		return vbox({
			text("ARBOL AVL - VISTA VERTICAL") | bold | color(Color::Green),
			text("Flechas: mover vista  |  PageUp/PageDown: subir/bajar  |  Enter/Esc/Q: salir") | color(Color::Yellow),
			separator(),
			vistaArbol,
		}) | border;
	});

	componente = CatchEvent(componente, [&](Event evento) {
		const int paso = 36;
		const int pasoPagina = 90;

		if (evento == Event::Return || evento == Event::Escape || evento == Event::Character('q') || evento == Event::Character('Q')) {
			pantalla.ExitLoopClosure()();
			return true;
		}
		if (evento == Event::ArrowLeft) {
			focoX = max(0, focoX - paso);
			return true;
		}
		if (evento == Event::ArrowRight) {
			focoX = min(anchoCanvas - 1, focoX + paso);
			return true;
		}
		if (evento == Event::ArrowUp) {
			focoY = max(0, focoY - paso);
			return true;
		}
		if (evento == Event::ArrowDown) {
			focoY = min(altoCanvas - 1, focoY + paso);
			return true;
		}
		if (evento == Event::PageUp) {
			focoY = max(0, focoY - pasoPagina);
			return true;
		}
		if (evento == Event::PageDown) {
			focoY = min(altoCanvas - 1, focoY + pasoPagina);
			return true;
		}
		return false;
	});

	pantalla.Loop(componente);
}

void mostrarArbolAVLCanvas() {
	mostrarArbolAVLCanvasResaltado(NULL);
}
void ArbolAVLPlantas() {
	int op;
	string opciones[] = {
		"1. Insertar nodo AVL",
		"2. Buscar nodo AVL",
		"3. Recorrer arbol AVL",
		"4. Eliminar nodo AVL",
		"5. Mostrar arbol AVL vertical",
		"6. Regresar al submenu de arboles"
	};

	do {
		op = menuConFlecha(opciones, 6, "MODULO DE PLANTAS - ARBOL AVL", 3);

		switch (op) {
		case 1:
			ingresarPlantaAVL();
			::system("pause");
			break;
		case 2:
			buscarAVL();
			break;
		case 3:
			menuRecorridosAVL();
			break;
		case 4:
			eliminarAVL();
			break;
		case 5:
			mostrarArbolAVLCanvas();
			::system("pause");
			break;
		case 6:
			break;
		}
	} while (op != 6);
}