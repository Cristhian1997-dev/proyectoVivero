#include "menu_ftxui.h"

#include <string>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;
using namespace std;

int menuConFlecha(string opciones[], int total, string encabezado,int startY) {
	::system("cls");
	vector<string> entradas;
	for (int i = 0; i < total; i++) {
		entradas.push_back(opciones[i]);
	}

	int seleccion = 0;
	auto menu = Menu(&entradas, &seleccion);
	auto pantalla = ScreenInteractive::TerminalOutput();

	auto componente = Renderer(menu, [&] {
		Elements filas;
		for (int i = 0; i < startY; i++) {
			filas.push_back(text(""));
		}

		filas.push_back(text(encabezado) | bold | color(Color::Green));
		filas.push_back(separator());
		filas.push_back(text("Use Flecha Arriba, Flecha Abajo y Enter."));
		filas.push_back(separator());
		filas.push_back(menu->Render() | frame);

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
	return seleccion + 1;
}
