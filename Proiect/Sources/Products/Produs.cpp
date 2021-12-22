#define _CRT_SECURE_NO_WARNINGS 1

#include "Products/Produs.h"
#include "Products/Cosmetice.h"
#include "Products/Naturiste.h"
#include "Products/Medicament.h"
#include "Products/Tableta.h"
#include "Products/Sirop.h"
#include "Products/Unguent.h"
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

void Produs::initializare(RBTree* tree, HashTable* dict) {
	ifstream in("Resources/products.txt");
	if (!in.is_open())
		return;

	string tip, nume, producator, aux1, aux2;
	int pret, gramaj, val, disponibilitate;
	Produs* tmp  = nullptr;
	double c;
	int n;

	in >> n;
	in.ignore(256, '\n');

	for (int i = 0; i < n; i++) {
		getline(in, tip, ';');  transform(tip.begin(), tip.end(), tip.begin(), tolower); tip[0] = (char)toupper(tip[0]);
		getline(in, nume, ';');  transform(nume.begin(), nume.end(), nume.begin(), tolower); nume[0] = (char)toupper(nume[0]);
		getline(in, producator, ';');  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
		in >> pret; in.get();

		if (tip == "Produs") {
			tree->RBInsert(tree->createNode(tmp = new Produs(nume, producator, pret)));
		}
		else if (tip == "Cosmetic") {
			getline(in, aux1, ';'); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			tree->RBInsert(tree->createNode(tmp = new Cosmetice(nume, producator, pret, aux1)));
		}
		else if (tip == "Naturist") {
			getline(in, aux1, ';'); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			tree->RBInsert(tree->createNode(tmp = new Naturiste(nume, producator, pret, aux1)));
		}
		else if (tip == "Medicament") {
			getline(in, aux1, ';'); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			getline(in, aux2, ';');
			tree->RBInsert(tree->createNode(tmp = new Medicament(nume, producator, pret, aux1, aux2 == "DA")));
		}
		else if (tip == "Tableta") {
			getline(in, aux1, ';'); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			getline(in, aux2, ';');
			in >> gramaj; in.get();
			tree->RBInsert(tree->createNode(tmp = new Tableta(nume, producator, pret, aux1, aux2 == "DA", gramaj)));
		}
		else if (tip == "Sirop") {
			getline(in, aux1, ';'); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			getline(in, aux2, ';');
			in >> c; in.get();
			tree->RBInsert(tree->createNode(tmp = new Sirop(nume, producator, pret, aux1, aux2 == "DA", c)));
		}
		else if (tip == "Unguent") {
			getline(in, aux1, ';'); transform(aux1.begin(), aux1.end(), aux1.begin(), tolower); aux1[0] = (char)toupper(aux1[0]);
			getline(in, aux2, ';');
			in >> val; in.get();
			tree->RBInsert(tree->createNode(tmp = new Unguent(nume, producator, pret, aux1, aux2 == "DA", val)));
		}

		in >> disponibilitate;

		if(tmp!= nullptr)
			dict->insert(tmp->getDenumire(), disponibilitate == 0 ? false : true);

		in.ignore(256, '\n');
	}
	in.close();
}

