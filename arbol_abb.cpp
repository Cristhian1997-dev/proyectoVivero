#include "arbol_abb.h"

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

using namespace std;
using namespace ftxui;

NodoPlanta* raizPlantasABB = NULL;

static NodoABB* crearNodoABB(Planta nuevaPlanta) {
	NodoABB* nuevo = new NodoABB;
	nuevo->dato = nuevaPlanta;
	nuevo->izquierda = NULL;
	nuevo->derecha = NULL;
	return nuevo;
}

static NodoPlanta* insertarPlanta(NodoPlanta* raiz, const Planta& nueva) {
	if (raiz == nullptr) {
		return new NodoPlanta(nueva);
	}
	if (nueva.precio < raiz->dato.precio) {
		raiz->izquierdo = insertarPlanta(raiz->izquierdo, nueva);
	}
	else if (nueva.precio > raiz->dato.precio) {
		raiz->derecho = insertarPlanta(raiz->derecho, nueva);
	}
	else {
		//Si tienen el mismo precio, se desempata con el ID
		if (nueva.id < raiz->dato.id) {
			raiz->izquierdo = insertarPlanta(raiz->izquierdo, nueva);
		}
		else {
			raiz->derecho = insertarPlanta(raiz->derecho, nueva);
		}
	}
	return raiz;
}

static NodoABB* buscarNodoABB(NodoABB* raiz, int id) {
	if (raiz == NULL) {
		return NULL;
	}

	if (id == raiz->dato.id) {
		return raiz;
	}
	else if (id < raiz->dato.id) {
		return buscarNodoABB(raiz->izquierda, id);
	}
	else {
		return buscarNodoABB(raiz->derecha, id);
	}
}

//Funciones para recorrer el arbol ABB

//Funcion auxiliar para buscar planta por precio
static NodoPlanta* buscarPlantaPorPrecio(NodoPlanta* raiz, float precio) {
	if (raiz == nullptr) return nullptr;
	if (raiz->dato.precio == precio) return raiz;
	NodoPlanta* encontrado = buscarPlantaPorPrecio(raiz->izquierdo, precio);
	if (encontrado) return encontrado;
	return buscarPlantaPorPrecio(raiz->derecho, precio);
}

static NodoABB* encontrarMinimoABB(NodoABB* raiz) {
	while (raiz != NULL && raiz->izquierda != NULL) {
		raiz = raiz->izquierda;
	}
	return raiz;
}

//Funcion para encontrar el nodo con el valor minimo
static NodoPlanta* encontrarMinimoPlanta(NodoPlanta* raiz) {
	while (raiz && raiz->izquierdo) raiz = raiz->izquierdo;
	return raiz;
}

static NodoPlanta* eliminarPlanta(NodoPlanta* raiz, float precio, int idDesempate) {
	if (!raiz) {
		cout << "Planta no encontrada para eliminar." << endl;
		::system("pause");
		return nullptr;
	}
	//BUSCAR NODO
	if (precio < raiz->dato.precio) {
		raiz->izquierdo = eliminarPlanta(raiz->izquierdo, precio, idDesempate);
	}
	else if (precio > raiz->dato.precio) {
		raiz->derecho = eliminarPlanta(raiz->derecho, precio, idDesempate);
	}
	else {
		if (idDesempate != -1 && raiz->dato.id != idDesempate) {//caso 1: mismo precio pero diferente ID, seguimos buscando
			raiz->derecho = eliminarPlanta(raiz->derecho, precio, idDesempate);
			return raiz;
		}

		if (!raiz->izquierdo && !raiz->derecho) {//caso 2: nodo hoja (sin hijos)
			delete raiz;
			return nullptr;
		}
		if (!raiz->izquierdo) {//caso 3: solo hijo derecho
			NodoPlanta* tmp = raiz->derecho;
			delete raiz;
			return tmp;
		}
		if (!raiz->derecho) {//caso 4: solo hijo izquierdo
			NodoPlanta* tmp = raiz->izquierdo;
			delete raiz;
			return tmp;
		}
		//Caso 5: La raiz tiene dos hijos
		NodoPlanta* sucesor = encontrarMinimoPlanta(raiz->derecho);
		raiz->dato = sucesor->dato;
		raiz->derecho = eliminarPlanta(raiz->derecho, sucesor->dato.precio, sucesor->dato.id);
	}

	return raiz;
}

