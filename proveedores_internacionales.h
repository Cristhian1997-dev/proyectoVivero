#pragma once

#include "modelos.h"

NodoDoble* crearNodoProveedorInternacional(const Proveedor& prov);
NodoDoble* buscarProveedorInternacionalPorID(ListaDoble& lista, int id);
void ingresarProveedorInternacional(ListaDoble& lista);
void ingresarProveedorInternacionalAlInicio(ListaDoble& lista);
void buscarProveedorInternacional(ListaDoble& lista);
void verProveedoresInternacionales(ListaDoble& lista);
void verReversaProveedoresInternacionales(ListaDoble& lista);
void modificarProveedorInternacional(ListaDoble& lista);
void eliminarProveedorInternacional(ListaDoble& lista);
void liberarListaDoble(ListaDoble& lista);