void Produs::adaugare(RBTree* tree, HashTable* dict) {
	string tip, nume, producator, aux1, aux2, disp;
	int pret, gramaj, val;
	double c;

	cout << "Introduceti tipul produsului(PRODUS/COSMETICE/NATURISTE/MEDICAMENT/TABLETA/SIROP/UNGUENT): ";
	while (true) {
		getline(cin, tip); transform(tip.begin(), tip.end(), tip.begin(), toupper);
		if (tip == "PRODUS" || tip == "MEDICAMENT" || tip == "TABLETA" || tip == "SIROP" || tip == "UNGUENT" || tip == "COSMETICE" || tip == "NATURISTE")
			break;
		cout << "\u001b[31mIntroduceti un tip existent: \u001b[0m";
	}

	cout << "Denumirea produsului: ";
	while (true) {
		getline(cin, nume);  transform(nume.begin(), nume.end(), nume.begin(), tolower); nume[0] = (char)toupper(nume[0]);
		if (nume.size())
			break;
		cout << "Denumirea produsului: ";
	}

	cout << "Producatorul produsului: ";
	while (true) {
		getline(cin, producator);  transform(producator.begin(), producator.end(), producator.begin(), tolower); producator[0] = (char)toupper(producator[0]);
		if (producator.size())
			break;
		cout << "Producatorul produsului: ";
	}

	cout << "Pretul produsului: ";
	if (!(cin >> pret))
		eroare(pret);
	cin.get();

	cout << "Disponibilitatea produsului(0/1): ";
	while (true) {
		getline(cin, disp);
		if (disp == "1" || disp == "0") {
			if (disp == "1")
				dict->insert(nume, true);
			else
				dict->insert(nume, false);

			break;
		}
		cout << "\u001b[31mIntroduceti 0/1: \u001b[0m";
	}

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

void Produs::modificare(RBTree* tree, HashTable* dict) {
	int pret, gramaj, val;
	double c;
	RBNode* node;
	Produs* tmp = nullptr;
	string nume, producator, aux1, aux2;

	cout << "Introduceti denumirea produsului: ";
	while (true) {
		getline(cin, nume);  transform(nume.begin(), nume.end(), nume.begin(), tolower); nume[0] = (char)toupper(nume[0]);
		if (nume.size())
			break;
		cout << "Denumirea produsului: ";
	}

	node = tree->search(tree->root, nume);
	dict->del(node->key->denumire);

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

		tree->RBInsert(tree->createNode(tmp = new Tableta(nume, producator, pret, aux1, aux2 == "DA", gramaj)));
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

		tree->RBInsert(tree->createNode(tmp = new Sirop(nume, producator, pret, aux1, aux2 == "DA", c)));
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

		tree->RBInsert(tree->createNode(tmp = new Unguent(nume, producator, pret, aux1, aux2 == "DA", val)));
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

		tree->RBInsert(tree->createNode(tmp = new Cosmetice(nume, producator, pret, aux1)));
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

		tree->RBInsert(tree->createNode(tmp = new Naturiste(nume, producator, pret, aux1)));
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

		tree->RBInsert(tree->createNode(tmp = new Medicament(nume, producator, pret, aux1, aux2 == "DA")));
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

		tree->RBInsert(tree->createNode(tmp = new Produs(nume, producator, pret)));
	}
	else {
		cout << "\n\u001b[31mProdusul nu exista!\u001b[0m\n";
		return;
	}

	cout << "Noua disponibilitate a produsului(0/1): ";
	while (true) {
		getline(cin, aux1);
		if (aux1 == "1" || aux1 == "0") {
			if (aux1 == "1")
				dict->insert(nume, true);
			else
				dict->insert(nume, false);

			break;
		}
		cout << "\u001b[31mIntroduceti 0/1: \u001b[0m";
	}

	cout << "\n\u001b[32mProdusul a fost modificat cu succes!\u001b[0m\n";
}

void Produs::stergere(RBTree* tree, HashTable* dict) {
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

		dict->del(node->key->denumire);
		tree->del(node);

		cout << "\u001b[32mProdusul a fost sters!\u001b[0m\n";
	}
	else
		cout << "\u001b[31mProdusul nu exista!\u001b[0m\n";
}

void Produs::afisare(RBTree* tree, HashTable* dict){
	queue<RBNode*> q;
	int i = 0;
	q.push(tree->root);

	while (q.empty() == false) {
		RBNode* node = q.front();
		cout << ++i << ". " << *node->key << "Disponibilitate: " << dict->get(node->key->denumire) << "\n\n";
		q.pop();
		
		if (node->left != RBNode::Nil)
			q.push(node->left);
		if (node->right != RBNode::Nil)
			q.push(node->right);
	}
}

void Produs::cautare(RBTree* tree, HashTable* dict) {
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
		cout << '\n' << *node->key << "Disponibilitate: " << dict->get(node->key->denumire) << "\n\n";
	else
		cout << "\u001b[31mProdusul cautat nu exista!\u001b[0m\n";
}

void Produs::disponibilitate(HashTable* dict){
	string nume;

	cout << "Introduceti denumirea produsului: ";
	while (true) {
		getline(cin, nume); transform(nume.begin(), nume.end(), nume.begin(), tolower); nume[0] = (char)toupper(nume[0]);
		if (nume.size())
			break;
		cout << "Denumirea produsului: ";
	}

	if (dict->get(nume) == 1)
		cout << "Produsul este disponibil!\n";
	else if (dict->get(nume) == false)
		cout << "Produsul nu este disponibil!\n";
	else
		cout << "\u001b[31mProdusul cautat nu exista!\u001b[0m\n";
}

void Produs::salvare_date(RBTree* tree, HashTable* dict) {
	queue<RBNode*> q;
	string eliberare;
	ofstream out("Resources/products.txt");
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

		if(node->key != NULL)
			out << ';' << dict->get(node->key->denumire) ? 1 : 0;
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
