#include "NodoAVL.h"

NodoAVL::NodoAVL(Paciente* paciente) {
    this->paciente = paciente;
    this->izquierdo = nullptr;
    this->derecho = nullptr;
    this->altura = 1;
}

NodoAVL::~NodoAVL() {}

Paciente* NodoAVL::getPaciente() {
    return this->paciente;
}

NodoAVL* NodoAVL::getIzquierdo() {
    return this->izquierdo;
}

NodoAVL* NodoAVL::getDerecho() {
    return this->derecho;
}

int NodoAVL::getAltura() {
    return this->altura;
}

void NodoAVL::setPaciente(Paciente* nuevoPaciente) {
    this->paciente = nuevoPaciente;
}

void NodoAVL::setIzquierdo(NodoAVL* nuevoNodo) {
    this->izquierdo = nuevoNodo;
}

void NodoAVL::setDerecho(NodoAVL* nuevoNodo) {
    this->derecho = nuevoNodo;
}

void NodoAVL::setAltura(int nuevaAltura) {
    this->altura = nuevaAltura;
}
