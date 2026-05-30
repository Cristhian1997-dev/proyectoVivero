#pragma once

#include "modelos.h"

#include <string>
#include <vector>

struct NodoAVL {
	Planta dato;
	NodoAVL* izquierda;
	NodoAVL* derecha;
	int altura;
};

void ArbolAVLPlantas();

NodoAVL* crearNodoAVL(Planta planta);
int obtenerAlturaAVL(NodoAVL* nodo);
int obtenerBalanceAVL(NodoAVL* nodo);
NodoAVL* rotarDerechaAVL(NodoAVL* y);
NodoAVL* rotarIzquierdaAVL(NodoAVL* x);
bool insertarNodoAVL(NodoAVL*& raiz, Planta planta);
void ingresarPlantaAVL();
NodoAVL* buscarNodoAVL(NodoAVL* raiz, int idBuscado);
void buscarAVL();
void recorrerPreOrdenAVL(NodoAVL* raiz, std::vector<NodoAVL*>& resultado);
void recorrerInOrdenAVL(NodoAVL* raiz, std::vector<NodoAVL*>& resultado);
void recorrerPosOrdenAVL(NodoAVL* raiz, std::vector<NodoAVL*>& resultado);
void mostrarRecorridoAVL(const std::vector<NodoAVL*>& resultado, const std::string& titulo);
void menuRecorridosAVL();
NodoAVL* encontrarMinimoAVL(NodoAVL* nodo);
NodoAVL* eliminarNodoAVL(NodoAVL* raiz, int idEliminar, bool& eliminado);
void eliminarAVL();
void mostrarArbolAVLCanvas();