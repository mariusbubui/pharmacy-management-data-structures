#pragma once

class RBNode;
#include "RBNode.h"
#include <string>

using std::string;

class RBTree{
public:
    RBNode* root;
    int nodes;

    RBTree();

    RBTree(Produs*);

    ~RBTree();

    void LeftRotate(RBNode*);

    /**
     * RightRotate(y) also assumes that y is the right child of
     * an RBNode x
     */
    void RightRotate(RBNode*);

    RBNode* createNode(Produs*);

    bool isNil(RBNode*);

    RBNode* search(RBNode*, string);

    /**
     * maximum(w) returns the node with maximum key in the
     * RB-tree with root node w
     */
    RBNode* maximum(RBNode*);

    /**
     * minimum(w) returns the node with minimum key in the
     * RB-tree with root node w
     */
    RBNode* minimum(RBNode*);

    /**
     * successor(w) returns the successor of node w in the
     * RB-tree to which node w belongs
     */
    RBNode* successor(RBNode*);

    RBNode* predecessor(RBNode*);

    /**
     * RBInsert(z) inserts node z in this RB-tree
     */
    void RBInsert(RBNode*);

    RBNode* del(RBNode*);

    void RBDeleteFixup(RBNode*);

    void RBInsertFixup(RBNode*);

    int inorder(RBNode*, int);

    void inorder();

    int rinorder(RBNode*, int);

    void rinorder();
};
