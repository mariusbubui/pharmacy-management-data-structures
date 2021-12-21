#include "../../Headers/Products/Unguent.h"

ostream& Unguent::afisare(ostream& st) const {
	st << "Unguent\nDenumire: " << denumire << "\nProducator: " << producator << "\nPret: " << pret << " RON\nSubstanta activa: " << substanta_activa << "\nPresciptie medicala: ";
	if (eliberare)
		st << "DA\n";
	else
		st << "NU\n";
	st << "Valabilitate dupa deschidere: " << valabilitate << " luni(a)\n";
	return st;
}

ostream& operator<<(ostream& st, const Unguent& u) {
	return u.afisare(st);
}
