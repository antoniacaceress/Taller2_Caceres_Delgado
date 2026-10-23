#pragma once
#include <string>

class Persona {
private:
    std::string Nombre;
    int Edad;

public:
    Persona(std::string Nombre, int Edad);
    virtual ~Persona();
    std::string getNombre();
    int getEdad();
    void setNombre(std::string nuevoNombre);
    void setEdad(int nuevaEdad);
};