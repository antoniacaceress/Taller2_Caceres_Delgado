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
    Paciente(std::string nombre, int edad, std::string id, std::string servicio, float temp, int presion, int dolor, std::string tipoDol, 
    int trauma, int sintomas, int cirugia, int dias);
    std::string getId();
    void setServicio(std::string nuevoServicio);
    float getTemperatura();
    int getPresion();
    int getDolor();
    std::string getTipoDolor();
    int getTrauma();
    int getSintomas();
    int getRequiereCirugia();
    int getDiasHosp();
    ~Paciente();
};