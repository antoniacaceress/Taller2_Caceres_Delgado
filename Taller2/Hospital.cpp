#include "Hospital.h"
#include <iostream>
#include <fstream>

Hospital::Hospital() {
    std::string nombres[8] = {
        "Urgencias", "Medicina General", "Cardiologia", "Neurologia",
        "Traumatologia", "Cirugia", "Pediatria", "Hospitalizacion"
    };

    for (int i = 0; i < 8; i++) {
        this->servicios.insertLast(new Servicio(nombres[i]));
    }
}

Hospital::~Hospital() {
    while (!this->servicios.isEmpty()) {
        delete this->servicios.getFirst();
        this->servicios.remove(0);
    }

    while (!this->pendientes.isEmpty()) {
        delete this->pendientes.front();
        this->pendientes.pop();
    }
}

Servicio* Hospital::buscarServicio(std::string nombre) {
    int total = this->servicios.size();

    for (int i = 0; i < total; i++) {
        Servicio* actual = this->servicios.get(i);
        if (actual->getNombreServicio() == nombre) {
            return actual;
        }
    }
    return nullptr;
}

bool Hospital::existeId(std::string id) {
    int totalServicios = this->servicios.size();
    std::string ruta;
    for (int i = 0; i < totalServicios; i++) {
        if (this->servicios.get(i)->getPacientes()->buscar(id, ruta) != nullptr) {
            return true;
        }
    }

    bool encontrado = false;
    int totalPendientes = this->pendientes.size();
    for (int i = 0; i < totalPendientes; i++) {
        Paciente* p = this->pendientes.front();
        this->pendientes.pop();
        if (p->getId() == id) {
            encontrado = true;
        }
        this->pendientes.push(p);
    }
    return encontrado;
}

bool Hospital::separarLinea(std::string linea, std::string campos[11]) {
    const char* p = linea.c_str();
    const char* inicioCampo = p;
    int cantidad = 0;

    while (true) {
        if (*p == ';' || *p == '\0') {
            if (cantidad == 11) {
                return false;
            }
            campos[cantidad] = std::string(inicioCampo, p - inicioCampo);
            cantidad++;
            if (*p == '\0') {
                break;
            }
            inicioCampo = p + 1;
        }
        p++;
    }
    return cantidad == 11;
}

bool Hospital::esNumero(std::string texto) {
    if (texto.empty() || texto.size() > 3) {
        return false;
    }
    int largo = texto.size();
    for (int i = 0; i < largo; i++) {
        if (texto[i] < '0' || texto[i] > '9') {
            return false;
        }
    }
    return true;
}

bool Hospital::esDecimal(std::string texto) {
    if (texto.empty() || texto.size() > 6) {
        return false;
    }
    int largo = texto.size();
    int puntos = 0;
    for (int i = 0; i < largo; i++) {
        if (texto[i] == '.') {
            puntos++;
            if (i == 0 || i == largo - 1) {
                return false;
            }
        } else if (texto[i] < '0' || texto[i] > '9') {
            return false;
        }
    }
    return puntos <= 1;
}

bool Hospital::esTipoDolorValido(std::string texto) {
    std::string tipos[5] = {"pecho", "cabeza", "abdomen", "extremidad", "otro"};
    for (int i = 0; i < 5; i++) {
        if (texto == tipos[i]) {
            return true;
        }
    }
    return false;
}

std::string Hospital::aMinusculas(std::string texto) {
    int largo = texto.size();
    for (int i = 0; i < largo; i++) {
        if (texto[i] >= 'A' && texto[i] <= 'Z') {
            texto[i] = texto[i] - 'A' + 'a';
        }
    }
    return texto;
}

