#include "ArbolDecision.h"

ArbolDecision::ArbolDecision() {
    this->raiz = new NodoArbol("Edad", 14);
    this->raiz->setRamaSi(new NodoArbol("Pediatria"));
    this->raiz->setRamaNo(new NodoArbol("Trauma", 1));

    NodoArbol* nodoTrauma = this->raiz->getNo();
    nodoTrauma->setRamaSi(new NodoArbol("RequiereCirugia", 1));
    nodoTrauma->getSi()->setRamaSi(new NodoArbol("Cirugia"));
    nodoTrauma->getSi()->setRamaNo(new NodoArbol("Traumatologia"));

    nodoTrauma->setRamaNo(new NodoArbol("SintomasNeurologicos", 1));
    NodoArbol* nodoNeuro = nodoTrauma->getNo();
    nodoNeuro->setRamaSi(new NodoArbol("Neurologia"));

    nodoNeuro->setRamaNo(new NodoArbol("TipoDolor", 0, "pecho"));
    NodoArbol* nodoPecho = nodoNeuro->getNo();
    nodoPecho->setRamaSi(new NodoArbol("Cardiologia"));

    nodoPecho->setRamaNo(new NodoArbol("Temperatura", 38.5));
    NodoArbol* nodoTemp = nodoPecho->getNo();
    nodoTemp->setRamaSi(new NodoArbol("Urgencias"));

    nodoTemp->setRamaNo(new NodoArbol("Dolor", 8));
    NodoArbol* nodoDolor = nodoTemp->getNo();
    nodoDolor->setRamaSi(new NodoArbol("Urgencias"));

    nodoDolor->setRamaNo(new NodoArbol("DiasHospitalizacion", 2));
    NodoArbol* nodoDias = nodoDolor->getNo();
    nodoDias->setRamaSi(new NodoArbol("Hospitalizacion"));
    nodoDias->setRamaNo(new NodoArbol("Medicina General"));
}

ArbolDecision::~ArbolDecision() {
    this->vaciarArbol(this->raiz);
}

void ArbolDecision::vaciarArbol(NodoArbol* nodo) {
    if (nodo != nullptr) {
        this->vaciarArbol(nodo->getSi());
        this->vaciarArbol(nodo->getNo());
        delete nodo;
    }
}

std::string ArbolDecision::obtenerServicio(Paciente* p) {
    if (p == nullptr) {
        return "Datos inválidos";
    }
    return this->buscarDepartamento(this->raiz, p);
}

std::string ArbolDecision::buscarDepartamento(NodoArbol* nodo, Paciente* p) {
    if (nodo->getPregunta() == "Hoja") {
        return nodo->getServicio();
    }

    bool verificador = false;

    if (nodo->getPregunta() == "Edad") {
        if (p->getEdad() < nodo->getValorNum()) {
            verificador = true;
        }
    } else if (nodo->getPregunta() == "Trauma") {
        if (p->getTrauma() == nodo->getValorNum()) {
            verificador = true;
        }
    } else if (nodo->getPregunta() == "RequiereCirugia") {
        if (p->getRequiereCirugia() == nodo->getValorNum()) {
            verificador = true;
        }
    } else if (nodo->getPregunta() == "SintomasNeurologicos") {
        if (p->getSintomas() == nodo->getValorNum()) {
            verificador = true;
        }
    } else if (nodo->getPregunta() == "TipoDolor") {
        if(p->getTipoDolor() == nodo->getValorTexto()) {
            verificador = true;
        }
    } else if (nodo->getPregunta() == "Temperatura") {
        if (p->getTemperatura() > nodo->getValorNum()) {
            verificador = true;
        }
    } else if (nodo->getPregunta() == "Dolor") {
        if (p->getDolor() >= nodo->getValorNum()) {
            verificador = true;
        }
    } else if (nodo->getPregunta() == "DiasHospitalizacion") {
        if (p->getDiasHosp() >= nodo->getValorNum()) {
            verificador = true;
        }
    }

    if (verificador) {
        return this->buscarDepartamento(nodo->getSi(), p);
    } else {
        return this->buscarDepartamento(nodo->getNo(), p);
    }

}

void ArbolDecision::verCaminos() {
    this->mostrarPreorden(this->raiz, 0);
}

void ArbolDecision::mostrarPreorden(NodoArbol* nodo, int nivel) {
    if (nodo == nullptr) {
        return;
    }

    for (int i = 0; i < nivel; i++) {
        std::cout<< " ";
    }

    if (nodo->getPregunta() == "Hoja") {
        std::cout<< "=> " << nodo->getServicio() << "\n";
    } else {
        std::cout << "- " << nodo->getPregunta() << " " << nodo->getValorNum() << nodo->getValorTexto() << "\n";
        this->mostrarPreorden(nodo->getSi(), nivel + 1);
        this->mostrarPreorden(nodo->getNo(), nivel + 1);
    }


}

