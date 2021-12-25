#pragma once
#include "Produs.h"

/**
* Abstract implemenatation of a Tableta
*
* It is a subclass of Produs.
*/
class Naturiste : public Produs {
	string utilizare;

	/**
	 * Passes the data in a stream
	 * for a Naturiste object.
	 *
	 * @return stream containing data
	 * of an Naturiste `ostream&`
	 */
	ostream& afisare(ostream&) const;
public:

	/**
	* Constructor
	*
	* Initializes a Naturiste with all
	* of its members and the superclass
	* members.
	*/
	Naturiste(string den, string prod, int p, string u) : Produs(den, prod, p), utilizare{ u }{};

	/**
	 * Overloads the << operator
	 * for a Naturiste object.
	 *
	 * @relatesalso Naturiste
	 */
	friend ostream& operator<<(ostream&, const Naturiste&);

	/**
	* Getter for utilizare
	*
	* @return the use cases `string`
	*/
	string getUtilizare()const { return this->utilizare; };
};