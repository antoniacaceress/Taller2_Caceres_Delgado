#pragma once
#include "Paciente.h"
template <typename T>

class Nodo {
private:
    T paciente;
    Nodo* siguiente;

public:
    Nodo(T paciente) {
        this->paciente = paciente;
        this->siguiente = nullptr;
    }

    T getPaciente() {
        return this->paciente;
    }

    Nodo<T>* getSiguiente() {
        return this->siguiente;
    }

    void setPaciente(T paciente) {
        this->paciente = paciente;
    }

    void setSiguiente(Nodo<T>* siguiente) {
        this->siguiente = siguiente;
    }

    ~Nodo(){}

};