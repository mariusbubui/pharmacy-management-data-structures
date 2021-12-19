#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <algorithm>
#include "RBTree.h"
#include "Produs.h"
using std::cin;
using std::cout;
using std::vector;
using std::string;

enum class string_code { zero, one, two, three, four, five, six, seven, err };

string_code conversie(string const& s) {
    if (s == "0") return string_code::zero;
    if (s == "1") return string_code::one;
    if (s == "2") return string_code::two;
    if (s == "3") return string_code::three;
    if (s == "4") return string_code::four;
    if (s == "5") return string_code::five;
    if (s == "6") return string_code::six;
    if (s == "7") return string_code::seven;
    return string_code::err;
}

void print_menu()
{
    cout << "\x1B[96mManagment produse farmacie\033[0m\n\n";
    cout << " ____________________________ \n";
    cout << "|                            |\n";
    cout << "|  (\x1B[96m1\033[0m). Afisare produse      |\n";
    cout << "|  (\x1B[96m2\033[0m). Adaugare produs      |\n";
    cout << "|  (\x1B[96m3\033[0m). Modificare produs    |\n";
    cout << "|  (\x1B[96m4\033[0m). Stergere produs      |\n";
    cout << "|  (\x1B[96m5\033[0m). Cautare produs       |\n";
    cout << "|  (\x1B[96m6\033[0m). Filtrare produse     |\n";
    cout << "|  (\x1B[96m7\033[0m). Sortare produse      |\n";
    cout << "|  (\x1B[96m0\033[0m). Iesire               |\n";
    cout << "|____________________________|\n\n";
    cout << "Introduceti o optiune: ";
}

void print_submenusort() {
    cout << "\x1B[96mSortare produse\033[0m\n";
    cout << " ________________________________________________\n";
    cout << "|                                                |\n";
    cout << "|  (\x1B[96m1\033[0m). Sortare crescatoare dupa pret            |\n";
    cout << "|  (\x1B[96m2\033[0m). Sortare descrescatoare dupa pret         |\n";
    cout << "|  (\x1B[96m3\033[0m). Sortare alfabetica dupa denumire         |\n";
    cout << "|  (\x1B[96m4\033[0m). Sortare invers alfabetica dupa denumire  |\n";
    cout << "|  (\x1B[96m0\033[0m). Intoarcere la meniul principal           |\n";
    cout << "|________________________________________________|\n\n";
    cout << "Introduceti o optiune: ";
}

void print_submenufil() {
    cout << "\x1B[96mFiltrare produse\033[0m\n";
    cout << " ________________________________________\n";
    cout << "|                                        |\n";
    cout << "|  (\x1B[96m1\033[0m). Filtrare dupa pret               |\n";
    cout << "|  (\x1B[96m2\033[0m). Filtrare dupa producator         |\n";
    cout << "|  (\x1B[96m0\033[0m). Intoarcere la meniul principal   |\n";
    cout << "|________________________________________|\n\n";
    cout << "Introduceti o optiune: ";
}

void submenu_sort(RBTree* tree) {
    string optiune;
    bool ok = true;
    print_submenusort();
    do {
        cin >> optiune;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (conversie(optiune)) {
        case string_code::zero:
            ok = false;
            break;
        case string_code::one:
            system("cls");
            cout << "\x1B[96mProdusele sortate crescator dupa pret:\033[0m\n\n";
            //Produs::sortare(tab, Produs::pret1);
            printf("\n\x1B[96mApasati o tasta pentru a continua...\033[0m");
            (void)_getch();
            system("cls");
            print_submenusort();
            break;
        case string_code::two:
            system("cls");
            cout << "\x1B[96mProdusele sortate descrescator dupa pret:\033[0m\n\n";
            //Produs::sortare(tab, Produs::pret2);
            printf("\n\x1B[96mApasati o tasta pentru a continua...\033[0m");
            (void)_getch();
            system("cls");
            print_submenusort();
            break;
        case string_code::three:
            system("cls");
            cout << "\x1B[96mProdusele sortate alfabetic dupa denumire:\033[0m\n\n";
            Produs::afisare(tree);
            printf("\n\x1B[96mApasati o tasta pentru a continua...\033[0m");
            (void)_getch();
            system("cls");
            print_submenusort();
            break;
        case string_code::four:
            system("cls");
            cout << "\x1B[96mProdusele sortate invers alfabetic dupa denumire:\033[0m\n\n";
            //Produs::sortare(tab, Produs::denumire2);
            printf("\n\x1B[96mApasati o tasta pentru a continua...\033[0m");
            (void)_getch();
            system("cls");
            print_submenusort();
            break;
        default:
            cout << "Introduceti o optiune corecta: ";
        }
    } while (ok);
}

