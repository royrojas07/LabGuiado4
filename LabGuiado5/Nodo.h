/* 
 * File:   Nodo.h
 * Author: alan.calderon
 */

#ifndef NODO_H
#define	NODO_H

#include <random>
#include <ostream>
#include <string>
using namespace std;

#include "Objeto.h"

class Nodo : public Objeto{
public:
    // Representa un nodo de la red de computadores sobre la cual se aplica la simulación
    // de dispersión de virus.
    
	/* SE DEBE MODIFICAR PARA QUE HEREDE CORRECTAMENTE DE LA CLASE ABSTRACTA Objeto */

    /* TIPO PÚBLICO DE ESTADOS DE VÉRTICES */
    enum E{ // representa el tipo de estados de la red de infección
        S, // representa un vértice susceptible de infección
        I, // representa un vértice infectado
        R, // representa un vértice resistente
    };
    
    Nodo();
    Nodo(const Nodo& orig);
    virtual ~Nodo();
    
    // EFE: retorna el valor del estado del nodo.
    E obtEstado() const;
        
    // MOD: *this.
    // EFE: cambia el estado del nodo a ne.
    void modEstado(E ne);
    
    virtual bool operator==(const Objeto& o) const;
    
    virtual bool operator!=(const Objeto& o) const;
    
    virtual Objeto& clonar() const;
    
    virtual string toString() const;
    
    virtual Objeto& operator=(const Objeto& o);
    
private:
    E estado; // representa el estado del nodo
};

#endif	/* NODO_H */

