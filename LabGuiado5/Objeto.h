#ifndef OBJETO_H
#define OBJETO_H

#include <string>
using namespace std;

class Objeto
{
	/* 
	* Es una clase abstracta de la cual se debe derivar implementando sus m�todos abstractos puros para obtener clases concretas.
	* Representa objetos ordenables, es decir, que pueden ser comparados mediante "operator<".
	* Toda clase derivada de Objeto para ser concreta DEBE implementar tanto los dos constructores, como el destructor
	* y los operadores de comparaci�n.
	*/

public:

	/* CONSTRUCTORES Y DESTRUCTOR */

	Objeto();
	Objeto(const Objeto& orig);
	virtual ~Objeto();

	/* COMPARADORES */

	//EFE: retorna true si *this < o, false en caso contrario.
	virtual bool operator==(const Objeto& o) const = 0;

	//EFE: retorna true si *this < o, false en caso contrario.
	virtual bool operator!=(const Objeto& o) const = 0;

	/* CLONADOR VIRTUAL PURO */

	//EFE: realiza la misma funci�n del constructor de copias, pero a diferencia del constructor
	//	   este m�todo s� permite el enlace din�mico, el constructor s�lo permite el enlace est�tico.
	virtual Objeto& clonar() const = 0;

	/* SERIALIZADOR VIRTUAL PURO */

	// EFE: genera una hilera que representa el estado de *this.
	virtual string toString() const = 0;

	/* ASIGNADOR VIRTUAL PURO */
	// EFE: asigna a *this los valores de las variables de estado de o.
	virtual Objeto& operator=(const Objeto& o) = 0;
};

#endif // OBJETO_H