#include "../../Headers/DataStructures/RBTree.h"
#include <iostream>
#include <queue>

using std::cout;
using std::queue;

RBTree::RBTree(){
    RBNode::Nil = new RBNode(nullptr);
    root = RBNode::Nil;
    nodes = 0;
}

RBTree::RBTree(Produs* p) {
    RBNode::Nil = new RBNode(nullptr);
    root = new RBNode(p);
    nodes = 1;
}

RBTree::~RBTree(){
    delete RBNode::Nil;
    delete root;
}

void RBTree::LeftRotate(RBNode* x)
{
    // Set y
    RBNode* y = x->right;
    // Turn y's left subtree into x's right subtree
    x->right = y->left;
    if (y->left != RBNode::Nil)
        y->left->p = x;
    // link x's parent to y
    y->p = x->p;
    if (x->p == RBNode::Nil)
        root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    // Put x on y's left
    y->left = x;
    x->p = y;
}

void RBTree::RightRotate(RBNode* y)
{
    // Set x
    RBNode* x = y->left;
    // Turn x's right subtree into y's left subtree
    y->left = x->right;
    if (x->right != RBNode::Nil)
        x->right->p = y;
    // link y's parent to x
    x->p = y->p;
    if (y->p == RBNode::Nil)
        root = x;
    else if (y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;
    // Put y on x's right
    x->right = y;
    y->p = x;
}

RBNode* RBTree::createNode(Produs* p)
{
    return new RBNode(p);
}

bool RBTree::isNil(RBNode* n)
{
    return (n == RBNode::Nil);
}

RBNode* RBTree::search(RBNode* w, string key)
{
    if (isNil(w) || w->key->getDenumire() == key)
        return w;
    return search((key < w->key->getDenumire()) ? w->left : w->right, key);
}

RBNode* RBTree::maximum(RBNode* w)
{
    RBNode* x = w;
    while (!isNil(x->right))
        x = x->right;
    return x;
}

RBNode* RBTree::minimum(RBNode* w)
{
    RBNode* x = w;
    while (!isNil(x->left))
        x = x->left;
    return x;
}

RBNode* RBTree::successor(RBNode* w)
{
    if (isNil(w)) return w;
    RBNode* x = w;
    if (!isNil(x->right))
        return minimum(x->right);
    RBNode* y = x->p;
    while (!isNil(y) && x == y->right)
    {
        x = y;
        y = x->p;
    }
    return y;
}

RBNode* RBTree::predecessor(RBNode* w)
{
    if (isNil(w)) return w;
    RBNode* x = w;
    if (!isNil(x->left))
        return maximum(x->left);
    RBNode* y = x->p;
    while (!isNil(y) && x == y->left)
    {
        x = y;
        y = x->p;
    }
    return y;
}

void RBTree::RBInsert(RBNode* z)
{
    nodes++;
    RBNode* y = RBNode::Nil;
    RBNode* x = root;
    while (!isNil(x))
    {
        y = x;
        x = (z->key->getDenumire() < x->key->getDenumire()) ? x->left : x->right;
    }
    z->p = y;
    if (isNil(y))
        root = z;
    else if (z->key->getDenumire() < y->key->getDenumire())
        y->left = z;
    else
        y->right = z;
    z->left = z->right = RBNode::Nil;
    z->col = RBNode::color::RED;
    RBInsertFixup(z);
}

RBNode* RBTree::del(RBNode* z)
{
    RBNode* y = (isNil(z->left) || isNil(z->right)) ? z : successor(z);
    RBNode* x = !isNil(y->left) ? y->left : y->right;
    x->p = y->p;
    if (isNil(y->p))
    {
        root = x;
    }
    else
    {
        if (y == y->p->left)
            y->p->left = x;
        else
            y->p->right = x;
    }
    if (y != z)
    {
        z->key = y->key;
        // copy y's satellite data into z
    }
    if (y->col == RBNode::color::BLACK)
        RBDeleteFixup(x);
    return y;
}

void RBTree::RBDeleteFixup(RBNode* x)
{
    RBNode* w;
    while ((x != root) && (x->col == RBNode::color::BLACK))
    {
        if (x == x->p->left)
        {
            w = x->p->right;
            if (w->col == RBNode::color::RED)
            {
                w->col = RBNode::color::BLACK;
                x->p->col = RBNode::color::RED;
                LeftRotate(x->p);
                w = x->p->right;
            }
            if ((w->left->col == RBNode::color::BLACK) && (w->right->col == RBNode::color::BLACK))
            {
                w->col = RBNode::color::RED;
                x = x->p;
            }
            else
            {
                if (w->right->col == RBNode::color::BLACK)
                {
                    w->left->col = RBNode::color::BLACK;
                    w->col = RBNode::color::RED;
                    RightRotate(w);
                    w = x->p->right;
                }
                w->col = x->p->col;
                x->p->col = RBNode::color::BLACK;
                w->right->col = RBNode::color::BLACK;
                LeftRotate(x->p);
                x = root;
            }
        }
        else
        {
            // same as 'then' clause with 'right' and 'left' exchanged
            w = x->p->left;
            if (w->col == RBNode::color::RED)
            {
                w->col = RBNode::color::BLACK;
                x->p->col = RBNode::color::RED;
                RightRotate(x->p);
                w = x->p->left;
            }
            if ((w->left->col == RBNode::color::BLACK) && (w->right->col == RBNode::color::BLACK))
            {
                w->col = RBNode::color::RED;
                x = x->p;
            }
            else
            {
                if (w->left->col == RBNode::color::BLACK)
                {
                    w->right->col = RBNode::color::BLACK;
                    w->col = RBNode::color::RED;
                    LeftRotate(w);
                    w = x->p->left;
                }
                w->col = x->p->col;
                x->p->col = RBNode::color::BLACK;
                w->left->col = RBNode::color::BLACK;
                RightRotate(x->p);
                x = root;
            }
        }
    }
    x->col = RBNode::color::BLACK;
}

void RBTree::RBInsertFixup(RBNode* z)
{
    while (z->p->col == RBNode::color::RED) {
        if (z->p == z->p->p->left)
        {
            RBNode* y = z->p->p->right;
            if (y->col == RBNode::color::RED)
            {
                z->p->col = RBNode::color::BLACK;
                y->col = RBNode::color::BLACK;
                z->p->p->col = RBNode::color::RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->right)
                {
                    z = z->p;
                    LeftRotate(z);
                }
                z->p->col = RBNode::color::BLACK;
                z->p->p->col = RBNode::color::RED;
                RightRotate(z->p->p);
            }
        }
        else
        {
            RBNode* y = z->p->p->left;
            if (y->col == RBNode::color::RED)
            {
                z->p->col = RBNode::color::BLACK;
                y->col = RBNode::color::BLACK;
                z->p->p->col = RBNode::color::RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;
                    RightRotate(z);
                }
                z->p->col = RBNode::color::BLACK;
                z->p->p->col = RBNode::color::RED;
                LeftRotate(z->p->p);
            }
        }
    }
    root->col = RBNode::color::BLACK;
}

int RBTree::inorder(RBNode* T, int i)
{
    if (!isNil(T))
    {
        int j = inorder(T->left, i);
        cout << j << ". " << *(T->key) << '\n';
        return inorder(T->right, j);
    }
    return i+1;
}

void RBTree::inorder()
{
    if (isNil(root))
    {
        cout << "empty";
    }
    else
        inorder(root, 0);
}

int RBTree::rinorder(RBNode* T, int i)
{
    if (!isNil(T))
    {
        int j = rinorder(T->right, i);
        cout << j << ". " << *(T->key) << '\n';
        return rinorder(T->left, j);
    }
    return i + 1;
}

void RBTree::rinorder()
{
    if (isNil(root))
    {
        cout << "empty";
    }
    else
        rinorder(root, 0);
}

/*void RBTree::bfs() {
    int i = 0;
    queue<RBNode*> q;
    q.push(root);
    while (q.empty() == false) {
        i++;
        RBNode* node = q.front();
        cout << i << ". " << * node->key << '\n';
        q.pop();
        if (node->left != RBNode::Nil)
            q.push(node->left);
        if (node->right != RBNode::Nil)
            q.push(node->right);
    }
}*/
