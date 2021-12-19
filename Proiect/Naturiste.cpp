#include "Naturiste.h"

ostream& Naturiste::afisare(ostream& st) const{
	st << "Produs naturist\nDenumire: " << denumire << "\nProducator: " << producator << "\nPret: " << pret << " RON\nActiunea produsului: " << utilizare << "\n";
	return st;
}

ostream& operator<<(ostream& st, const Naturiste& n){
	return n.afisare(st);
}
