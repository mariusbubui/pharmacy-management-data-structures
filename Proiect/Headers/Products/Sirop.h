#pragma once
#include "Medicament.h"

class Sirop :
    public Medicament{
	double concentratie;
	ostream& afisare(ostream&) const;
public:
	Sirop(string den, string prod, int p, string subs, bool e, double c) : Medicament(den, prod, p, subs, e), concentratie{ c }{};
	friend ostream& operator<<(ostream&, const Sirop&);
	double getConcentratie() const { return this->concentratie; };
};