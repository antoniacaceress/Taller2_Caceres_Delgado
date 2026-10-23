#pragma once
#include <string>
#include <iostream>
#include "Paciente.h"
#include "NodoArbol.h"

class ArbolDecision {
private:
    NodoArbol* raiz;
    void vaciarArbol(NodoArbol* nodo);
    std::string buscarDepartamento(NodoArbol* nodo, Paciente* p);
    void mostrarPreorden(NodoArbol* nodo, int nivel);

public:
    ArbolDecision();
    ~ArbolDecision();
    std::string obtenerServicio(Paciente* p);
    void verCaminos();
};