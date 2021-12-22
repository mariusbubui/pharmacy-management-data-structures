#include "../Headers/Products/Tableta.h"

ostream& Tableta::afisare(ostream& st) const {
	st << "Tableta\nDenumire: " << denumire << "\nProducator: " << producator << "\nPret: " << pret << " RON\nSubstanta activa: " << substanta_activa << "\nPresciptie medicala: ";
	if (eliberare)
		st << "DA\n";
	else
		st << "NU\n";
	st << "Gramaj: " << gramaj << "mg\n";
	return st;
}

ostream& operator<<(ostream& st, const Tableta& t) {
	return t.afisare(st);
}
