#include "menu_arboles.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "arbol_abb.h"
#include "arbol_avl.h"
#include "consola.h"

using namespace ftxui;
using namespace std;

static void mostrarMensajeArboles(const string& titulo, const string& mensaje) {
	::system("cls");
	Element documento = vbox({
		text(titulo) | bold | color(Color::Green),
		separator(),
		text(mensaje) | color(Color::Yellow),
	}) | border;

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(documento));
	Render(pantalla, documento);
	pantalla.Print();
	cout << endl;
}

void MenuArbolesBinarios() {
	int op;
	string opciones[] = {
		"1. Arbol ABB",
		"2. Arbol AVL",
		"3. Regresar al menu principal"
	};

	do {
		op = menuConFlecha(opciones, 3, "ARBOLES BINARIOS DE BUSQUEDA", 3);

		switch (op) {
		case 1:
			ArbolABBPlantas();
			break;
		case 2:
			ArbolAVLPlantas();
			break;
		case 3:
			break;
		}
	} while (op != 3);
}
