#pragma once
class Produs;
#include "Products/Produs.h"

/**
 * Implementation of a red-black tree node
 *
 * The RBNode contains pointers to the actual
 * key and it`s color, left and right child
 * nodes and the parent node.
 */
class RBNode {
public:
    Produs* key;
    RBNode* p, * left, * right;

    /**
    * Supported node colors for a
    * red-black tree node.
    */
    enum class color { RED, BLACK };
    color col;

    /// Pointer to the single entity of the Nil.
    static RBNode* Nil;

    /**
    * Constructor
    * 
    * Initializes a RBNode with all 
    * of its members.
    */
    RBNode(Produs* key, RBNode* l = Nil, RBNode* r = Nil, RBNode* parent = Nil, color c = RBNode::color::BLACK) :
        key(key), p(parent), left(l), right(r), col(c) { };

    /**
    * Default destructor.
    */
    ~RBNode();
};