bool Hospital::cargarPacientes(std::string ruta) {
    std::ifstream archivo(ruta.c_str());
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo " << ruta << std::endl;
        return false;
    }

    std::string linea;
    int numeroLinea = 0;
    int cargados = 0;
    int ignoradas = 0;

    while (std::getline(archivo, linea)) {
        numeroLinea++;

        if (!linea.empty() && linea[linea.size() - 1] == '\r') {
            linea.erase(linea.size() - 1);
        }
        if (linea.empty()) {
            continue;
        }

        std::string campos[11];
        if (!this->separarLinea(linea, campos)) {
            std::cout << "Error en la linea " << numeroLinea << ": formato incorrecto" << std::endl;
            ignoradas++;
            continue;
        }

        std::string id = campos[0];
        std::string nombre = campos[1];
        std::string tipoDolor = this->aMinusculas(campos[6]);

        if (id.empty() || nombre.empty()) {
            std::cout << "Error en la linea " << numeroLinea << ": falta el ID o el nombre" << std::endl;
            ignoradas++;
            continue;
        }
        if (id.size() != 3 || !this->esNumero(id)) {
            std::cout << "Error en la linea " << numeroLinea << ": el ID debe tener exactamente 3 digitos" << std::endl;
            ignoradas++;
            continue;
        }

        int enteros[11];
        int posiciones[7] = {2, 4, 5, 7, 8, 9, 10};
        for (int i = 0; i < 7; i++) {
            int pos = posiciones[i];
            enteros[pos] = -1;
            if (this->esNumero(campos[pos])) {
                enteros[pos] = std::stoi(campos[pos]);
            }
        }
        int edad = enteros[2];
        int presion = enteros[4];
        int dolor = enteros[5];
        int trauma = enteros[7];
        int sintomas = enteros[8];
        int cirugia = enteros[9];
        int dias = enteros[10];

        float temperatura = -1;
        if (this->esDecimal(campos[3])) {
            temperatura = std::stof(campos[3]);
        }

        std::string error = "";
        if (edad < 0 || edad > 120) {
            error = "edad incorrecta";
        } else if (temperatura < 30 || temperatura > 45) {
            error = "temperatura incorrecta";
        } else if (presion < 0 || presion > 300) {
            error = "presion arterial incorrecta";
        } else if (dolor < 0 || dolor > 10) {
            error = "dolor fuera de la escala 0 a 10";
        } else if (!this->esTipoDolorValido(tipoDolor)) {
            error = "el tipo de dolor " + campos[6] + " no existe";
        } else if ((trauma != 0 && trauma != 1) || (sintomas != 0 && sintomas != 1) || (cirugia != 0 && cirugia != 1)) {
            error = "Trauma, SintomasNeurologicos y RequiereCirugia deben ser 0 o 1";
        } else if (dias < 0 || dias > 365) {
            error = "dias de hospitalizacion incorrectos";
        } else if (this->existeId(id)) {
            error = "el ID " + id + " ya existe";
        }

        if (error != "") {
            std::cout << "Error en la linea " << numeroLinea << ": " << error << std::endl;
            ignoradas++;
            continue;
        }

        this->pendientes.push(new Paciente(nombre, edad, id, temperatura, presion, dolor, tipoDolor,
            trauma, sintomas, cirugia, dias));
        cargados++;
    }
    archivo.close();

    std::cout << "Se cargaron " << cargados << " pacientes" << std::endl;
    std::cout << "Lineas con error: " << ignoradas << std::endl;
    return true;
}

void Hospital::mostrarDatos(Paciente* paciente) {
    std::cout << "ID: " << paciente->getId() << std::endl;
    std::cout << "Nombre: " << paciente->getNombre() << std::endl;
    std::cout << "Edad: " << paciente->getEdad() << std::endl;
    std::cout << "Temperatura: " << paciente->getTemperatura() << std::endl;
    std::cout << "PresionArterial: " << paciente->getPresion() << std::endl;
    std::cout << "Dolor: " << paciente->getDolor() << std::endl;
    std::cout << "TipoDolor: " << paciente->getTipoDolor() << std::endl;
    std::cout << "Trauma: " << paciente->getTrauma() << std::endl;
    std::cout << "SintomasNeurologicos: " << paciente->getSintomas() << std::endl;
    std::cout << "RequiereCirugia: " << paciente->getRequiereCirugia() << std::endl;
    std::cout << "DiasHospitalizacion: " << paciente->getDiasHosp() << std::endl;
}

int Hospital::cantidadPendientes() {
    return this->pendientes.size();
}

void Hospital::mostrarPendientes() {
    std::cout << "=== PACIENTES EN ESPERA ===" << std::endl;
    if (this->pendientes.isEmpty()) {
        std::cout << "No hay pacientes en espera" << std::endl;
        return;
    }

    int total = this->pendientes.size();
    for (int i = 0; i < total; i++) {
        Paciente* p = this->pendientes.front();
        this->pendientes.pop();
        std::cout << (i + 1) << ". " << p->getId() << " - " << p->getNombre() << std::endl;
        this->pendientes.push(p);
    }
}

void Hospital::atenderPacientes(int cantidad) {
    if (this->pendientes.isEmpty()) {
        std::cout << "No hay pacientes en espera" << std::endl;
        return;
    }
    if (cantidad <= 0) {
        std::cout << "La cantidad debe ser mayor a 0" << std::endl;
        return;
    }
    if (cantidad > this->pendientes.size()) {
        std::cout << "Solo hay " << this->pendientes.size() << " pacientes en espera, se atenderan todos" << std::endl;
        cantidad = this->pendientes.size();
    }

    std::cout << "=== ATENDIENDO PACIENTES ===" << std::endl;
    for (int i = 0; i < cantidad; i++) {
        Paciente* p = this->pendientes.front();
        this->pendientes.pop();

        std::cout << std::endl;
        this->mostrarDatos(p);
        std::cout << std::endl;

        std::string ruta;
        std::string nombreServicio = this->arbol.obtenerServicio(p, ruta);
        std::cout << "Ruta: " << ruta << std::endl;
        std::cout << std::endl;

        Servicio* servicio = this->buscarServicio(nombreServicio);
        if (servicio == nullptr) {
            std::cout << "No se pudo asignar un servicio (" << nombreServicio << "), el paciente se descarta." << std::endl;
            delete p;
            continue;
        }

        p->setServicio(nombreServicio);
        servicio->getPacientes()->insertar(p);

        std::cout << "Servicio asignado: " << nombreServicio << std::endl;
        std::cout << "Paciente insertado en el AVL de " << nombreServicio << "." << std::endl;
    }
}

