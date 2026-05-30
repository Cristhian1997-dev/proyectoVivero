#include <cstdlib>
#include <iostream>
#include <string>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include "arbol_abb.h"
#include "cola_clientes.h"
#include "consola.h"
#include "globales.h"
#include "login.h"
#include "menu.h"
#include "pila_plantas.h"
#include "proveedores_circular.h"

using namespace ftxui;
using namespace std;
int main() {
    dibujo();
    string nombre;
    string contra;
    string error;
    bool salir = false;

    auto pantalla = ScreenInteractive::TerminalOutput();
    auto inputNombre = Input(&nombre, "Usuario");

    InputOption opcionContra;
    opcionContra.password = true;
    auto inputContra = Input(&contra, "Contraseña", opcionContra);

    auto contenedor = Container::Vertical({ inputNombre, inputContra });

    auto componente = Renderer(contenedor, [&] {
        Elements filas = {
            text("Bienvenidos a RAICES VERDES GT.") | bold | color(Color::Cyan) | hcenter,
            separator(),
            hbox(text("Ingrese su usuario:    "), inputNombre->Render()),
            hbox(text("Ingrese su contrasena: "), inputContra->Render()),
        };

        if (!error.empty())
            filas.push_back(text(error) | color(Color::Red));

        return vbox(filas) | border;
        });

    componente = CatchEvent(componente, [&](Event e) {
        if (e == Event::Return) {
            if (login(nombre, contra)) {
                salir = true;
                pantalla.ExitLoopClosure()();
            }
            else {
                error = "Los datos ingresados son incorrectos.";
                contra = "";
            }
            return true;
        }
        return false;
        });

    pantalla.Loop(componente);

    if (salir) {
        menuPrincipal();
    }

    liberarPila();
    liberarCola();
    liberarListaCircular();
    liberarArbolABB(raizABB);

    system("pause");
    return 0;
}