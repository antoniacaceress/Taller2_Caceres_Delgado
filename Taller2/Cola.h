#pragma once 
#include <iostream>
#include <string>
#include "Nodo.h"
template <typename T>

class Cola {
private: 
    Nodo<T>* inicio;
    Nodo<T>* final;
    int contador;

public:
    Cola() {
        this->inicio = nullptr;
        this->final = nullptr;
        this->contador = 0;
        }

    bool isEmpty() {
        bool verificador = false;
        if (this-> inicio == nullptr) {
                verificador = true;
        }
        return verificador;
    }

    void push(T paciente) {
        Nodo<T>* nuevoPaciente = new Nodo<T>(paciente);

        if (isEmpty()) {
            this->inicio = nuevoPaciente;
            this->final = nuevoPaciente;
        } else {
            this->final->setSiguiente(nuevoPaciente);
            this->final = nuevoPaciente;
        }
        contador++;
    } 

    void pop() {
        if (isEmpty()) {
            std::cout << "La fila esta vacia" << std::endl;
            return;
        }

        Nodo<T>* datoInicial = this-> inicio;
        Nodo<T>* siguiente = datoInicial->getSiguiente();
        this->inicio = siguiente;

        if (siguiente==nullptr) {
            this-> final = nullptr;
        }

        delete datoInicial;
        this-> contador--;
    }

    T front() {
        if (isEmpty()) throw 0;
        return this->inicio->getPaciente();
    }

    int size() {
        return this-> contador;
    }

    void clear() {
        while (!this->isEmpty()) {
            this->pop();
        }
    }

    ~Cola() {
        this->clear();
    }


};
