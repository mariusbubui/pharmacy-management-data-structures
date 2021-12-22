#pragma once
#include "../Headers/DataStructures/RBTree.h"

void menu();
void show_menu();
void submenu_sort(RBTree*);
void show_submenusort();
void submenu_filter(RBTree*);
void show_submenufil();
void return_menu(void (*)());
void clear_screen(string);