#pragma once

#include "modelos.h"

NodoSimple* crearNodoProveedorLocal(Proveedor prov);
NodoSimple* buscarProveedorLocalPorId(NodoSimple* cabeza, int id);
void ingresarProveedorLocalAlInicio(NodoSimple*& cabeza);
void ingresarProveedorLocalAlFinal(NodoSimple*& cabeza);
void buscarProveedorLocal(NodoSimple* cabeza);
void verProveedoresLocales(NodoSimple*& cabeza);
void modificarProveedorLocal(NodoSimple*& cabeza);
void eliminarProveedorLocal(NodoSimple*& cabeza);
void liberarListaSimple(NodoSimple*& cabeza);
