#include "ArbolAVL.h"

ArbolAVL::ArbolAVL() {
    this->raiz = nullptr;
}

ArbolAVL::~ArbolAVL() {
    this->vaciar(this->raiz);
}

void ArbolAVL::vaciar(NodoAVL* nodo) {
    if (nodo != nullptr) {
        this->vaciar(nodo->getIzquierdo());
        this->vaciar(nodo->getDerecho());
        delete nodo->getPaciente();
        delete nodo;
    }
}

int ArbolAVL::altura(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->getAltura();
}

int ArbolAVL::factorBalance(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return this->altura(nodo->getIzquierdo()) - this->altura(nodo->getDerecho());
}

void ArbolAVL::actualizarAltura(NodoAVL* nodo) {
    int alturaIzquierda = this->altura(nodo->getIzquierdo());
    int alturaDerecha = this->altura(nodo->getDerecho());
    if (alturaIzquierda > alturaDerecha) {
        nodo->setAltura(alturaIzquierda + 1);
    } else {
        nodo->setAltura(alturaDerecha + 1);
    }
}

NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->getIzquierdo();
    NodoAVL* subarbol = nuevaRaiz->getDerecho();

    nuevaRaiz->setDerecho(nodo);
    nodo->setIzquierdo(subarbol);

    this->actualizarAltura(nodo);
    this->actualizarAltura(nuevaRaiz);
    return nuevaRaiz;
}

NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->getDerecho();
    NodoAVL* subarbol = nuevaRaiz->getIzquierdo();

    nuevaRaiz->setIzquierdo(nodo);
    nodo->setDerecho(subarbol);

    this->actualizarAltura(nodo);
    this->actualizarAltura(nuevaRaiz);
    return nuevaRaiz;
}

NodoAVL* ArbolAVL::rotacionIzquierdaDerecha(NodoAVL* nodo) {
    nodo->setIzquierdo(this->rotacionIzquierda(nodo->getIzquierdo()));
    return this->rotacionDerecha(nodo);
}

NodoAVL* ArbolAVL::rotacionDerechaIzquierda(NodoAVL* nodo) {
    nodo->setDerecho(this->rotacionDerecha(nodo->getDerecho()));
    return this->rotacionIzquierda(nodo);
}

NodoAVL* ArbolAVL::balancear(NodoAVL* nodo) {
    this->actualizarAltura(nodo);
    int balance = this->factorBalance(nodo);

    if (balance > 1) {
        if (this->factorBalance(nodo->getIzquierdo()) >= 0) {
            return this->rotacionDerecha(nodo);
        }
        return this->rotacionIzquierdaDerecha(nodo);
    }

    if (balance < -1) {
        if (this->factorBalance(nodo->getDerecho()) <= 0) {
            return this->rotacionIzquierda(nodo);
        }
        return this->rotacionDerechaIzquierda(nodo);
    }

    return nodo;
}

void ArbolAVL::insertar(Paciente* paciente) {
    this->raiz = this->insertar(this->raiz, paciente);
}

NodoAVL* ArbolAVL::insertar(NodoAVL* nodo, Paciente* paciente) {
    if (nodo == nullptr) {
        return new NodoAVL(paciente);
    }

    std::string id = paciente->getId();
    std::string idNodo = nodo->getPaciente()->getId();

    if (id < idNodo) {
        nodo->setIzquierdo(this->insertar(nodo->getIzquierdo(), paciente));
    } else if (id > idNodo) {
        nodo->setDerecho(this->insertar(nodo->getDerecho(), paciente));
    } else {
        return nodo;
    }

    return this->balancear(nodo);
}

Paciente* ArbolAVL::buscar(std::string id, std::string& ruta) {
    ruta = "";
    NodoAVL* actual = this->raiz;

    while (actual != nullptr) {
        std::string idActual = actual->getPaciente()->getId();
        if (ruta != "") {
            ruta += " -> ";
        }
        ruta += idActual;

        if (id == idActual) {
            return actual->getPaciente();
        }
        if (id < idActual) {
            actual = actual->getIzquierdo();
        } else {
            actual = actual->getDerecho();
        }
    }
    return nullptr;
}

