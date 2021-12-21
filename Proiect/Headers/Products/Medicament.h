#pragma once
#include "Produs.h"

class Medicament : public Produs {
protected:
	string substanta_activa;
	bool eliberare;
	virtual ostream& afisare(ostream&) const;
public:
	Medicament(string den, string prod, int p, string subs, bool e) : Produs(den, prod, p), substanta_activa{ subs }, eliberare{ e } {};
	friend ostream& operator<<(ostream&, const Medicament&);
	string getSubstanta() const { return this->substanta_activa; };
	bool getEliberare() const { return this->eliberare; };
};