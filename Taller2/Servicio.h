#pragma once
#include <string>
#include "Paciente.h"
#include "ArbolAVL.h"

class Servicio {
    private:
        std::string nombreServicio;
        ArbolAVL pacientes;

    public:
        Servicio(std::string );
        ~Servicio();

        std::string getNombreServicio();
        ArbolAVL* getPacientes();
};
