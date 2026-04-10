#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

void menuPrincipal() {
	
}


int main() {
	string nombre;
	string contra;
	string linea; // Variable temporal donde se almacenará usuario y contraseña
	string arreglo[2]; // Este arreglo servirá para separar el usuario y la contraseña
	size_t pos = 0; // Variable que contendrá la posición donde se encuentra la coma
	int contador = 0;
	string dato;
	int fin = 0;

	cout << "Bienvenidos a RAÍCES VERDES GT." << endl;
	cout << "Ingrese su usuario." << endl; cin >> nombre;
	cout << "Ingrese su contraseña." << endl; cin >> contra;

	fstream archivo("datos.txt");

	while (getline(archivo, linea) && fin == 0 ) {
		while ((pos = linea.find(",")) != string::npos) {
			dato = linea.substr(0, pos);
			arreglo[contador] = dato;
			linea.erase(0, pos + 1);
			contador++;
		}
		if (arreglo[0].find(nombre, 0) != string::npos) {
			fin = 1;
		}
		contador = 0;
	}

	if (nombre == arreglo[0] && contra == arreglo[1]) {
		menuPrincipal();
	}
	else {
		cout << "Los datos ingresados son incorrectos" << endl;
	}

	

	system("pause");
	return 0;
}