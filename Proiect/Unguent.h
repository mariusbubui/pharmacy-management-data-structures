#pragma once
#include "Medicament.h"

class Unguent :
	public Medicament {
	int valabilitate;
	ostream& afisare(ostream&) const;
public:
	Unguent(string den, string prod, int p, string subs, bool e, int v) : Medicament(den, prod, p, subs, e), valabilitate{ v }{};
	friend ostream& operator<<(ostream&, const Unguent&);
	int getValabilitate() const { return this->valabilitate; };
};