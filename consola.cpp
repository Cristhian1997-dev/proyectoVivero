#include <cstdlib>
#include <iostream>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "consola.h"

using namespace std;
using namespace ftxui;

void dibujo() {
	::system("cls");

	Element conejo = vbox({
		text("       (\\_//)        ") | hcenter,
		text("       ( o.o )       ") | hcenter,
		text("       / > < \\       ") | hcenter,
		text("      /       \\      ") | hcenter,
		text("     /  RAICES \\     ") | hcenter,
		text("    /   VERDES  \\    ") | hcenter,
		text("    (_____________)    ") | hcenter,
	}) | color(Color::Yellow);

	Element contenido = vbox({
		text("RAICES VERDES GT") | bold | color(Color::Green) | hcenter,
		separator(),
		conejo,
		separator(),
		text("Vivero y gestion de plantas") | color(Color::White) | hcenter,
		text("PROGRAMACION 3") | color(Color::Yellow) | hcenter,
		text("Cristhian Mucun | 2290-17-17851") | color(Color::Yellow) | hcenter,
		text("Bryan Anleu     | 2290-20-23001") | color(Color::Yellow) | hcenter,
		text("David Hernandez | 2290-24-10427 ") | color(Color::Yellow) | hcenter,
	}) | borderRounded | color(Color::Green);

	Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Fit(contenido));
	Render(pantalla, contenido | center);
	pantalla.Print();

	cout << endl;
	::system("pause");
	::system("cls");
}
