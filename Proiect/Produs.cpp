#define _CRT_SECURE_NO_WARNINGS 1
#include "Produs.h"
#include "Cosmetice.h"
#include "Naturiste.h"
#include "Medicament.h"
#include "Tableta.h"
#include "Sirop.h"
#include "Unguent.h"
#include <fstream>
#include <algorithm>
#include <ios>
#include <limits>
#include <queue>

using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::sort;
using std::transform;
using std::queue;

template <class myType>
void eroare(myType& x) {
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "\u001b[31mIntroduceti o valoare numerica: \u001b[0m";
	while (!(cin >> x)) {
		cout << "\u001b[31mIntroduceti o valoare numerica: \u001b[0m";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

ostream& Produs::afisare(ostream& st) const {
	st << "Produs\nDenumire: " << denumire << "\nProducator: " << producator << "\nPret: " << pret << " RON\n";
	return st;
}

void Produs::initializare(RBTree* tree) {
	int n;
	ifstream in("produse.txt");
	if (!in.is_open())
		return;
	in >> n;
	in.ignore(256, '\n');
	string tip, nume, producator, aux1, aux2;
	int pret, gramaj, val;
	double c;
	for (int i = 0; i < n; i++) {
		getline(in, tip, ';');  transform(tip.begin(), tip.end(), tip.begin(), tolower); tip[0] = (char)toupper(tip[0]);
		getline(in, nume, ';');  transform(nume.begin(), nume.end(), nume.begin(), tolower); nume[0] = (char)toupper(nume[0]);
		getline(in, producator, ';');  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
		in >> pret;
		if (tip == "Produs")
			tree->RBInsert(tree->createNode(new Produs(nume, producator, pret)));
		else if (tip == "Cosmetic") {
			in.get();
			in >> aux1; transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			tree->RBInsert(tree->createNode(new Cosmetice(nume, producator, pret, aux1)));
		}
		else if (tip == "Naturist") {
			in.get();
			in >> aux1; transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			tree->RBInsert(tree->createNode(new Naturiste(nume, producator, pret, aux1)));
		}
		else if (tip == "Medicament") {
			in.get();
			getline(in, aux1, ';'); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			in >> aux2;
			tree->RBInsert(tree->createNode(new Medicament(nume, producator, pret, aux1, aux2 == "DA")));
		}
		else if (tip == "Tableta") {
			in.get();
			getline(in, aux1, ';'); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			getline(in, aux2, ';');
			in >> gramaj;
			tree->RBInsert(tree->createNode(new Tableta(nume, producator, pret, aux1, aux2 == "DA", gramaj)));
		}
		else if (tip == "Sirop") {
			in.get();
			getline(in, aux1, ';'); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			getline(in, aux2, ';');
			in >> c;
			tree->RBInsert(tree->createNode(new Sirop(nume, producator, pret, aux1, aux2 == "DA", c)));
		}
		else if (tip == "Unguent") {
			in.get();
			getline(in, aux1, ';'); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			getline(in, aux2, ';');
			in >> val;
			tree->RBInsert(tree->createNode(new Unguent(nume, producator, pret, aux1, aux2 == "DA", val)));
		}
		in.ignore(256, '\n');
	}
	in.close();
}

void Produs::adaugare(RBTree* tree) {
	string tip, nume, producator, aux1, aux2;
	int pret, gramaj, val;
	double c;
	cout << "Introduceti tipul produsului(PRODUS/COSMETICE/NATURISTE/MEDICAMENT/TABLETA/SIROP/UNGUENT): ";
	while (true) {
		getline(cin, tip); transform(tip.begin(), tip.end(), tip.begin(), toupper);
		if (tip == "PRODUS" || tip == "MEDICAMENT" || tip == "TABLETA" || tip == "SIROP" || tip == "UNGUENT" || tip == "COSMETICE" || tip == "NATURISTE")
			break;
		cout << "Introduceti un tip existent: ";
	}
	cout << "Denumirea produsului: ";
	while (true) {
		getline(cin, nume);  transform(nume.begin(), nume.end(), nume.begin(), tolower); nume[0] = (char)toupper(nume[0]);
		if (nume.size())
			break;
		cout << "Denumirea produsului: ";
	}
	cout << "Producatorul produsului: ";
	getline(cin, producator);  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
	cout << "Pretul produsului: ";
	if (!(cin >> pret))
		eroare(pret);
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (tip == "PRODUS") {
		tree->RBInsert(tree->createNode(new Produs(nume, producator, pret)));
		cout << "\n\u001b[32mProdusul a fost adaugat cu succes!\u001b[0m\n";
	}
	else if (tip == "COSMETICE") {
		cout << "Zona de aplicare: ";
		while (true) {
			getline(cin, aux1); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Zona de aplicare: ";
		}
		tree->RBInsert(tree->createNode(new Cosmetice(nume, producator, pret, aux1)));
		cout << "\n\u001b[32mProdusul a fost adaugat cu succes!\u001b[0m\n";
	}
	else if (tip == "NATURISTE") {
		cout << "Utilizarea produsului naturist: ";
		while (true) {
			getline(cin, aux1); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Utilizarea produsului naturist: ";
		}
		tree->RBInsert(tree->createNode(new Naturiste(nume, producator, pret, aux1)));
		cout << "\n\u001b[32mProdusul a fost adaugat cu succes!\u001b[0m\n";
	}
	else if (tip == "MEDICAMENT") {
		cout << "Substanta activa: ";
		while (true) {
			getline(cin, aux1); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Substanta activa: ";
		}
		while (true) {
			cout << "Necesita prescriptie(DA/NU): ";
			getline(cin, aux2); transform(aux2.begin(), aux2.end(), aux2.begin(), toupper);
			if (aux2 == "DA" || aux2 == "NU")
				break;
		}
		tree->RBInsert(tree->createNode(new Medicament(nume, producator, pret, aux1, aux2 == "DA")));
		cout << "\n\u001b[32mProdusul a fost adaugat cu succes!\u001b[0m\n";
	}
	else if (tip == "TABLETA") {
		cout << "Substanta activa: ";
		while (true) {
			getline(cin, aux1); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Substanta activa: ";
		}
		while (true) {
			cout << "Necesita prescriptie(DA/NU): ";
			getline(cin, aux2); transform(aux2.begin(), aux2.end(), aux2.begin(), toupper);
			if (aux2 == "DA" || aux2 == "NU")
				break;
		}
		cout << "Gramajul tabletei: ";
		if (!(cin >> gramaj))
			eroare(gramaj);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		tree->RBInsert(tree->createNode(new Tableta(nume, producator, pret, aux1, aux2 == "DA", gramaj)));
		cout << "\n\u001b[32mProdusul a fost adaugat cu succes!\u001b[0m\n";
	}
	else if (tip == "SIROP") {
		cin.get();
		cout << "Substanta activa: ";
		while (true) {
			getline(cin, aux1); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Substanta activa: ";
		}
		while (true) {
			cout << "Necesita prescriptie(DA/NU): ";
			getline(cin, aux2); transform(aux2.begin(), aux2.end(), aux2.begin(), toupper);
			if (aux2 == "DA" || aux2 == "NU")
				break;
		}
		cout << "Concentratia in procente: ";
		if (!(cin >> c))
			eroare(c);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		tree->RBInsert(tree->createNode(new Sirop(nume, producator, pret, aux1, aux2 == "DA", c)));
		cout << "\n\u001b[32mProdusul a fost adaugat cu succes!\u001b[0m\n";
	}
	else if (tip == "UNGUENT") {
		cin.get();
		cout << "Substanta activa: ";
		while (true) {
			getline(cin, aux1); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Substanta activa: ";
		}
		while (true) {
			cout << "Necesita prescriptie(DA/NU): ";
			getline(cin, aux2); transform(aux2.begin(), aux2.end(), aux2.begin(), toupper);
			if (aux2 == "DA" || aux2 == "NU")
				break;
		}
		cout << "Numarul de luni valabile de la deschidere: ";
		if (!(cin >> val))
			eroare(val);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		tree->RBInsert(tree->createNode(new Unguent(nume, producator, pret, aux1, aux2 == "DA", val)));
		cout << "\n\u001b[32mProdusul a fost adaugat cu succes!\u001b[0m\n";
	}
}

void Produs::modificare(RBTree* tree) {
	int pret, gramaj, val;
	double c;
	RBNode* node;
	string nume, producator, aux1, aux2;

	cout << "Introduceti denumirea produsului: ";
	while (true) {
		getline(cin, nume);  transform(nume.begin(), nume.end(), nume.begin(), tolower); nume[0] = (char)toupper(nume[0]);
		if (nume.size())
			break;
		cout << "Denumirea produsului: ";
	}

	node = tree->search(tree->root, nume);

	if (dynamic_cast<Tableta*>(node->key)) {
		tree->del(node);

		cout << "Noul producator al produsului: ";
		while (true) {
			getline(cin, producator);  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
			if (producator.size())
				break;
			cout << "Noul producator al produsului: ";
		}
		cout << "Noul pret al produsului: ";
		if (!(cin >> pret))
			eroare(pret);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Noua substanta activa: ";
		while (true) {
			getline(cin, aux1);  transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Noua substanta activa: ";
		}
		while (true) {
			cout << "Necesita prescriptie(DA/NU): ";
			getline(cin, aux2); transform(aux2.begin(), aux2.end(), aux2.begin(), toupper);
			if (aux2 == "DA" || aux2 == "NU")
				break;
		}
		cout << "Noul gramaj al tabletei: ";
		if (!(cin >> gramaj))
			eroare(gramaj);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		tree->RBInsert(tree->createNode(new Tableta(nume, producator, pret, aux1, aux2 == "DA", gramaj)));

		cout << "\n\u001b[32mProdusul a fost modificat cu succes!\u001b[0m\n";
		return;
	}
	else if (dynamic_cast<Sirop*>(node->key)) {
		tree->del(node);

		cout << "Noul producator al produsului: ";
		while (true) {
			getline(cin, producator);  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
			if (producator.size())
				break;
			cout << "Noul producator al produsului: ";
		}
		cout << "Noul pret al produsului: ";
		if (!(cin >> pret))
			eroare(pret);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Noua substanta activa: ";
		while (true) {
			getline(cin, aux1);  transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Noua substanta activa: ";
		}
		while (true) {
			cout << "Necesita prescriptie(DA/NU): ";
			getline(cin, aux2); transform(aux2.begin(), aux2.end(), aux2.begin(), toupper);
			if (aux2 == "DA" || aux2 == "NU")
				break;
		}
		cout << "Noua concentratie: ";
		if (!(cin >> c))
			eroare(c);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		tree->RBInsert(tree->createNode(new Sirop(nume, producator, pret, aux1, aux2 == "DA", c)));

		cout << "\n\u001b[32mProdusul a fost modificat cu succes!\u001b[0m\n";
		return;
	}
	else if (dynamic_cast<Unguent*>(node->key)) {
		tree->del(node);

		cout << "Noul producator al produsului: ";
		while (true) {
			getline(cin, producator);  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
			if (producator.size())
				break;
			cout << "Noul producator al produsului: ";
		}
		cout << "Noul pret al produsului: ";
		if (!(cin >> pret))
			eroare(pret);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin.get();
		cout << "Noua substanta activa: ";
		while (true) {
			getline(cin, aux1);  transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Noua substanta activa: ";
		}
		while (true) {
			cout << "Necesita prescriptie(DA/NU): ";
			getline(cin, aux2); transform(aux2.begin(), aux2.end(), aux2.begin(), toupper);
			if (aux2 == "DA" || aux2 == "NU")
				break;
		}
		cout << "Numarul de luni valabile de la deschidere: ";
		if (!(cin >> val))
			eroare(val);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		tree->RBInsert(tree->createNode(new Unguent(nume, producator, pret, aux1, aux2 == "DA", val)));

		cout << "\n\u001b[32mProdusul a fost modificat cu succes!\u001b[0m\n";
		return;
	}
	else if (dynamic_cast<Cosmetice*>(node->key)) {
		tree->del(node);

		cout << "Noul producator al produsului: ";
		while (true) {
			getline(cin, producator);  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
			if (producator.size())
				break;
			cout << "Noul producator al produsului: ";
		}
		cout << "Noul pret al produsului: ";
		if (!(cin >> pret))
			eroare(pret);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Noua zona de plicare: ";
		while (true) {
			getline(cin, aux1);  transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Noua zona de aplicare: ";
		}

		tree->RBInsert(tree->createNode(new Cosmetice(nume, producator, pret, aux1)));

		cout << "\n\u001b[32mProdusul a fost modificat cu succes!\u001b[0m\n";
		return;
	}
	else if (dynamic_cast<Naturiste*>(node->key)) {
		tree->del(node);

		cout << "Noul producator al produsului: ";
		while (true) {
			getline(cin, producator);  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
			if (producator.size())
				break;
			cout << "Noul producator al produsului: ";
		}
		cout << "Noul pret al produsului: ";
		if (!(cin >> pret))
			eroare(pret);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Noua utilizare a produsului naturist: ";
		while (true) {
			getline(cin, aux1);  transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Noua utilizare a produsului naturist: ";
		}

		tree->RBInsert(tree->createNode(new Naturiste(nume, producator, pret, aux1)));

		cout << "\n\u001b[32mProdusul a fost modificat cu succes!\u001b[0m\n";
		return;
	}
	else if (dynamic_cast<Medicament*>(node->key)) {
		tree->del(node);

		cout << "Noul producator al produsului: ";
		while (true) {
			getline(cin, producator);  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
			if (producator.size())
				break;
			cout << "Noul producator al produsului: ";
		}
		cout << "Noul pret al produsului: ";
		if (!(cin >> pret))
			eroare(pret);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Noua substanta activa: ";
		while (true) {
			getline(cin, aux1);  transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			if (aux1.size())
				break;
			cout << "Noua substanta activa: ";
		}
		while (true) {
			cout << "Necesita prescriptie(DA/NU): ";
			getline(cin, aux2); transform(aux2.begin(), aux2.end(), aux2.begin(), toupper);
			if (aux2 == "DA" || aux2 == "NU")
				break;
		}

		tree->RBInsert(tree->createNode(new Medicament(nume, producator, pret, aux1, aux2 == "DA")));

		cout << "\n\u001b[32mProdusul a fost modificat cu succes!\u001b[0m\n";
		return;
	}
	else if (dynamic_cast<Produs*>(node->key)) {
		tree->del(node);

		cout << "Noul producator al produsului: ";
		while (true) {
			getline(cin, producator);  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
			if (producator.size())
				break;
			cout << "Noul producator al produsului: ";
		}
		cout << "Noul pret al produsului: ";
		if (!(cin >> pret))
			eroare(pret);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		tree->RBInsert(tree->createNode(new Produs(nume, producator, pret)));

		cout << "\n\u001b[32mProdusul a fost modificat cu succes!\u001b[0m\n";
		return;
	}

	cout << "\n\u001b[31mProdusul nu exista!\u001b[0m\n";
}

void Produs::stergere(RBTree* tree) {
	string nume;
	RBNode* node;

	cout << "Introduceti denumirea produsului: ";
	while (true) {
		getline(cin, nume); transform(nume.begin(), nume.end(), nume.begin(), tolower); nume[0] = (char)toupper(nume[0]);
		if (nume.size())
			break;
		cout << "Denumirea produsului: ";
	}
	
	node = tree->search(tree->root, nume);
	if (!tree->isNil(node)) {
		cout << '\n' << *node->key << '\n';
		tree->del(node);
		cout << "\u001b[32mProdusul a fost sters!\u001b[0m\n";
	}
	else
		cout << "\u001b[31mProdusul nu exista!\u001b[0m\n";
}

void Produs::afisare(RBTree* tree){
	tree->bfs();
}

void Produs::cautare(RBTree* tree) {
	string nume;
	RBNode* node;

	cout << "Introduceti denumirea produsului: ";
	while (true) {
		getline(cin, nume); transform(nume.begin(), nume.end(), nume.begin(), tolower); nume[0] = (char)toupper(nume[0]);
		if (nume.size())
			break;
		cout << "Denumirea produsului: ";
	}

	node = tree->search(tree->root, nume);
	if(!tree->isNil(node))
		cout << '\n' << *node->key << '\n';
	else
		cout << "\u001b[31mProdusul cautat nu exista!\u001b[0m\n";
}

void Produs::salvare_date(RBTree* tree) {
	queue<RBNode*> q;
	string eliberare;
	ofstream out("produse.txt");
	int n = tree->nodes;

	q.push(tree->root);
	out << n << '\n';

	while (q.empty() == false) {
		RBNode* node = q.front();
		
		if (dynamic_cast<Tableta*>(node->key)) {
			out << "Tableta;" << node->key->denumire << ';' << node->key->producator << ';' << node->key->pret;
			eliberare = node->key->getEliberare() ? "DA" : "NU";
			out << ';' << node->key->getSubstanta() << ';' << eliberare << ';' << node->key->getGramaj();
		}
		else if (dynamic_cast<Sirop*>(node->key)) {
			out << "Sirop;" << node->key->denumire << ';' << node->key->producator << ';' << node->key->pret;
			eliberare = node->key->getEliberare() ? "DA" : "NU";
			out << ';' << node->key->getSubstanta() << ';' << eliberare << ';' << node->key->getConcentratie();
		}
		else if (dynamic_cast<Unguent*>(node->key)) {
			out << "Unguent;" << node->key->denumire << ';' << node->key->producator << ';' << node->key->pret;
			eliberare = node->key->getEliberare() ? "DA" : "NU";
			out << ';' << node->key->getSubstanta() << ';' << eliberare << ';' << node->key->getValabilitate();
		}
		else if (dynamic_cast<Medicament*>(node->key)) {
			out << "Medicament;" << node->key->denumire << ';' << node->key->producator << ';' << node->key->pret;
			eliberare = node->key->getEliberare() ? "DA" : "NU";
			out << ';' << node->key->getSubstanta() << ';' << eliberare;
		}
		else if (dynamic_cast<Cosmetice*>(node->key)) {
			out << "Cosmetic;" << node->key->denumire << ';' << node->key->producator << ';' << node->key->pret;
			out << ';' << node->key->getZona();
		}
		else if (dynamic_cast<Naturiste*>(node->key)) {
			out << "Naturist;" << node->key->denumire << ';' << node->key->producator << ';' << node->key->pret;
			out << ';' << node->key->getUtilizare();
		}
		else if (dynamic_cast<Produs*>(node->key)) {
			out << "Produs;" << node->key->denumire << ';' << node->key->producator << ';' << node->key->pret;
		}

		out << '\n';
		delete node->key;
		q.pop();

		if (node->left != RBNode::Nil)
			q.push(node->left);
		if (node->right != RBNode::Nil)
			q.push(node->right);
	}

	out.close();
}

bool Produs::filter_producator(Produs* p, string prod) {
	return (p->getProducator() == prod);
}

bool Produs::filter_pret(Produs* p, string pret) {
	return p->getPret() == stoi(pret);
}

bool Produs::filtrare(RBTree* tree, string key, bool(* filter)(Produs*, string)) {
	bool ok = false;
	queue<RBNode*> q;
	int i = 0;

	q.push(tree->root);

	while (q.empty() == false) {
		i++;
		RBNode* node = q.front();

		if (filter(node->key, key)) {
			cout << *node->key << '\n';
			ok = true;
		}

		q.pop();
		if (node->left != RBNode::Nil)
			q.push(node->left);
		if (node->right != RBNode::Nil)
			q.push(node->right);
	}

	return ok;
}

bool Produs::pret1(Produs* p1, Produs* p2) {
	return (p1->getPret() < p2->getPret());
}

bool Produs::pret2(Produs* p1, Produs* p2) {
	return (p1->getPret() > p2->getPret());
}

void Produs::sortare(RBTree* tree, bool (*comparator)(Produs*, Produs*)) {
	vector<Produs*> tab;
	RBNode* curr, * pre;
	int i = 1;

	curr = tree->root;
	while (!tree->isNil(curr)) {
		if (tree->isNil(curr->left)) {
			tab.push_back(curr->key);
			curr = curr->right;
		}
		else {
			pre = curr->left;
			while (!tree->isNil(pre->right) && pre->right != curr)
				pre = pre->right;

			if (tree->isNil(pre->right)) {
				pre->right = curr;
				curr = curr->left;
			}
			else {
				pre->right = RBNode::Nil;
				tab.push_back(curr->key);
				curr = curr->right;
			}
		}
	}

	sort(tab.begin(), tab.end(), comparator);
	for (auto it : tab) {
		cout << i++ << ". " << *it << '\n';
	}
}

ostream& operator<<(ostream& st, const Produs& p) {
	return p.afisare(st);
}
