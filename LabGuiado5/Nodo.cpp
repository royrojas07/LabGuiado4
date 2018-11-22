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
    bool v = false;
    if( toString() == o.toString() )
        v = true;
    return v;
}

bool Nodo::operator!=(const Objeto& o) const{
    return !(*this == o);
}

Nodo::Objeto& clonar() const{
    
}

string Nodo::toString() const{
    string s;
    if( estado == 0 )
        s = "Susceptible";
    else if( estado == 1 )
        s = "Infectado";
    else if( estado == 2 )
        s = "Resistente";
    s << estado;
    return s;
}

Objeto& Nodo::operator=(const Objeto& o){
    if( o.toString() == "Susceptible" )
        estado = 0;
    else if( o.toString() == "Infectado" )
        estado = 1;
    else if( o.toString() == "Resistente" )
        estado = 2;
    return *this;
}