#pragma once
#include <string>
#include <iostream>
#include "NodoPorPaciente.h"
template <typename T>

class ListaPrincipal {
    protected:
        NodoPorPaciente<T>* inicio;

    public: 
        ListaPrincipal() {
            this-> inicio = nullptr;
        }

        ~ListaPrincipal() {
            this->clear();
        }

        bool isEmpty() {
            return this->inicio == nullptr;
        }

        int size() {
            int total = 0;
            NodoPorPaciente<T>* cursor = this->inicio;
            while (cursor != nullptr) {
                total++;
                cursor = cursor->getNext();
            }
            return total;
        }

        void insert(T paciente, int indice) {
            if (indice < 0 ) throw 0;
            if (indice == 0) {
                this->insertFirst(paciente);
                return;
            }
            if (this->inicio == nullptr) throw 0;

            NodoPorPaciente<T>* cursor = this->inicio;
            for (int i = 0; i < indice - 1; i++) {
                cursor = cursor->getNext();
                if (!cursor) throw 0;
            }
            NodoPorPaciente<T>* nuevo = new NodoPorPaciente<T>(paciente);
            nuevo->setNext(cursor->getNext());
            cursor->setNext(nuevo);

        } 

        void insertFirst(T paciente) { 
            NodoPorPaciente<T>* nuevo = new NodoPorPaciente<T>(paciente); 
            nuevo->setNext(this->inicio);
            this->inicio = nuevo;
        }

        void insertLast(T paciente) {
            if (this->inicio == nullptr) {
                this->inicio = new NodoPorPaciente<T>(paciente);
                return;
            }

            NodoPorPaciente<T>* cursor = this->inicio;
            while (cursor->getNext() != nullptr) {
                cursor = cursor->getNext();
            }
            cursor->setNext(new NodoPorPaciente<T>(paciente));
        }

        T get(int indice) {
            if(!this->inicio || indice < 0 ) {
                throw 0;
            }
            NodoPorPaciente<T>* cursor = this->inicio;

            for (int i = 0; i < indice; i++) {
                cursor = cursor->getNext();
                if (cursor == nullptr) throw 0;
            }
            return cursor->getPaciente();

        }

        T getFirst() {
            if(this->inicio == nullptr) {
                throw 0;
            }
            return this->inicio->getPaciente();
        }

        void remove(int indice) {
            if(!this->inicio || indice < 0) throw 0;
            if (indice == 0) {
                NodoPorPaciente<T>* toDel = this ->inicio;
                this->inicio = toDel->getNext();
                delete toDel;
                return;
            }

            NodoPorPaciente<T>*cursor = this->inicio;
            for (int i = 0; i < indice - 1; i++) {
                cursor = cursor->getNext();
                if (!cursor) throw 0;
            }

            NodoPorPaciente<T>* toDelete = cursor->getNext();
            if(toDelete == nullptr) throw 0;
            
            cursor->setNext(
                toDelete ? toDelete->getNext() : nullptr
            );
            delete toDelete;

        }
        
        void clear() {
            while (this->inicio != nullptr) {
                NodoPorPaciente<T>* temp = this->inicio->getNext();
                delete this->inicio;
                this->inicio = temp;
            }
        }


};


