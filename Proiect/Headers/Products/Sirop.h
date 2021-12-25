#pragma once
#include "Medicament.h"

/**
* Abstract implemenatation of a Sirop
*
* It is a subclass of Medicament.
*/
class Sirop : public Medicament{
	double concentratie;

	/**
	 * Passes the data in a stream
	 * for an Sirop object.
	 *
	 * @return stream containing data
	 * of an Sirop `ostream&`
	 */
	ostream& afisare(ostream&) const;
public:

	/**
	* Constructor
	*
	* Initializes a Sirop with all
	* of its members and the superclass
	* members.
	*/
	Sirop(string den, string prod, int p, string subs, bool e, double c) : Medicament(den, prod, p, subs, e), concentratie{ c }{};
	
	/**
	 * Overloads the << operator
	 * for a Sirop object.
	 *
	 * @relatesalso Sirop
	 */
	friend ostream& operator<<(ostream&, const Sirop&);

	/**
	* Getter for concentratie
	*
	* @return the concentration of the Sirop in % `double`
	*/
	double getConcentratie() const { return this->concentratie; };
};