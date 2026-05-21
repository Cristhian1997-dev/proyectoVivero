#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

#include "globales.h"
#include "login.h"

using namespace std;
bool login(string nombre, string contra) {
	string linea;
	string usuarioArchivo;
	string contraArchivo;
	size_t pos;

	fstream archivo("datos.txt", ios::in);

	if (!archivo) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "No se pudo abrir el archivo datos.txt" << endl;
		return false;
	}
	while (getline(archivo, linea)) {
		pos = linea.find(",");

		if (pos != string::npos) {
			usuarioArchivo = linea.substr(0, pos);
			contraArchivo = linea.substr(pos + 1);

			if (nombre == usuarioArchivo && contra == contraArchivo) {
				archivo.close();
				return true;
			}
		}
	}
	archivo.close();
	return false;
}
