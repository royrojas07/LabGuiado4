/* 
 * File:   Nodo.cpp
 * Author: alan.calderon
 * 
 * Created on 24 de octubre de 2016, 06:00 PM
 */

#include "Nodo.h"
using namespace std;

Nodo::Nodo() : estado(S) {
}

Nodo::Nodo(const Objeto& orig){
    if( orig.toString() == "Susceptible" )
        estado = S;
    else if( orig.toString() == "Infectado" )
        estado = I;
    else if( orig.toString() == "Resistente" )
        estado = R;
}

Nodo::Nodo(const Nodo& orig) : estado(orig.estado) {
}

Nodo::~Nodo() {
}

Nodo::E Nodo::obtEstado() const {
    return estado;
}

void Nodo::modEstado(E ne) {
    estado = ne;
}

bool Nodo::operator==(const Objeto& o) const{
    return toString() == o.toString();
}

bool Nodo::operator!=(const Objeto& o) const{
    return !(*this == o);
}

Objeto& Nodo::clonar() const{
    Nodo* clon = new Nodo(*this);
    return *clon;
}

string Nodo::toString() const{
    string s;
    if( estado == 0 )
        s = "Susceptible";
    else if( estado == 1 )
        s = "Infectado";
    else if( estado == 2 )
        s = "Resistente";
    return s;
}

Objeto& Nodo::operator=(const Objeto& o){
    if( o.toString() == "Susceptible" )
        estado = S;
    else if( o.toString() == "Infectado" )
        estado = I;
    else if( o.toString() == "Resistente" )
        estado = R;
    return *this;
}