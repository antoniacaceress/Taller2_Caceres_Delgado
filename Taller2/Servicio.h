#pragma once
#include <string>
#include "Paciente.h"
#include "ListaPrincipal.h"

class Servicio {
    private:
        std::string nombreServicio;
        ListaPrincipal<Paciente*> listaPacientes;

    public:
        Servicio(std::string );
        ~Servicio();

        std::string getNombreServicio();
        void agregarPaciente(Paciente* paciente);
        Paciente* buscarPaciente(std::string id);
        int cantidadPacientes();
        void mostrarPacientes();
};