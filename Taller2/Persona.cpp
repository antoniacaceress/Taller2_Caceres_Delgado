#pragma once
#include "Persona.h"
#include <string>
using namespace std;

Persona::Persona(string nombre, int edad) {
    this->Nombre = nombre;
    this->Edad = edad;
}

Persona::~Persona(){}

string Persona::getNombre() {
    return this-> Nombre;
}

int Persona::getEdad() {
    return this-> Edad;
}

void Persona::setNombre(string nuevoNombre) {
    this->Nombre = nuevoNombre;
}

void Persona::setEdad(int nuevaEdad) {
    this->Edad = nuevaEdad;
}