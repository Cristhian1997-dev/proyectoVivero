#include "globales.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
NodoPlanta* cima = NULL;
Cola cola;
NodoProveedor* inicioCircular = NULL;
NodoProveedor* finCircular = NULL;
NodoSimple* cabeza = NULL;
NodoDoble* cabezaDoble = NULL;
NodoABB* raizABB = NULL;