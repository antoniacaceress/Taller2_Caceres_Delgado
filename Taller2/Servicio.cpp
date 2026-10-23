#include "Servicio.h"
#include <iostream>

Servicio::Servicio(std::string nombreServ) {
    this->nombreServicio = nombreServ;
}

Servicio::~Servicio() {
    while (!this->listaPacientes.isEmpty()) {
        Paciente* p = this->listaPacientes.getFirst();
        delete p;
        this->listaPacientes.remove(0);
    }
}

std::string Servicio::getNombreServicio() {
    return this->nombreServicio;
}

void Servicio::agregarPaciente(Paciente* paciente) {
    this->listaPacientes.insertLast(paciente);
}

Paciente* Servicio::buscarPaciente(std::string id) {
    int total = this->listaPacientes.size();
    for (int i = 0; i < total; i++) {
        Paciente* p = this->listaPacientes.get(i);
        if (p->getId() == id) {
            return p;
        }
    }
    return nullptr;
}

int Servicio::cantidadPacientes() {
    return this->listaPacientes.size();
}

void Servicio::mostrarPacientes() {
    int total = this->cantidadPacientes();
    std::cout << "Pacientes en el departamento de " << this->nombreServicio << ": " << total << std::endl;

    for (int i = 0; i < total; i++) {
        Paciente* p = this->listaPacientes.get(i);
        std::cout << p->getNombre() << " (" << p->getEdad() << ")" << std::endl;
    }
}