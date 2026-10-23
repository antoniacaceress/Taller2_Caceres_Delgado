#pragma once
#include <string>

class NodoArbol {
private:
    std::string pregunta;
    float valorNum;
    std::string valorTexto;
    std::string servicio;
    NodoArbol* si;
    NodoArbol* no;

public:
    NodoArbol(std::string pregunta, float num, std::string valText);
    NodoArbol(std::string servicio);
    ~NodoArbol();

    std::string getPregunta();
    float getValorNum();
    std::string getValorTexto();
    std::string getServicio();
    NodoArbol* getSi();
    NodoArbol* getNo();
    void setRamaSi(NodoArbol* nuevoNodo);
    void setRamaNo(NodoArbol* nuevoNsodo);
};