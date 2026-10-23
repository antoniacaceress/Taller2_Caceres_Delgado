#pragma once
#include <string>
#include <iostream>
#include "Paciente.h"
#include "NodoAVL.h"

class ArbolAVL {
private:
    NodoAVL* raiz;

    int altura(NodoAVL* nodo);
    int factorBalance(NodoAVL* nodo);
    void actualizarAltura(NodoAVL* nodo);
    NodoAVL* rotacionDerecha(NodoAVL* nodo);
    NodoAVL* rotacionIzquierda(NodoAVL* nodo);
    NodoAVL* rotacionIzquierdaDerecha(NodoAVL* nodo);
    NodoAVL* rotacionDerechaIzquierda(NodoAVL* nodo);
    NodoAVL* balancear(NodoAVL* nodo);
    NodoAVL* insertar(NodoAVL* nodo, Paciente* paciente);
    NodoAVL* eliminar(NodoAVL* nodo, std::string id);
    NodoAVL* eliminarMinimo(NodoAVL* nodo);
    NodoAVL* minimo(NodoAVL* nodo);
    Paciente* buscarPorNombre(NodoAVL* nodo, std::string nombre);
    void mostrarPaciente(NodoAVL* nodo);
    void inorden(NodoAVL* nodo);
    void preorden(NodoAVL* nodo);
    void postorden(NodoAVL* nodo);
    void factores(NodoAVL* nodo);
    void vaciar(NodoAVL* nodo);

public:
    ArbolAVL();
    ~ArbolAVL();

    void insertar(Paciente* paciente);
    Paciente* buscar(std::string id, std::string& ruta);
    Paciente* buscarPorNombre(std::string nombre);
    void eliminar(std::string id);

    void mostrarInorden();
    void mostrarPreorden();
    void mostrarPostorden();
    void mostrarFactoresBalance();

    int getAltura();
    bool isEmpty();
};
