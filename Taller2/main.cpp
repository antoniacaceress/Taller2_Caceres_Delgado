#include <iostream>
#include <string>
#include "Hospital.h"
using namespace std;

int leerNumero() {
    int numero;
    while (!(cin >> numero)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ingrese un numero valido: ";
    }
    return numero;
}

void menuPrincipal(Hospital& hospital) {
    int opcion = 0;
    while (opcion != 4) {
        cout << endl;
        cout << "=== HOSPITAL MARMAJA ===" << endl;
        cout << "1. Atender pacientes" << endl;
        cout << "2. Ver departamentos" << endl;
        cout << "3. Buscar paciente" << endl;
        cout << "4. Salir" << endl;
        cout << "5. Ver arbol de decision" << endl;
        cout << "Seleccionar opcion: ";
        opcion = leerNumero();
        cout << endl;

        if (opcion == 1) {
            hospital.mostrarPendientes();
            if (hospital.cantidadPendientes() > 0) {
                cout << endl;
                cout << "Indique la cantidad de pacientes a atender: ";
                int cantidad = leerNumero();
                cout << endl;
                hospital.atenderPacientes(cantidad);
            }
        } else if (opcion == 2) {
            hospital.mostrarDepartamentos();
        } else if (opcion == 3) {
            cout << "=== BUSCAR PACIENTE ===" << endl;
            cout << endl;
            cout << "Indique el ID o Nombre del paciente: ";
            string texto;
            cin.ignore(1000, '\n');
            getline(cin, texto);
            cout << endl;
            hospital.buscarPaciente(texto);
        } else if (opcion == 4) {
            cout << "Hasta luego :D." << endl;
        } else if (opcion == 5) {
            cout << "1. Preorden" << endl;
            cout << "2. Inorden" << endl;
            cout << "3. Postorden" << endl;
            cout << "Seleccionar recorrido: ";
            int recorrido = leerNumero();
            cout << endl;
            hospital.mostrarArbolDecision(recorrido);
        } else {
            cout << "Opcion invalida" << endl;
        }
    }
}

int main() {
    Hospital hospital;
    if (!hospital.cargarPacientes("Prueba.txt")) {
        return 1;
    }

    menuPrincipal(hospital);
    return 0;
}
