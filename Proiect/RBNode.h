#pragma once

class Produs;

#include "Produs.h"

class RBNode {
public:
    Produs* key;
    RBNode* p;
    RBNode* left;
    RBNode* right;
    enum color { RED, BLACK };
    color col;

    static RBNode* Nil;

    RBNode(Produs* key, RBNode* l = Nil, RBNode* r = Nil, RBNode* parent = Nil, color c = RBNode::BLACK) :
        key(key), p(parent), left(l), right(r), col(c) { };

    ~RBNode();
};