void submenu_filter(vector<Produs*>& tab) {
    string optiune, aux;
    bool ok = true, digit = true;
    print_submenufil();
    do {
        cin >> optiune;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (conversie(optiune)) {
        case string_code::zero:
            ok = false;
            break;
        case string_code::one:
            cout << "Introduceti pretul dupa care sa se filtreaze: ";
            do {
                digit = true;
                getline(cin, aux);
                if (aux[0] == '0')
                    digit = false;
                for (unsigned int i = 0; i < aux.size() && digit; i++)
                    if (!isdigit(aux[i]))
                        digit = false;
                if (!digit)
                    cout << "\u001b[31mIntroduceti un pret valid: \u001b[0m";
            } while (!digit);
            system("cls");
            cout << "\x1B[96mProdusele cu pretul " << aux << " RON:\033[0m\n\n";
            if (!Produs::filtrare(tab, aux, Produs::f_pret))
                cout << "\u001b[31mNu exista produse cu acest pret!\u001b[0m\n";
            printf("\n\x1B[96mApasati o tasta pentru a continua...\033[0m");
            (void)_getch();
            system("cls");
            print_submenufil();
            break;
        case string_code::two:
            cout << "Introduceti producatorul dupa care sa se filtreaze: ";
            getline(cin, aux);  std::transform(aux.begin(), aux.end(), aux.begin(), tolower); aux[0] = (char)toupper(aux[0]);
            system("cls");
            cout << "\x1B[96mProdusele cu producatorul " << aux << ":\033[0m\n\n";
            if (!Produs::filtrare(tab, aux, Produs::f_producator))
                cout << "\u001b[31mNu exista produse de la acest producator!\u001b[0m\n";
            printf("\n\x1B[96mApasati o tasta pentru a continua...\033[0m");
            (void)_getch();
            system("cls");
            print_submenufil();
            break;
        default:
            cout << "Introduceti o optiune corecta: ";
        }
    } while (ok);
}

void revenire_meniu() {
    printf("\n\x1B[96mApasati o tasta pentru a continua...\033[0m");
    (void)_getch();
    system("cls");
    print_menu();
}

void menu()
{
    string optiune;
    bool ok = true;
    print_menu();
    RBTree* tree = new RBTree();
    Produs::initializare(tree);
    do {
        cin >> optiune;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (conversie(optiune)) {
        case string_code::zero:
            ok = false;
            Produs::salvare_date(tree);
            delete tree;
            cout << "\u001b[32mDatele au fost salvate in fisier!\u001b[0m\n";
            break;
        case string_code::one:
            system("cls");
            cout << "\x1B[96mLista de produse\033[0m\n\n";
            Produs::afisare(tree);
            revenire_meniu();
            break;
        case string_code::two:
            system("cls");
            cout << "\x1B[96mAdaugare produs\033[0m\n\n";
            //Produs::adaugare(tab);
            revenire_meniu();
            break;
        case string_code::three:
            system("cls");
            cout << "\x1B[96mModificare produs\033[0m\n\n";
            //Produs::modificare(tab);
            revenire_meniu();
            break;
        case string_code::four:
            system("cls");
            cout << "\x1B[96mStergere produs\033[0m\n\n";
            Produs::stergere(tree);
            revenire_meniu();
            break;
        case string_code::five:
            system("cls");
            cout << "\x1B[96mCautare produs\033[0m\n\n";
            Produs::cautare(tree);
            revenire_meniu();
            break;
        case string_code::six:
            system("cls");
            //submenu_filter(tab);
            revenire_meniu();
            break;
        case string_code::seven:
            system("cls");
            submenu_sort(tree);
            revenire_meniu();
            break;
        default:
            cout << "Introduceti o optiune corecta: ";
        }
    } while (ok);
}