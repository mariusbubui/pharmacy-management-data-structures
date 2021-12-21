#pragma once
#include "Produs.h"

class Cosmetice : public Produs {
	string zona_aplicare;
	ostream& afisare(ostream&) const;
public:
	Cosmetice(string den, string prod, int p, string zona) : Produs(den, prod, p), zona_aplicare{ zona }{};
	friend ostream& operator<<(ostream&, const Cosmetice&);
	string getZona()const { return this->zona_aplicare; };
};
