#include "../Headers/Products/Cosmetice.h"

ostream& Cosmetice::afisare(ostream& st) const{
	st << "Produs cosmetic\nDenumire: " << denumire << "\nProducator: " << producator << "\nPret: " << pret << "  RON\nZona de aplicare: " << zona_aplicare << "\n";
	return st;
}

ostream& operator<<(ostream& st, const Cosmetice& c) {
	return c.afisare(st);
}
