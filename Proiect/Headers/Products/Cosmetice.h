#pragma once
#include "Produs.h"

/**
* Abstract implemenatation of a Cosmetice
*
* It is a subclass of Produs.
*/
class Cosmetice : public Produs {
	string zona_aplicare;

	/**
	 * Passes the data in a stream
	 * for a Cosmetice object.
	 *
	 * @return stream containing data
	 * of an Cosmetice `ostream&`
	 */
	ostream& afisare(ostream&) const;
public:

	/**
	* Constructor
	*
	* Initializes a Cosmetice with all
	* of its members and the superclass
	* members.
	*/
	Cosmetice(string den, string prod, int p, string zona) : Produs(den, prod, p), zona_aplicare{ zona }{};

	/**
	 * Overloads the << operator
	 * for a Cosmetice object.
	 *
	 * @relatesalso Cosmetice
	 */
	friend ostream& operator<<(ostream&, const Cosmetice&);

	/**
	* Getter for zona_aplicare
	*
	* @return the application area `string`
	*/
	string getZona() const { return this->zona_aplicare; };
};
