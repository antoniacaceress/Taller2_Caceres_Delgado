#include "NodoArbol.h"

NodoArbol::NodoArbol(std::string pregunta, float num, std::string valText) {
    this->pregunta = pregunta;
    this->valorNum = num;
    this->valorTexto = valText;
    this->servicio = "";
    this->si = nullptr;
    this->no = nullptr;
}

NodoArbol::NodoArbol(std::string servicio) {
    this->pregunta = "Hoja";
    this->valorNum = 0;
    this->valorTexto = "";
    this->servicio = servicio;
    this->si = nullptr;
    this->no = nullptr;
}

NodoArbol::~NodoArbol() {}

std::string NodoArbol::getPregunta() {
    return this->pregunta;
}

float NodoArbol::getValorNum() {
    return this->valorNum;
}

std::string NodoArbol::getValorTexto() {
    return this->valorTexto;
}

std::string NodoArbol::getServicio() {
    return this->servicio;
}

NodoArbol* NodoArbol::getSi() {
    return this->si;
}

NodoArbol* NodoArbol::getNo() {
    return this->no;
}

void NodoArbol::setRamaSi(NodoArbol* nuevoNodo) {
    this->si = nuevoNodo;
}

void NodoArbol::setRamaNo(NodoArbol* nuevoNodo) {
    this->no = nuevoNodo;
}
     