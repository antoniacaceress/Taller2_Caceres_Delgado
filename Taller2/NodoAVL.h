#pragma once
#include "Paciente.h"

class NodoAVL {
private:
    Paciente* paciente;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

public:
    NodoAVL(Paciente* paciente);
    ~NodoAVL();

    Paciente* getPaciente();
    NodoAVL* getIzquierdo();
    NodoAVL* getDerecho();
    int getAltura();
    void setPaciente(Paciente* nuevoPaciente);
    void setIzquierdo(NodoAVL* nuevoNodo);
    void setDerecho(NodoAVL* nuevoNodo);
    void setAltura(int nuevaAltura);
};
