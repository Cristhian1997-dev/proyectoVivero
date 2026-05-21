#pragma once

#include <string>
#include "modelos.h"

NodoABB* crearNodoABB(Planta nuevaPlanta);
bool insertarNodoABB(NodoABB*& raiz, Planta nuevaPlanta);
NodoABB* buscarNodoABB(NodoABB* raiz, int id);
void ingresarPlantaABB();
void buscarPlantaABB();
void recorrerArbolABB();
void preOrdenABB(NodoABB* raiz, int& y);
void inOrdenABB(NodoABB* raiz, int& y);
void posOrdenABB(NodoABB* raiz, int& y);
void imprimirPlantaABB(const Planta& planta, int& y);
NodoABB* encontrarMinimoABB(NodoABB* raiz);
bool eliminarNodoABB(NodoABB*& raiz, int id);
void eliminarPlantaABB();
void mostrarArbolABBVertical();
void imprimirArbolVertical(NodoABB* raiz, int nivel, std::string rama, int& y);
void liberarArbolABB(NodoABB*& raiz);
