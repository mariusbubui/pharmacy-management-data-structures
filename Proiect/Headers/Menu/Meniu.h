#pragma once
#include "../Headers/DataStructures/RBTree.h"

/**
* Computes the user input
* and operation management.
*/
void menu();

/**
* Print the menu.
*/
void show_menu();

/**
* Computes the user input
* and operation management
* for sorting operation.
*/
void submenu_sort(RBTree*);

/**
* Print the submenu for sorting.
*/
void show_submenusort();

/**
* Computes the user input
* and operation management
* for filtering operation.
*/
void submenu_filter(RBTree*);

/**
* Print the submenu for filtering.
*/
void show_submenufil();

/**
* Computes the return to
* the previous menu.
*/
void return_menu(void (*)());

/**
* Clears the screen in terminal.
*/
void clear_screen(string);