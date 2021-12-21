#pragma once
#include "Medicament.h"

class Tableta :
    public Medicament{
	int gramaj;
	ostream& afisare(ostream&) const;
public:
	Tableta(string den, string prod, int p, string subs, bool e, int g) : Medicament(den, prod, p, subs, e), gramaj{ g }{};
	friend ostream& operator<<(ostream&, const Tableta&);
	int getGramaj() const { return this->gramaj; };
};

