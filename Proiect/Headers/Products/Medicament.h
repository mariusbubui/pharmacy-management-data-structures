#pragma once
#include "Produs.h"

/**
* Abstract implemenatation of a Medicament
*
* It is a subclass of Produs.
*/
class Medicament : public Produs {
protected:
	string substanta_activa;
	bool eliberare;

	/**
	 * Passes the data in a stream
	 * for a Medicament object.
	 *
	 * @return stream containing data
	 * of an Medicament `ostream&`
	 */
	virtual ostream& afisare(ostream&) const;
public:

	/**
	* Constructor
	*
	* Initializes a Medicament with all
	* of its members and the superclass
	* members.
	*/
	Medicament(string den, string prod, int p, string subs, bool e) : Produs(den, prod, p), substanta_activa{ subs }, eliberare{ e } {};

	/**
	 * Overloads the << operator
	 * for a Medicament object.
	 *
	 * @relatesalso Medicament
	 */
	friend ostream& operator<<(ostream&, const Medicament&);

	/**
	* Getter for substanta_activa
	*
	* @return the active substance `string`
	*/
	string getSubstanta() const { return this->substanta_activa; };

	/**
	* Getter for eliberare
	*
	* @return the need for medical prescription `bool`
	*/
	bool getEliberare() const { return this->eliberare; };
};