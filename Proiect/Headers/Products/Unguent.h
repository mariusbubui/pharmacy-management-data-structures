#pragma once
#include "Medicament.h"

/**
* Abstract implemenatation of an Unguent
* 
* It is a subclass of Medicament.
*/
class Unguent : public Medicament {
	int valabilitate;

	/**
	 * Passes the data in a stream
	 * for an Unguent object.
	 *
	 * @return stream containing data
	 * of an Unguent `ostream&`
	 */	
	ostream& afisare(ostream&) const;
public:

	/**
	* Constructor
	*
	* Initializes an Unguent with all
	* of its members and the superclass
	* members.
	*/
	Unguent(string den, string prod, int p, string subs, bool e, int v) : Medicament(den, prod, p, subs, e), valabilitate{ v }{};

	/**
	 * Overloads the << operator
	 * for an Unguent object.
	 *
	 * @relatesalso Unguent
	 */
	friend ostream& operator<<(ostream&, const Unguent&);

	/**
	* Getter for valabilitate
	* 
	* @return the number of months the Unguent expires `int`
	*/
	int getValabilitate() const { return this->valabilitate; };
};