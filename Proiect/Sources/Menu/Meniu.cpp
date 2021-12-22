#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <algorithm>
#include "../Headers/DataStructures/HashTable.h"
#include "../Headers/Products/Produs.h"
#include "../Headers/Menu/Meniu.h"

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::for_each;

enum class string_code { zero, one, two, three, four, five, six, seven, eight, err };

string_code conversion(string const& s) {
    if (s == "0") return string_code::zero;
    if (s == "1") return string_code::one;
    if (s == "2") return string_code::two;
    if (s == "3") return string_code::three;
    if (s == "4") return string_code::four;
    if (s == "5") return string_code::five;
    if (s == "6") return string_code::six;
    if (s == "7") return string_code::seven;
    if (s == "8") return string_code::eight;
    return string_code::err;
}

void show_menu(){
    cout << "\x1B[96mManagment produse farmacie\033[0m\n\n";
    cout << " ____________________________ \n";
    cout << "|                            |\n";
    cout << "|  (\x1B[96m1\033[0m). Afisare produse      |\n";
    cout << "|  (\x1B[96m2\033[0m). Cautare produs       |\n";
    cout << "|  (\x1B[96m3\033[0m). Disponibilitate      |\n";
    cout << "|  (\x1B[96m4\033[0m). Adaugare produs      |\n";
    cout << "|  (\x1B[96m5\033[0m). Modificare produs    |\n";
    cout << "|  (\x1B[96m6\033[0m). Stergere produs      |\n";
    cout << "|  (\x1B[96m7\033[0m). Filtrare produse     |\n";
    cout << "|  (\x1B[96m8\033[0m). Sortare produse      |\n";
    cout << "|  (\x1B[96m0\033[0m). Iesire               |\n";
    cout << "|____________________________|\n\n";
    cout << "Introduceti o optiune: ";
}

void show_submenusort() {
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

void show_submenufil() {
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

    show_submenusort();

    do {
        cin >> optiune;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (conversion(optiune)) {
        case string_code::zero:
            ok = false;
            break;

        case string_code::one:
            clear_screen("Produsele sortate crescator dupa pret:");
            Produs::sortare(tree, Produs::pret1);
            return_menu(show_submenusort);
            break;

        case string_code::two:
            clear_screen("Produsele sortate descrescator dupa pret:");
            Produs::sortare(tree, Produs::pret2);
            return_menu(show_submenusort);
            break;

        case string_code::three:
            clear_screen("Produsele sortate alfabetic dupa denumire:");
            tree->inorder();
            return_menu(show_submenusort);
            break;

        case string_code::four:
            clear_screen("Produsele sortate invers alfabetic dupa denumire:");
            tree->rinorder();
            return_menu(show_submenusort);
            break;

        default:
            cout << "Introduceti o optiune corecta: ";
        }
    } while (ok);
}

void submenu_filter(RBTree* tree) {
    string optiune, aux;
    bool ok = true, digit = true;

    show_submenufil();

    do {
        cin >> optiune;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (conversion(optiune)) {
        case string_code::zero:
            ok = false;
            break;

        case string_code::one:
            cout << "Introduceti pretul dupa care sa se filtreaze: ";
            do {
                digit = true; getline(cin, aux);

                if (aux[0] == '0')
                    digit = false;
                for (unsigned int i = 0; i < aux.size() && digit; i++)
                    if (!isdigit(aux[i]))
                        digit = false;

                if (!digit)
                    cout << "\u001b[31mIntroduceti un pret valid: \u001b[0m";
            } while (!digit);

            clear_screen("Produsele cu pretul de " + aux + " RON:");

            if (!Produs::filtrare(tree, aux, Produs::filter_pret))
                cout << "\u001b[31mNu exista produse cu acest pret!\u001b[0m\n";

            return_menu(show_submenufil);
            break;

        case string_code::two:
            cout << "Introduceti producatorul dupa care sa se filtreaze: ";
            getline(cin, aux); for_each(aux.begin(), aux.end(), tolower); aux[0] = (char)toupper(aux[0]);

            clear_screen("Produsele cu producatorul " + aux + ":");

            if (!Produs::filtrare(tree, aux, Produs::filter_producator))
                cout << "\u001b[31mNu exista produse de la acest producator!\u001b[0m\n";
        
            return_menu(show_submenufil);
            break;

        default:
            cout << "Introduceti o optiune corecta: ";
        }
    } while (ok);
}

void clear_screen(string const text) {
    system("cls");
    cout << "\x1B[96m" << text << "\033[0m\n\n";
}

void return_menu(void (*show)()) {
    printf("\n\x1B[96mApasati o tasta pentru a continua...\033[0m");
    (void)_getch();
    system("cls");
    show();
}

void menu() {
    RBTree* tree = new RBTree();
    HashTable* dict = new HashTable();

    string optiune;
    bool ok = true;

    show_menu();

    Produs::initializare(tree, dict);

    do {
        cin >> optiune;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (conversion(optiune)) {
        case string_code::zero:
            ok = false;

            Produs::salvare_date(tree, dict);
            cout << "\u001b[32mDatele au fost salvate in fisier!\u001b[0m\n";

            delete tree;
            delete dict;

            break;

        case string_code::one:
            clear_screen("Lista de produse");
            Produs::afisare(tree, dict);
            return_menu(show_menu);
            break;

        case string_code::two:
            clear_screen("Cautare produs");
            Produs::cautare(tree, dict);
            return_menu(show_menu);
            break;

        case string_code::three:
            clear_screen("Verificare disponibilitate");
            Produs::disponibilitate(dict);
            return_menu(show_menu);
            break;

        case string_code::four:
            clear_screen("Adaugare produs");
            Produs::adaugare(tree, dict);
            return_menu(show_menu);
            break;

        case string_code::five:
            clear_screen("Modificare produs");
            Produs::modificare(tree, dict);
            return_menu(show_menu);
            break;

        case string_code::six:
            clear_screen("Stergere produs");
            Produs::stergere(tree, dict);
            return_menu(show_menu);
            break;

        case string_code::seven:
            system("cls");
            submenu_filter(tree);
            return_menu(show_menu);
            break;

        case string_code::eight:
            system("cls");
            submenu_sort(tree);
            return_menu(show_menu);
            break;

        default:
            cout << "Introduceti o optiune corecta: ";
        }
    } while (ok);
}