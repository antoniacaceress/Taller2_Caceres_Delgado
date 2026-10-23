#include "Paciente.h"
using namespace std;

Paciente::Paciente(std::string nombre, int edad, std::string id, float temp, int presion, int dolor, std::string tipoDol,
    int trauma, int sintomas, int cirugia, int dias) : Persona(nombre, edad) {
        this->ID = id;
        this->Servicio = "";
        this->Temperatura = temp;
        this->PresionArterial = presion;
        this->Dolor = dolor;
        this->TipoDolor= tipoDol;
        this->Trauma = trauma;
        this->SintomasNeurologicos = sintomas;
        this->RequiereCirugia = cirugia;
        this->DiasHospitalizacion = dias;
}

std::string Paciente::getId() {
    return this-> ID;
}

std::string Paciente::getServicio() {
    return this->Servicio;
}

void Paciente::setServicio(std::string nuevoServicio) {
    this->Servicio = nuevoServicio;
}
float Paciente::getTemperatura() {
    return this->Temperatura;
}
int Paciente::getPresion() {
    return this->PresionArterial;
}
int Paciente::getDolor() {
    return this->Dolor;
}
std::string Paciente::getTipoDolor() {
    return this->TipoDolor;
}
int Paciente::getTrauma() {
    return this->Trauma;
}
int Paciente::getSintomas() {
    return this->SintomasNeurologicos;
}
int Paciente::getRequiereCirugia() {
    return this->RequiereCirugia;
}
int Paciente::getDiasHosp() {
    return this->DiasHospitalizacion;
}

Paciente::~Paciente() {}