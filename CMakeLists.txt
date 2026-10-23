cmake_minimum_required(VERSION 3.10)
project(Taller2_Caceres_Delgado)

set(CMAKE_CXX_STANDARD 14)

include_directories(Taller2)

configure_file(Prueba.txt Prueba.txt COPYONLY)

add_executable(Taller2_Caceres_Delgado
        Taller2/ArbolDecision.cpp
        Taller2/ArbolDecision.h
        Taller2/Cola.h
        Taller2/Hospital.cpp
        Taller2/Hospital.h
        Taller2/ListaPrincipal.h
        Taller2/main.cpp
        Taller2/Nodo.h
        Taller2/NodoArbol.cpp
        Taller2/NodoArbol.h
        Taller2/NodoPorPaciente.h
        Taller2/Paciente.cpp
        Taller2/Paciente.h
        Taller2/Persona.cpp
        Taller2/Persona.h
        Taller2/Servicio.cpp
        Taller2/Servicio.h
        Prueba.txt)
