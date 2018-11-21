#include "GrafoAbst.h"

GrafoAbst::GrafoAbst(int N, double p, Objeto& o) {
    vectorVrts.resize( N, Vrt(o) );
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, 9999);
    double random;
    for( int i = 0; i < N; i++ ){
        for( int j = i+1; j < N; j++ ){
            random = (double)(distribution(generator))/10000.0;
            if( random <= p ){
                vectorVrts[i].lstAdy.push_back( j );
                vectorVrts[j].lstAdy.push_back( i );
            }
        }
    }
}

GrafoAbst::GrafoAbst(int N, int K, double beta, Objeto& o) {
    vectorVrts.resize( N, Vrt(o) );
    
    //ANILLO
    int iz;
    int dr;
    for( int n = 0; n < N; n++ ){
        iz = n;
        dr = n;
        for( int j = 0; j < K; j++ ){
            if( j < K/2 ){
                iz--;
                if( iz < 0 )
                    iz = N-1;
                vectorVrts[n].lstAdy.push_back(iz);
            } else {
                dr++;
                if( dr > N-1 )
                    dr = 0;
                vectorVrts[n].lstAdy.push_back(dr);
            }
        }
    }
    
    //REALAMBRAMIENTO
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, 9999);
    uniform_int_distribution<int> distribution1(0, N-1);
    double nodRand;
    bool nodRandValido;
    double proRand;
    int limInferior;
    int limSuperior;
    list<int>::iterator itParaInsert;
    for( int n = 0; n < N; n++ ){
        limInferior = n+1;
        limSuperior = n+K/2;
        if( N <= limInferior ){
            limInferior -= N;
            limSuperior -= N;
        }
        itParaInsert = vectorVrts[n].lstAdy.begin();
        while( !(limInferior <= *itParaInsert && *itParaInsert <= limSuperior) )
            itParaInsert++;
        for( int i = K/2; i < K; i++ ){
            proRand = (double)(distribution(generator))/10000;
            if( proRand <= beta ){
                nodRand = distribution1(generator);
                nodRandValido = false;
                while( !nodRandValido ){
                    nodRandValido = true;
                    for( list<int>::const_iterator t = vectorVrts[n].lstAdy.begin(); t != vectorVrts[n].lstAdy.end(); t++ ){
                        if( *t == nodRand || nodRand == n ){
                            nodRandValido = false;
                            t = --(vectorVrts[n].lstAdy.end());
                        }
                    }
                    if( !nodRandValido )
                        nodRand = (rand()%N);
                }
                vectorVrts[nodRand].lstAdy.push_back(n);
                vectorVrts[*itParaInsert].lstAdy.remove(n);
                *itParaInsert = nodRand;
                itParaInsert++;
            }
        }
    }
}

GrafoAbst::GrafoAbst(ifstream& archivo, Objeto& o) {
    string cantNodos;
    getline( archivo, cantNodos );
    int nodos = atoi( cantNodos.c_str() );
    int c;
    vectorVrts.resize( nodos, Vrt(o) );
    for( int i = 0; i < nodos; i++ ){
        while( archivo.peek() != '\n' && !archivo.eof() ){
            archivo >> c;
            vectorVrts[i].lstAdy.push_back(c);
            archivo.get();
        }
        archivo.get();
    }
    archivo.close();
}

GrafoAbst::GrafoAbst(const GrafoAbst& orig) {
    vectorVrts.resize( orig.obtTotVrt() );
    for( int i = 0; i < orig.obtTotVrt(); i++ ){
        Vrt vertice( orig.vectorVrts[i] );
        vectorVrts[i] = vertice;
//      Vrt<T> vertice( orig[i] );
//      vectorVrts[i] = vertice;
//      vectorVrts[i].lstAdy = orig.vectorVrts[i].lstAdy;
    }
}

GrafoAbst::~GrafoAbst() {
}

bool GrafoAbst::xstVrt(int idVrt) const {
    bool result = false;
    if( 0 <= idVrt && idVrt < vectorVrts.size() )
        result = true;
    return result;
}

bool GrafoAbst::xstAdy(int idVrtO, int idVrtD) const {
    int i =idVrtO;
    int j=idVrtD;
    bool func =false;
    list<int>::const_iterator recor = vectorVrts[i].lstAdy.begin();
    list<int>::const_iterator fin = vectorVrts[i].lstAdy.end();
    while(recor!=fin){
        if(*recor==j){
            func=true;
            recor=fin;
        }
        if(recor != fin){
            recor++;
        }
    }
    return func;
}

void GrafoAbst::obtIdVrtAdys(int idVrt, vector< int >& rsp) const {
    list<int>::const_iterator i = vectorVrts[idVrt].lstAdy.begin();
    list<int>::const_iterator end = vectorVrts[idVrt].lstAdy.end();
    rsp.resize( vectorVrts[idVrt].lstAdy.size() );
    int j = 0;
    while( i != end ){
        rsp[j] = *i;
        i++;
        j++;
    }
}

int GrafoAbst::obtCntVrtAdys(int idVrt) const {
    return vectorVrts[idVrt].lstAdy.size();
}

int GrafoAbst::obtTotArc() const {
    int total=0;
    int N=obtTotVrt();
    for( int i = 0; i < N; i++ ){
        total += vectorVrts[i].lstAdy.size();
    }
    total /= 2;
    return total;
}

int GrafoAbst::obtTotVrt() const {
    return vectorVrts.size();
}

Objeto& GrafoAbst::operator[](int idVrt) {
    return *(vectorVrts[idVrt].obj_ptr);
}

double GrafoAbst::coeficienteLocalAgrupamiento(int idVrt) const {
    int nodo=idVrt;
    double resul=0;
    double cuenta=0;
    vector<int> nodos;
    obtIdVrtAdys(nodo,nodos);
    int tamano = nodos.size();
    
    for(int i=0;i<tamano;i++){
        for(int j=0;j<tamano;j++){
            if( xstAdy(nodos[i], nodos[j])){
                cuenta++;
            }
        }
    }
    cuenta=cuenta/2;
    int vrtAdyNodo = obtCntVrtAdys(nodo);
    double den=( vrtAdyNodo*(vrtAdyNodo - 1) );
    resul= ( 2*(cuenta) )/den;
    if(tamano==1){
        resul=0;
    }
    
    return resul;
}

bool GrafoAbst::conformidadPareto() const {
    vector<double> coe;
    int tamano=(vectorVrts.size());
    coe.resize( tamano );
    int i=0;
    while(i < tamano){
        coe[i] = coeficienteLocalAgrupamiento(i);
        i++;
    }

    sort( coe.begin(), coe.end(), greater<double>() );

    double cmenor=(vectorVrts.size())*0.20;
    i=0;
    double may = 0.0;
    double men = 0.0;
    while(i<(coe.size())){
    if (i<cmenor){
        men=men+coe[i];
    }else{
        may=may+coe[i];
    }
        i++;
    }
    if(men>=may){
        return true;
    }else{
        return false;
    }
}