static void destruirArbol(NodoPlanta*& raiz) {//Funcion para liberar memoria del arbol
	if (raiz == nullptr) return;

	destruirArbol(raiz->izquierdo);
	destruirArbol(raiz->derecho);
	delete raiz;
	raiz = nullptr;

}

static bool convertirEnteroABB(const string& texto, int& valor) {
	try {
		size_t posicion = 0;
		valor = stoi(texto, &posicion);
		return posicion == texto.size();
	}
	catch (...) {
		return false;
	}
}

static bool convertirFloatABB(const string& texto, float& valor) {
	try {
		size_t posicion = 0;
		valor = stof(texto, &posicion);
		return posicion == texto.size();
	}
	catch (...) {
		return false;
	}
}

static string obtenerDireccionNodoABB(NodoPlanta* nodo) {
	ostringstream direccion;
	direccion << static_cast<const void*>(nodo);
	return direccion.str();
}

static string obtenerDireccionCortaABB(NodoPlanta* nodo) {
	string direccion = obtenerDireccionNodoABB(nodo);
	if (direccion.size() > 10) {
		direccion = "..." + direccion.substr(direccion.size() - 8);
	}
	return direccion;
}

static void mostrarMensajeABB(const string& titulo, const string& mensaje, Color colorMensaje = Color::Yellow) {
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

static Element crearTarjetaNodoABB(NodoPlanta* nodo, int numero) {
	Planta planta = nodo->dato;
	return vbox({
		text("Nodo " + to_string(numero)) | bold | color(Color::Green),
		separator(),
		text("ID: " + to_string(planta.id)),
		text("Nombre: " + planta.nombre),
		text("Tipo: " + planta.tipo),
		text("Color: " + planta.color),
		text("Precio: " + to_string(planta.precio)),
		text("Cantidad: " + to_string(planta.cantidad)),
		text("Dir: " + obtenerDireccionCortaABB(nodo)) | color(Color::Cyan),
	}) | border | size(WIDTH, EQUAL, 38);
}

static void mostrarNodoEncontradoABB(NodoPlanta* nodo) {
	if (nodo == nullptr) {
		mostrarMensajeABB("BUSCAR NODO ABB", "No se encontro ninguna planta con ese precio.", Color::Red);
		return;
	}

	Planta planta = nodo->dato;
	Element documento = vbox({
		text("NODO ABB ENCONTRADO") | bold | color(Color::Green),
		separator(),
		text("ID: " + to_string(planta.id)),
		text("Nombre: " + planta.nombre),
		text("Tipo: " + planta.tipo),
		text("Color: " + planta.color),
		text("Precio: " + to_string(planta.precio)),
		text("Cantidad: " + to_string(planta.cantidad)),
		text("Direccion de memoria: " + obtenerDireccionNodoABB(nodo)) | color(Color::Cyan),
	}) | border;

	::system("cls");
	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(documento));
	Render(pantalla, documento);
	pantalla.Print();
	cout << endl;
}

static void recorrerPreOrdenABBVisual(NodoPlanta* raiz, vector<NodoPlanta*>& resultado) {
	if (raiz == nullptr) {
		return;
	}
	resultado.push_back(raiz);
	recorrerPreOrdenABBVisual(raiz->izquierdo, resultado);
	recorrerPreOrdenABBVisual(raiz->derecho, resultado);
}

static void recorrerInOrdenABBVisual(NodoPlanta* raiz, vector<NodoPlanta*>& resultado) {
	if (raiz == nullptr) {
		return;
	}
	recorrerInOrdenABBVisual(raiz->izquierdo, resultado);
	resultado.push_back(raiz);
	recorrerInOrdenABBVisual(raiz->derecho, resultado);
}

static void recorrerPosOrdenABBVisual(NodoPlanta* raiz, vector<NodoPlanta*>& resultado) {
	if (raiz == nullptr) {
		return;
	}
	recorrerPosOrdenABBVisual(raiz->izquierdo, resultado);
	recorrerPosOrdenABBVisual(raiz->derecho, resultado);
	resultado.push_back(raiz);
}

