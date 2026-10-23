#pragma once
#include <string>
#include "ListaPrincipal.h"
#include "Cola.h"
#include "Paciente.h"
#include "Servicio.h"
#include "ArbolDecision.h"

class Hospital {
    private:
        ListaPrincipal<Servicio*> servicios;
        Cola<Paciente*> pendientes;
        ArbolDecision arbol;

        bool separarLinea(std::string linea, std::string campos[11]);
        bool esNumero(std::string texto);
        bool esDecimal(std::string texto);
        bool esTipoDolorValido(std::string texto);
        std::string aMinusculas(std::string texto);
        void mostrarDatos(Paciente* paciente);

    public:
        Hospital();
        ~Hospital();

        Servicio* buscarServicio(std::string nombre);
        bool existeId(std::string id);
        bool cargarPacientes(std::string ruta);

        int cantidadPendientes();
        void mostrarPendientes();
        void atenderPacientes(int cantidad);
        void mostrarDepartamentos();
        void mostrarArbolDecision(int recorrido);
        void mostrarServicios();
        void mostrarAVL(int numero);
        void eliminarPaciente(std::string id);
        void buscarPaciente(std::string texto);
};
