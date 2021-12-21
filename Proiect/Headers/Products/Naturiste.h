#pragma once
#include "Produs.h"

class Naturiste : public Produs {
	string utilizare;
	ostream& afisare(ostream&) const;
public:
	Naturiste(string den, string prod, int p, string u) : Produs(den, prod, p), utilizare{ u }{};
	friend ostream& operator<<(ostream&, const Naturiste&);
	string getUtilizare()const { return this->utilizare; };
};