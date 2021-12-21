#pragma once
class Produs;
#include "../Products/Produs.h"

class RBNode {
public:
    Produs* key;
    RBNode* p;
    RBNode* left;
    RBNode* right;
    enum class color { RED, BLACK };
    color col;

    static RBNode* Nil;

    RBNode(Produs* key, RBNode* l = Nil, RBNode* r = Nil, RBNode* parent = Nil, color c = RBNode::color::BLACK) :
        key(key), p(parent), left(l), right(r), col(c) { };

    ~RBNode();
};
