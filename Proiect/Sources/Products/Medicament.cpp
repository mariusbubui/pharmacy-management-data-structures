#include "../../Headers/Products/Medicament.h"

ostream& Medicament::afisare(ostream& st) const{
	st << "Medicament\nDenumire: " << denumire << "\nProducator: " << producator << "\nPret: " << pret << " RON\nSubstanta activa: " << substanta_activa << "\nPresciptie medicala: ";
	if (eliberare)
		st << "DA\n";
	else
		st << "NU\n";
	return st;
}

ostream& operator<<(ostream& st, const Medicament& m){
	return m.afisare(st);
}
