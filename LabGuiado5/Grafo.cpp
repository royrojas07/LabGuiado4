#include "Grafo.h"

Grafo::Grafo(int N, double p): grf_nodos(N, p, (Objeto&)(*(new Nodo()))){

}

Grafo::Grafo(int N, int K, double beta): grf_nodos(N, K, beta, (Objeto&)(*(new Nodo()))){

}

Grafo::Grafo(ifstream& archivo): grf_nodos(archivo, (Objeto&)(*(new Nodo()))){

}

Grafo::Grafo(const Grafo& orig): grf_nodos( orig.grf_nodos ){

}

Grafo::~Grafo() {
}

bool Grafo::xstVrt(int idVrt) const {
    return grf_nodos.xstVrt(idVrt);
}

bool Grafo::xstAdy(int idVrtO, int idVrtD) const {
    return grf_nodos.xstAdy(idVrtO, idVrtD);
}

void Grafo::obtIdVrtAdys(int idVrt, vector< int >& rspRetornar) const {
    grf_nodos.obtIdVrtAdys(idVrt, rspRetornar);
}

int Grafo::obtCntVrtAdys(int idVrt) const {
    return grf_nodos.obtCntVrtAdys(idVrt);
}

Nodo Grafo::operator[](int idVrt) const {
    return Nodo( grf_nodos.obtVrt(idVrt) );
}

int Grafo::obtTotArc() const {
    return grf_nodos.obtTotArc();
}

int Grafo::obtTotVrt() const {
    return grf_nodos.obtTotVrt();
}

int Grafo::obtTotVrtSusceptibles() const {
    int cantSusceptibles = 0;
    for( int i = 0; i < grf_nodos.obtTotVrt(); i++ ){
        if( grf_nodos.obtVrt(i).toString() == "Susceptible" )
            cantSusceptibles++;
    }
    return cantSusceptibles;
}

int Grafo::obtTotVrtInfectados() const {
    int cantInfectados = 0;
    for( int i = 0; i < grf_nodos.obtTotVrt(); i++ ){
        if( grf_nodos.obtVrt(i).toString() == "Infectado" )
            cantInfectados++;
    }
    return cantInfectados;
}

int Grafo::obtTotVrtResistentes() const {
    int cantResistentes = 0;
    for( int i = 0; i < grf_nodos.obtTotVrt(); i++ ){
        if( grf_nodos.obtVrt(i).toString() == "Resistente" )
            cantResistentes++;
    }
    return cantResistentes;
}

Nodo& Grafo::operator[](int idVrt) {
    Nodo& nodo = static_cast<Nodo&>( grf_nodos[idVrt] );
    return nodo;
}

double Grafo::coeficienteLocalAgrupamiento(int idVrt) const {
    return grf_nodos.coeficienteLocalAgrupamiento(idVrt);
}

bool Grafo::conformidadPareto() const {
    return grf_nodos.conformidadPareto();
}