void Hospital::mostrarDepartamentos() {
    std::cout << "=== ESTADO DE LOS DEPARTAMENTOS ===" << std::endl;
    int total = this->servicios.size();
    for (int i = 0; i < total; i++) {
        Servicio* servicio = this->servicios.get(i);
        std::cout << std::endl;
        std::cout << servicio->getNombreServicio() << std::endl;
        if (servicio->getPacientes()->isEmpty()) {
            std::cout << "Sin pacientes" << std::endl;
        } else {
            std::cout << "Pacientes:" << std::endl;
            servicio->getPacientes()->mostrarInorden();
        }
    }
}

void Hospital::mostrarServicios() {
    int total = this->servicios.size();
    for (int i = 0; i < total; i++) {
        std::cout << (i + 1) << ". " << this->servicios.get(i)->getNombreServicio() << std::endl;
    }
}

void Hospital::mostrarAVL(int numero) {
    if (numero < 1 || numero > this->servicios.size()) {
        std::cout << "Opcion invalida" << std::endl;
        return;
    }

    Servicio* servicio = this->servicios.get(numero - 1);
    ArbolAVL* avl = servicio->getPacientes();
    std::cout << "=== AVL DE " << servicio->getNombreServicio() << " ===" << std::endl;
    if (avl->isEmpty()) {
        std::cout << "Sin pacientes" << std::endl;
        return;
    }

    std::cout << std::endl << "Inorden:" << std::endl;
    avl->mostrarInorden();
    std::cout << std::endl << "Preorden:" << std::endl;
    avl->mostrarPreorden();
    std::cout << std::endl << "Postorden:" << std::endl;
    avl->mostrarPostorden();
    std::cout << std::endl << "Altura del arbol: " << avl->getAltura() << std::endl;
    std::cout << std::endl << "Factor de balance:" << std::endl;
    avl->mostrarFactoresBalance();
}

void Hospital::eliminarPaciente(std::string id) {
    int totalServicios = this->servicios.size();
    std::string ruta;
    for (int i = 0; i < totalServicios; i++) {
        Servicio* servicio = this->servicios.get(i);
        if (servicio->getPacientes()->buscar(id, ruta) != nullptr) {
            servicio->getPacientes()->eliminar(id);
            std::cout << "Paciente " << id << " eliminado del AVL de " << servicio->getNombreServicio() << "." << std::endl;
            return;
        }
    }
    std::cout << "No se encontro ningun paciente atendido con el ID " << id << std::endl;
}

void Hospital::mostrarArbolDecision(int recorrido) {
    if (recorrido == 1) {
        std::cout << "=== ARBOL DE DECISION (PREORDEN) ===" << std::endl;
        this->arbol.verPreorden();
    } else if (recorrido == 2) {
        std::cout << "=== ARBOL DE DECISION (INORDEN) ===" << std::endl;
        this->arbol.verInorden();
    } else if (recorrido == 3) {
        std::cout << "=== ARBOL DE DECISION (POSTORDEN) ===" << std::endl;
        this->arbol.verPostorden();
    } else {
        std::cout << "Opcion invalida" << std::endl;
    }
}

void Hospital::buscarPaciente(std::string texto) {
    std::cout << "Buscando en AVL..." << std::endl;
    std::cout << std::endl;

    int totalServicios = this->servicios.size();
    for (int i = 0; i < totalServicios; i++) {
        Servicio* servicio = this->servicios.get(i);
        ArbolAVL* avl = servicio->getPacientes();
        std::string ruta;
        Paciente* p = avl->buscar(texto, ruta);
        if (p == nullptr) {
            p = avl->buscarPorNombre(texto);
            if (p != nullptr) {
                avl->buscar(p->getId(), ruta);
            }
        }
        if (p != nullptr) {
            std::cout << "Paciente encontrado:" << std::endl;
            std::cout << "-------" << std::endl;
            this->mostrarDatos(p);
            std::cout << "Departamento: " << servicio->getNombreServicio() << std::endl;
            std::cout << "-------" << std::endl;
            std::cout << std::endl;
            std::cout << "Ruta de busqueda:" << std::endl;
            std::cout << ruta << std::endl;
            return;
        }
    }

    Paciente* encontrado = nullptr;
    int totalPendientes = this->pendientes.size();
    for (int i = 0; i < totalPendientes; i++) {
        Paciente* p = this->pendientes.front();
        this->pendientes.pop();
        if (p->getId() == texto || p->getNombre() == texto) {
            encontrado = p;
        }
        this->pendientes.push(p);
    }

    if (encontrado != nullptr) {
        std::cout << "Paciente en espera de atencion" << std::endl;
        this->mostrarDatos(encontrado);
    } else {
        std::cout << "No se encontro ningun paciente con el ID o nombre " << texto << std::endl;
    }
}
