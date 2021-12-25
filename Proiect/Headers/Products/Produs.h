#pragma once
#include "DataStructures/RBTree.h"
#include "DataStructures/HashTable.h"
#include <iostream>
#include <vector>
#include <string>

using std::ostream;
using std::vector;
using std::string;

class RBTree;

/**
* Abstract implemenatation of a Produs
*
* Contains the name,price and the 
* producer of the product.
*/
class Produs {
protected:
	string denumire, producator;
	int pret;
	virtual ostream& afisare(ostream&) const;
public:
	Produs(string den, string prod, int p) : denumire{ den }, producator{ prod }, pret{ p } {};
	virtual ~Produs() {};
	friend ostream& operator<<(ostream&, const Produs&);

	static void initializare(RBTree*, HashTable*);
	static void adaugare(RBTree*, HashTable*);
	static void modificare(RBTree*, HashTable*);
	static void stergere(RBTree*, HashTable*);
	static void afisare(RBTree*, HashTable*);
	static void cautare(RBTree*, HashTable*);
	static void disponibilitate(HashTable*);
	static void sortare(RBTree*, bool (*comparator)(Produs*, Produs*));
	static bool filtrare(RBTree*, string, bool (*filter)(Produs*, string));
	static void salvare_date(RBTree*, HashTable*);
	static bool pret1(Produs*, Produs*);
	static bool pret2(Produs*, Produs*);
	static bool filter_producator(Produs*, string);
	static bool filter_pret(Produs*, string);

	string getDenumire() const { return this->denumire; };
	string getProducator() const { return this->producator; };
	int getPret() const { return this->pret; };
	virtual string getSubstanta() const { return ""; };
	virtual bool getEliberare() const { return false; };
	virtual string getUtilizare() const { return ""; };
	virtual string getZona()const { return ""; };
	virtual int getGramaj() const { return -1; };
	virtual double getConcentratie() const { return -1; };
	virtual int getValabilitate() const { return -1; };
};
