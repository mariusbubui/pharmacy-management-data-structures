#include "../Headers/Products/Sirop.h"

ostream& Sirop::afisare(ostream& st) const {
	st << "Sirop\nDenumire: " << denumire << "\nProducator: " << producator << "\nPret: " << pret << " RON\nSubstanta activa: " << substanta_activa << "\nPresciptie medicala: ";
	if (eliberare)
		st << "DA\n";
	else
		st << "NU\n";
	st << "Concentratie: " << concentratie << "%\n";
	return st;
}

ostream& operator<<(ostream& st, const Sirop& s) {
	return s.afisare(st);
}
