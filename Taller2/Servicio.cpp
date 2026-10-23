#include "Servicio.h"

Servicio::Servicio(std::string nombreServ) {
    this->nombreServicio = nombreServ;
}

Servicio::~Servicio() {}

std::string Servicio::getNombreServicio() {
    return this->nombreServicio;
}

ArbolAVL* Servicio::getPacientes() {
    return &this->pacientes;
}
