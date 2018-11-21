/* 
 * File:   GrafoAbst.h
 * Author: Alan
 *
 * Created on 13 de noviembre de 2018, 05:49 PM
 */

#ifndef GRAFOABST_H
#define GRAFOABST_H

#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

#include "Objeto.h"

class GrafoAbst {
    // Representa una red compleja genérica con vértices de tipo Objeto.
	/* Los supuestos sobre el tipo Objeto están especificados en la definición 
	*  de la clase abstracta.
    */

public:
    /* CONSTRUCTORES */
    // DADOS:
    // N la cantidad de vértices o nodos.
    // K el promedio de adyacencias por vértice.
    
    // REQ: 0 < p < 1.
    // Construye un GrafoAbst con N vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando p. Esto
    // implica que la probabilidad de que un arco exista entre 
    // cualesquiera dos vértices es igual a p.
	// NOTA: inicializa todos vértices con o.
    GrafoAbst(int N, double p, Objeto& o);
    
    // REQ: N >> K >> ln N >> 1.
    // REQ: 0 <= beta <= 1.
    // Construye un GrafoAbst con N vértices, cada uno con K adyacencias EN PROMEDIO,
    // siguiendo el algoritmo de Watts-Strogatz:
    // https://en.wikipedia.org/wiki/Watts%E2%80%93Strogatz_model
	// NOTA: inicializa todos vértices con o.
    GrafoAbst(int N, int K, double beta, Objeto& o);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices se identifican con números de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
	// NOTA: inicializa todos vértices con o.
    GrafoAbst(ifstream& archivo, Objeto& o);

    // Construye una copia idéntica a orig.
    GrafoAbst(const GrafoAbst& orig);

    // Destructor
    ~GrafoAbst();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el GrafoAbst.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna la cantidad de vértices adyacentes a idVrt en el GrafoAbst.    
    int obtCntVrtAdys(int idVrt) const;

    // EFE: retorna el total de arcos o adyacencias en el GrafoAbst.
    int obtTotArc() const;

    // EFE: retorna el total de vértices en el GrafoAbst.
    int obtTotVrt() const;

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    Objeto& operator[](int idVrt);

    /* MÉTODOS OBSERVADORES ESPECIALES */
    
    // REQ: 0 <= idVrt < N.
    // EFE: retorna el "local clustering coefficient" o coeficiente local de agrupamiento
    //      para el vértice indicado por idVrt.
    // La definición que aparece en: http://en.wikipedia.org/wiki/Clustering_coefficient
    // Sea c == obtCntVrtAdys(idVrt).
    // Entonces coeficienteLocalAgrupamiento(idVrt) == 2 * c / (c * (c - 1))
    double coeficienteLocalAgrupamiento(int idVrt) const;
   
    // EFE: retorna true si la sumatoria del coeficiente local de agrupamiento del 20% de
    //      los vértices con coeficiente más alto es mayor o igual a la sumatoria del
    //      coeficiente local de agrupamiento del 80% de los vértices con coeficiente más
    //      bajo.
    // NOTA: se basa en el principio de Paretto: https://en.wikipedia.org/wiki/Pareto_principle
    bool conformidadPareto() const;
    
private:

    struct Vrt {
        Objeto* obj_ptr;
        list< int > lstAdy;

        Vrt() : obj_ptr(0), lstAdy() {
        }; // constructor estándar de Vrt

        Vrt(const Objeto& obj) : obj_ptr(&(&obj)->clonar()), lstAdy() {
        }; // constructor con dato de vértice, se usa enlace dinámico de clonar()

        Vrt(const Vrt& vrt) : obj_ptr(&vrt.obj_ptr->clonar()), lstAdy(vrt.lstAdy) {
        }; // constructor de copias de Vrt, se usa enlace dinámico de clonar()
    };

    vector< Vrt > vectorVrts; // vector de vértices que apuntan a Objetos
};

#endif /* GRAFOABST_H */
