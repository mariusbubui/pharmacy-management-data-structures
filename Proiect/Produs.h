#pragma once
#include "RBTree.h"
#include <iostream>
#include <vector>
#include <string>

using std::ostream;
using std::vector;
using std::string;

class RBTree;

class Produs {
protected:
	string denumire, producator;
	int pret;
	virtual ostream& afisare(ostream&) const;
public:
	Produs(string den, string prod, int p) : denumire{ den }, producator{ prod }, pret{ p } {};
	virtual ~Produs() {};
	friend ostream& operator<<(ostream&, const Produs&);
	static void initializare(RBTree*);
	static void adaugare(vector<Produs*>&);
	static void modificare(vector<Produs*>&);
	static void stergere(RBTree*);
	static void afisare(RBTree*);
	static void cautare(RBTree*);
	static void sortare(vector<Produs*>, bool (*)(Produs*, Produs*));
	static bool filtrare(vector<Produs*>, string, bool (*)(Produs*, string));
	static void salvare_date(RBTree*);
	static bool pret1(Produs*, Produs*);
	static bool pret2(Produs*, Produs*);
	static bool denumire1(Produs*, Produs*);
	static bool denumire2(Produs*, Produs*);
	static bool f_producator(Produs*, string);
	static bool f_pret(Produs*, string);
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