Paciente* ArbolAVL::buscarPorNombre(std::string nombre) {
    return this->buscarPorNombre(this->raiz, nombre);
}

Paciente* ArbolAVL::buscarPorNombre(NodoAVL* nodo, std::string nombre) {
    if (nodo == nullptr) {
        return nullptr;
    }

    Paciente* encontrado = this->buscarPorNombre(nodo->getIzquierdo(), nombre);
    if (encontrado != nullptr) {
        return encontrado;
    }
    if (nodo->getPaciente()->getNombre() == nombre) {
        return nodo->getPaciente();
    }
    return this->buscarPorNombre(nodo->getDerecho(), nombre);
}

void ArbolAVL::eliminar(std::string id) {
    this->raiz = this->eliminar(this->raiz, id);
}

NodoAVL* ArbolAVL::eliminar(NodoAVL* nodo, std::string id) {
    if (nodo == nullptr) {
        return nullptr;
    }

    std::string idNodo = nodo->getPaciente()->getId();

    if (id < idNodo) {
        nodo->setIzquierdo(this->eliminar(nodo->getIzquierdo(), id));
    } else if (id > idNodo) {
        nodo->setDerecho(this->eliminar(nodo->getDerecho(), id));
    } else {
        if (nodo->getIzquierdo() == nullptr || nodo->getDerecho() == nullptr) {
            NodoAVL* hijo = nodo->getIzquierdo();
            if (hijo == nullptr) {
                hijo = nodo->getDerecho();
            }
            delete nodo->getPaciente();
            delete nodo;
            return hijo;
        }

        Paciente* pacienteEliminado = nodo->getPaciente();
        NodoAVL* sucesor = this->minimo(nodo->getDerecho());
        nodo->setPaciente(sucesor->getPaciente());
        nodo->setDerecho(this->eliminarMinimo(nodo->getDerecho()));
        delete pacienteEliminado;
    }

    return this->balancear(nodo);
}

NodoAVL* ArbolAVL::eliminarMinimo(NodoAVL* nodo) {
    if (nodo->getIzquierdo() == nullptr) {
        NodoAVL* derecho = nodo->getDerecho();
        delete nodo;
        return derecho;
    }
    nodo->setIzquierdo(this->eliminarMinimo(nodo->getIzquierdo()));
    return this->balancear(nodo);
}

NodoAVL* ArbolAVL::minimo(NodoAVL* nodo) {
    NodoAVL* actual = nodo;
    while (actual->getIzquierdo() != nullptr) {
        actual = actual->getIzquierdo();
    }
    return actual;
}

void ArbolAVL::mostrarPaciente(NodoAVL* nodo) {
    std::cout << nodo->getPaciente()->getId() << " - " << nodo->getPaciente()->getNombre() << std::endl;
}

void ArbolAVL::mostrarInorden() {
    this->inorden(this->raiz);
}

void ArbolAVL::mostrarPreorden() {
    this->preorden(this->raiz);
}

void ArbolAVL::mostrarPostorden() {
    this->postorden(this->raiz);
}

void ArbolAVL::inorden(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }
    this->inorden(nodo->getIzquierdo());
    this->mostrarPaciente(nodo);
    this->inorden(nodo->getDerecho());
}

void ArbolAVL::preorden(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }
    this->mostrarPaciente(nodo);
    this->preorden(nodo->getIzquierdo());
    this->preorden(nodo->getDerecho());
}

void ArbolAVL::postorden(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }
    this->postorden(nodo->getIzquierdo());
    this->postorden(nodo->getDerecho());
    this->mostrarPaciente(nodo);
}

void ArbolAVL::mostrarFactoresBalance() {
    this->factores(this->raiz);
}

void ArbolAVL::factores(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }
    this->factores(nodo->getIzquierdo());
    std::cout << "ID " << nodo->getPaciente()->getId() << " | factor de balance: " << this->factorBalance(nodo) << std::endl;
    this->factores(nodo->getDerecho());
}

int ArbolAVL::getAltura() {
    return this->altura(this->raiz);
}

bool ArbolAVL::isEmpty() {
    return this->raiz == nullptr;
}