static void mostrarRecorridoABBVisual(const vector<NodoPlanta*>& resultado, const string& titulo) {
	if (resultado.empty()) {
		mostrarMensajeABB(titulo, "No hay nodos para mostrar.", Color::Red);
		return;
	}

	Elements tarjetas;
	int numero = 1;
	for (NodoPlanta* nodo : resultado) {
		tarjetas.push_back(crearTarjetaNodoABB(nodo, numero));
		numero++;
	}

	int focoX = 0;
	int focoY = 0;
	auto pantalla = ScreenInteractive::Fullscreen();
	auto componente = Renderer([&] {
		Element contenido = hbox(tarjetas) | focusPosition(focoX, focoY) | frame | flex;
		return vbox({
			text(titulo) | bold | color(Color::Green),
			text("Flechas: mover vista  |  PageUp/PageDown: mover rapido  |  Enter/Esc/Q: regresar") | color(Color::Yellow),
			separator(),
			contenido,
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

struct PosicionNodoABBVisual {
	NodoPlanta* nodo;
	int x;
	int y;
};

static int alturaABBVisual(NodoPlanta* raiz) {
	if (raiz == nullptr) {
		return 0;
	}
	return 1 + max(alturaABBVisual(raiz->izquierdo), alturaABBVisual(raiz->derecho));
}

static int calcularAnchoCanvasABB(int altura) {
	const int anchoNodo = 34;
	const int margen = 40;
	const int alturaLimitada = min(altura, 12);
	int hojasEstimadas = 1;
	for (int i = 1; i < alturaLimitada; i++) {
		hojasEstimadas *= 2;
	}
	return max(160, hojasEstimadas * (anchoNodo + 22) + margen * 2);
}

static int calcularAltoCanvasABB(int altura) {
	const int margenSuperior = 8;
	const int margenInferior = 28;
	const int separacionVertical = 30;
	const int altoNodo = 22;
	return max(90, margenSuperior + altura * separacionVertical + altoNodo + margenInferior);
}

static void asignarPosicionesABB(NodoPlanta* raiz, int xCentro, int profundidad, int separacionHorizontal, vector<PosicionNodoABBVisual>& posiciones) {
	if (raiz == nullptr) {
		return;
	}

	const int anchoNodo = 34;
	const int margenSuperior = 8;
	const int separacionVertical = 30;
	const int separacionMinima = anchoNodo + 18;

	PosicionNodoABBVisual posicion;
	posicion.nodo = raiz;
	posicion.x = xCentro - anchoNodo / 2;
	posicion.y = margenSuperior + profundidad * separacionVertical;
	posiciones.push_back(posicion);

	int siguienteSeparacion = max(separacionMinima, separacionHorizontal / 2);
	asignarPosicionesABB(raiz->izquierdo, xCentro - separacionHorizontal, profundidad + 1, siguienteSeparacion, posiciones);
	asignarPosicionesABB(raiz->derecho, xCentro + separacionHorizontal, profundidad + 1, siguienteSeparacion, posiciones);
}

static void ajustarPosicionesABB(vector<PosicionNodoABBVisual>& posiciones, int& anchoCanvas) {
	if (posiciones.empty()) {
		return;
	}

	const int anchoNodo = 34;
	const int margen = 20;
	int minimoX = posiciones[0].x;
	int maximoX = posiciones[0].x + anchoNodo;

	for (const PosicionNodoABBVisual& posicion : posiciones) {
		minimoX = min(minimoX, posicion.x);
		maximoX = max(maximoX, posicion.x + anchoNodo);
	}

	if (minimoX < margen) {
		int desplazamiento = margen - minimoX;
		for (PosicionNodoABBVisual& posicion : posiciones) {
			posicion.x += desplazamiento;
		}
		maximoX += desplazamiento;
	}

	anchoCanvas = max(anchoCanvas, maximoX + margen);
}

static PosicionNodoABBVisual obtenerPosicionABB(NodoPlanta* nodo, const vector<PosicionNodoABBVisual>& posiciones) {
	for (const PosicionNodoABBVisual& posicion : posiciones) {
		if (posicion.nodo == nodo) {
			return posicion;
		}
	}
	return { nullptr, 0, 0 };
}

static void dibujarCajaNodoABB(Canvas& canvasABB, const PosicionNodoABBVisual& posicion) {
	const int ancho = 34;
	const int alto = 22;
	int x = posicion.x;
	int y = posicion.y;

	canvasABB.DrawPointLine(x, y, x + ancho, y, Color::Green);
	canvasABB.DrawPointLine(x, y + alto, x + ancho, y + alto, Color::Green);
	canvasABB.DrawPointLine(x, y, x, y + alto, Color::Green);
	canvasABB.DrawPointLine(x + ancho, y, x + ancho, y + alto, Color::Green);

	string id = "ID: " + to_string(posicion.nodo->dato.id);
	string nombre = posicion.nodo->dato.nombre;
	if (nombre.size() > 14) {
		nombre = nombre.substr(0, 14);
	}
	string direccion = "Dir:" + obtenerDireccionCortaABB(posicion.nodo);

	canvasABB.DrawText(x + 4, y + 4, id, Color::White);
	canvasABB.DrawText(x + 4, y + 9, nombre, Color::Yellow);
	canvasABB.DrawText(x + 4, y + 14, direccion, Color::Cyan);
}

static void dibujarRamasABB(Canvas& canvasABB, NodoPlanta* raiz, const vector<PosicionNodoABBVisual>& posiciones) {
	if (raiz == nullptr) {
		return;
	}

	const int ancho = 34;
	const int alto = 22;
	PosicionNodoABBVisual padre = obtenerPosicionABB(raiz, posiciones);
	int padreX = padre.x + ancho / 2;
	int padreY = padre.y + alto;

	if (raiz->izquierdo != nullptr) {
		PosicionNodoABBVisual hijo = obtenerPosicionABB(raiz->izquierdo, posiciones);
		canvasABB.DrawPointLine(padreX, padreY, hijo.x + ancho / 2, hijo.y, Color::Blue);
		dibujarRamasABB(canvasABB, raiz->izquierdo, posiciones);
	}
	if (raiz->derecho != nullptr) {
		PosicionNodoABBVisual hijo = obtenerPosicionABB(raiz->derecho, posiciones);
		canvasABB.DrawPointLine(padreX, padreY, hijo.x + ancho / 2, hijo.y, Color::Blue);
		dibujarRamasABB(canvasABB, raiz->derecho, posiciones);
	}
}

void ingresarPlantaABB() {
	::system("cls");

	string idTexto;
	string nombre;
	string tipo;
	string colorPlanta;
	string precioTexto;
	string cantidadTexto;
	string error;
	Planta nueva;

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
				text("INSERTAR NODO ABB") | bold | color(Color::Green),
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

		if (!convertirEnteroABB(idTexto, nueva.id)) {
			::system("cls");
			error = "Entrada invalida. El ID debe ser numerico.";
			continue;
		}
		if (!convertirEnteroABB(precioTexto, nueva.precio)) {
			::system("cls");
			error = "Entrada invalida. El precio debe ser numerico.";
			continue;
		}
		if (!convertirEnteroABB(cantidadTexto, nueva.cantidad)) {
			::system("cls");
			error = "Entrada invalida. La cantidad debe ser numerica.";
			continue;
		}
		break;
	}

	nueva.nombre = nombre;
	nueva.tipo = tipo;
	nueva.color = colorPlanta;
	raizPlantasABB = insertarPlanta(raizPlantasABB, nueva);
	mostrarMensajeABB("ARBOL ABB", "Nodo ABB insertado correctamente.", Color::Green);
}

void buscarPlantaABB() {
	::system("cls");

	if (raizPlantasABB == nullptr) {
		mostrarMensajeABB("BUSCAR NODO ABB", "El arbol ABB esta vacio.", Color::Red);
		return;
	}

	string precioTexto;
	string error;
	float precioBuscado = 0;

	while (true) {
		auto inputPrecio = Input(&precioTexto, "Precio");
		auto contenedor = Container::Vertical({ inputPrecio });
		auto pantalla = ScreenInteractive::TerminalOutput();

		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("BUSCAR NODO ABB") | bold | color(Color::Green),
				separator(),
				hbox(text("Precio a buscar: "), inputPrecio->Render()),
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

		if (!convertirFloatABB(precioTexto, precioBuscado)) {
			::system("cls");
			error = "Entrada invalida. El precio debe ser numerico.";
			continue;
		}
		break;
	}

	NodoPlanta* encontrado = buscarPlantaPorPrecio(raizPlantasABB, precioBuscado);
	mostrarNodoEncontradoABB(encontrado);
}

void recorrerArbolABB() {
	if (raizPlantasABB == nullptr) {
		mostrarMensajeABB("RECORRIDOS ABB", "El arbol ABB esta vacio.", Color::Red);
		return;
	}

	int op;
	string opciones[] = {
		"1. PreOrden",
		"2. InOrden",
		"3. PosOrden",
		"4. Regresar al menu ABB"
	};

	do {
		op = menuConFlecha(opciones, 4, "RECORRIDOS ABB", 3);
		vector<NodoPlanta*> resultado;

		switch (op) {
		case 1:
			recorrerPreOrdenABBVisual(raizPlantasABB, resultado);
			mostrarRecorridoABBVisual(resultado, "RECORRIDO ABB - PREORDEN");
			break;
		case 2:
			recorrerInOrdenABBVisual(raizPlantasABB, resultado);
			mostrarRecorridoABBVisual(resultado, "RECORRIDO ABB - INORDEN");
			break;
		case 3:
			recorrerPosOrdenABBVisual(raizPlantasABB, resultado);
			mostrarRecorridoABBVisual(resultado, "RECORRIDO ABB - POSORDEN");
			break;
		case 4:
			break;
		}
	} while (op != 4);
}

void eliminarPlantaABB() {
	::system("cls");

	if (raizPlantasABB == nullptr) {
		mostrarMensajeABB("ELIMINAR NODO ABB", "El arbol ABB esta vacio.", Color::Red);
		return;
	}

	string precioTexto;
	string error;
	float precioBuscado = 0;

	while (true) {
		auto inputPrecio = Input(&precioTexto, "Precio");
		auto contenedor = Container::Vertical({ inputPrecio });
		auto pantalla = ScreenInteractive::TerminalOutput();

		auto componente = Renderer(contenedor, [&] {
			Elements filas = {
				text("ELIMINAR NODO ABB") | bold | color(Color::Green),
				separator(),
				hbox(text("Precio a eliminar: "), inputPrecio->Render()),
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

		if (!convertirFloatABB(precioTexto, precioBuscado)) {
			::system("cls");
			error = "Entrada invalida. El precio debe ser numerico.";
			continue;
		}
		break;
	}

	NodoPlanta* encontrado = buscarPlantaPorPrecio(raizPlantasABB, precioBuscado);
	if (encontrado == nullptr) {
		mostrarMensajeABB("ELIMINAR NODO ABB", "No se encontro ninguna planta con ese precio.", Color::Red);
		return;
	}

	raizPlantasABB = eliminarPlanta(raizPlantasABB, precioBuscado, -1);
	mostrarMensajeABB("ELIMINAR NODO ABB", "Nodo ABB eliminado correctamente.", Color::Green);
	::system("pause");
	mostrarArbolABBVertical();
}

void mostrarArbolABBVertical() {
	::system("cls");
	if (raizPlantasABB == nullptr) {
		mostrarMensajeABB("ARBOL ABB", "El arbol ABB esta vacio.", Color::Red);
		return;
	}

	int altura = alturaABBVisual(raizPlantasABB);
	int anchoCanvas = calcularAnchoCanvasABB(altura);
	int altoCanvas = calcularAltoCanvasABB(altura);
	int separacionInicial = max(52, anchoCanvas / 4);

	vector<PosicionNodoABBVisual> posiciones;
	asignarPosicionesABB(raizPlantasABB, anchoCanvas / 2, 0, separacionInicial, posiciones);
	ajustarPosicionesABB(posiciones, anchoCanvas);

	Canvas canvasABB(anchoCanvas, altoCanvas);
	dibujarRamasABB(canvasABB, raizPlantasABB, posiciones);
	for (const PosicionNodoABBVisual& posicion : posiciones) {
		dibujarCajaNodoABB(canvasABB, posicion);
	}

	PosicionNodoABBVisual raizPosicion = obtenerPosicionABB(raizPlantasABB, posiciones);
	int focoX = raizPosicion.x + 17;
	int focoY = raizPosicion.y;
	auto pantalla = ScreenInteractive::Fullscreen();

	auto componente = Renderer([&] {
		Element vistaArbol = canvas(canvasABB) | focusPosition(focoX, focoY) | frame | flex;
		return vbox({
			text("ARBOL ABB - VISTA VERTICAL") | bold | color(Color::Green),
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
void liberarArbolABB(NodoABB*& raiz) {
	if (raiz != NULL) {
		liberarArbolABB(raiz->izquierda);
		liberarArbolABB(raiz->derecha);
		delete raiz;
		raiz = NULL;
	}

	destruirArbol(raizPlantasABB);
}