#pragma once
#include <string>
#include "Paciente.h"
template <typename T>

class NodoPorPaciente {
    private: 
        T pacienteActual;
        NodoPorPaciente* next;  
    public:
        NodoPorPaciente(T paciente) : pacienteActual(paciente), next(nullptr) {}

        T getPaciente() {
            return this-> pacienteActual;
        }   

        NodoPorPaciente<T>* getNext(){
            return this->next;
        }

        void setPaciente(T paciente){
            this-> pacienteActual = paciente; 
        }
        void setNext(NodoPorPaciente<T>* nuevoNext) {
            this-> next = nuevoNext;
        }

        ~NodoPorPaciente() {}
};

