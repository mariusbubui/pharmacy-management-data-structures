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

    RBTree(Produs* p);

    ~RBTree();

    void LeftRotate(RBNode* x);

    /**
     * RightRotate(y) also assumes that y is the right child of
     * an RBNode x
     */
    void RightRotate(RBNode* y);

    RBNode* createNode(Produs* p);

    bool isNil(RBNode* n);

    RBNode* search(RBNode* w, string key);

    /**
     * maximum(w) returns the node with maximum key in the
     * RB-tree with root node w
     */
    RBNode* maximum(RBNode* w);

    /**
     * minimum(w) returns the node with minimum key in the
     * RB-tree with root node w
     */
    RBNode* minimum(RBNode* w);

    /**
     * successor(w) returns the successor of node w in the
     * RB-tree to which node w belongs
     */
    RBNode* successor(RBNode* w);

    RBNode* predecessor(RBNode* w);

    /**
     * RBInsert(z) inserts node z in this RB-tree
     */
    void RBInsert(RBNode* z);

    RBNode* del(RBNode* z);

    void RBDeleteFixup(RBNode* x);

    void RBInsertFixup(RBNode* z);

    void inorder(RBNode* T);

    void inorder();

    void bfs();
};
