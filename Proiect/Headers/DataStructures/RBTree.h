#pragma once

class RBNode;
#include "RBNode.h"
#include <string>

using std::string;

/**
 * Implementation of a Red-Black Tree
 *
 * The RBTree contains a pointer to
 * the root node and the current
 * number of nodes.
 */
class RBTree{
public:
    RBNode* root;
    int nodes;

    /// Default constructor
    RBTree();

    /// Default destructor
    ~RBTree();

    /**
    * Rotates to the left the
    * given node
    * 
    * @param RBNode* the node on
    * which the rotation is being made
    */
    void LeftRotate(RBNode*);

    /**
    * Rotates to the right the
    * given node
    * 
    * @param RBNode* the node on
    * which the rotation is being made
    */
    void RightRotate(RBNode*);

    /**
    * Creates a new node with
    * the given key
    * 
    * @param Produs* the key
    * 
    * @return the new node
    */
    RBNode* createNode(Produs*);

    /**
    * @param RBNode* node to be checked
    * 
    * @return true if node is Nil
    * false otherwise `bool`
    */
    bool isNil(RBNode*);
    
    /**
    * Searches the node containing
    * the key string int the subtree
    * rooted at RBNode*.
    * 
    * @param RBNode* root of the subtree
    * that the search is performed on
    * @param string that is the key 
    * for the searched node
    * 
    * @return the searched RBNode* or NIL
    */
    RBNode* search(RBNode*, string);

    /**
     * @param the root of the tree
     *
     * @return the node with maximum key in
     * the tree with root node
     */
    RBNode* maximum(RBNode*);

    /**
     * @param the root of the tree
     * 
     * @return the node with minimum key in
     * the tree with root node
     */
    RBNode* minimum(RBNode*);

    /**
     * @param RBNode* the node to find the
     * successor for
     * 
     * @return the successor of the given node
     * in the tree to which node belongs
     */
    RBNode* successor(RBNode*);

    /**
     * @param RBNode* the node to find the
     * predecessor for
     *
     * @return the predecessor of the given node
     * in the tree to which node belongs
     */
    RBNode* predecessor(RBNode*);

    /**
     * Inserts node in this RBTree
     * 
     * @param RBNode* to be inserted
     */
    void RBInsert(RBNode*);

    /**
     * Delete a node in this RBTree
     *
     * @param RBNode* to be deleted
     * 
     * @return the deleted node `RBNode*`
     */
    RBNode* del(RBNode*);

    /**
     * Fixes the tree after a delete
     *
     * @param RBNode* from which to 
     * begin the fixup
     */
    void RBDeleteFixup(RBNode*);

    /**
     * Fixes the tree after an insert
     *
     * @param RBNode* from which to
     * begin the fixup
     */
    void RBInsertFixup(RBNode*);

    /**
     * Recursively traverses the
     * tree in inorder
     *
     * @param RBNode* node to
     * be processed
     * @param int index of the
     * current element
     */
    int inorder(RBNode*, int);

    /**
     * Calls the inorder traverse
     * for the root node.
     */
    void inorder();

    /**
     * Recursively traverses the
     * tree in reverse inorder
     *
     * @param RBNode* node to
     * be processed
     * @param int index of the
     * current element
     */
    int rinorder(RBNode*, int);

    /**
     * Calls the reverse inorder
     * traverse for the root node.
     */
    void rinorder();
};
