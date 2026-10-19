#pragma once
#include "Persona.h"
using namespace std;

class Paciente : public Persona {
private:
    std::string ID;
    std::string Servicio;
    float Temperatura;
    int PresionArterial;
    int Dolor;
    std::string TipoDolor;
    int Trauma;
    int SintomasNeurologicos;
    int RequiereCirugia;
    int DiasHospitalizacion;

public:
    std::string getId();
    void setServicio();
    float getTemperatura();
    int getPresion();
    int getDolor();
    std::string getTipoDolor();
    int getTrauma();
    int getSintomas();
    int getRequiereCirugia();
    int getDiasHosp();

};