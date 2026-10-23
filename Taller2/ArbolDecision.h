#pragma once
#include <string>
#include <iostream>
#include "Paciente.h"
#include "NodoArbol.h"

class ArbolDecision {
private:
    NodoArbol* raiz;
    void vaciarArbol(NodoArbol* nodo);
    std::string buscarDepartamento(NodoArbol* nodo, Paciente* p, std::string& ruta);
    std::string operador(NodoArbol* nodo, bool cumple);
    std::string condicion(NodoArbol* nodo, bool cumple);
    void mostrarNodo(NodoArbol* nodo, int nivel);
    void mostrarPreorden(NodoArbol* nodo, int nivel);
    void mostrarInorden(NodoArbol* nodo, int nivel);
    void mostrarPostorden(NodoArbol* nodo, int nivel);

public:
    ArbolDecision();
    ~ArbolDecision();
    std::string obtenerServicio(Paciente* p, std::string& ruta);
    void verPreorden();
    void verInorden();
    void verPostorden();
};
