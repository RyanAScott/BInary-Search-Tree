#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

template <class T>
BST<T>::BST ()
{
    root = NULL;
}    // constructor

template <class T>
BST<T>::~BST ()
{
    reclaimAllNodes(root);
}// destructor

template <class T>
void BST<T>::transferFrom (BST& source)
{
    reclaimAllNodes(root);
    root = source.root;
    source.root = NULL;
} // transferFrom

template <class T>
BST<T>& BST<T>::operator=(BST& rhs)
{
    reclaimAllNodes(root);
    root=rhs.root;
    return *this;
}    // operator =

template <class T>
void BST<T>::clear (void)
{
    reclaimAllNodes(root);
    root = NULL;
} // clear

template <class T>
void BST<T>::reclaimAllNodes (TreeNodeRecord<T>*& root)
// requires: Null(root)  or  Alive(root)
//  ensures: all nodes in BST
//           beginning with root are reclaimed
{
    if (root != NULL) {
        reclaimAllNodes(root->left);
        reclaimAllNodes(root->right);
        root->parent = NULL;
        delete (root);
    } // end if
} // reclaimAllNodes

//----------------------------------------


template <class T>
void BST<T>:: inorderTraversal(){
    inorderTraversal(root);
}// inorderTraversal

template <class T>
void BST<T>:: inorderTraversal(TreeNodeRecord<T>*& root){
    if(root!=NULL) {
        inorderTraversal(root->left);
        cout<<root->value<<", ";
        inorderTraversal(root->right);
    }// if
}// inorderTraversal


template <class T>
void BST<T>:: insertElement (T& x){
     root = insertElement(x, root);
}// insertElement

template <class T>
TreeNodeRecord<T>* BST<T>:: insertElement(T& x,TreeNodeRecord<T>*& root){
    TreeNodeRecord<T>* n = new TreeNodeRecord<T>;
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;

    if (root==NULL){
        n->value = x;
        return n;
    }// if
    else if (x < root->value){
        root->left = insertElement(x, root->left);
        root->left->parent = root;
    }// else if
    else{
        root->right = insertElement(x, root->right);
        root->right->parent = root;
    }// else
    return root;
}// insertElement

template <class T>
bool BST<T>::searchElement(T& x) {
    return searchElement(x, root);
}// searchElement

template <class T>
bool BST<T>::searchElement (T& x, TreeNodeRecord<T>*& root) {

    if (root == NULL)
        return false;
        if (root->value == x)
            return true;
    else if (x < root->value)
        return searchElement(x, root->left);
    else if (x > root->value)
        return searchElement(x, root->right);

}// searchElement

template<class T>
void BST<T>::deleteElement(T& x) {
    deleteElement(x, root);
}// deleteElement

template <class T>
void BST<T>::deleteElement(T& x, TreeNodeRecord<T>*& root) {
    if (root == NULL)
        return;
    if (root->value == x) {
        if (root->left == NULL && root->right == NULL)
            root = NULL;
        else if (root->left == NULL && root->right != NULL) {
            root->right->parent = root->parent;
            root = root->right;
        }// else if
        else if (root->left != NULL && root->right == NULL) {
            root->left->parent = root->parent;
            root = root->left;
        }// else if
        else {
            TreeNodeRecord<T>* predecessor = inorderPredecessor(root);
            root->value = predecessor->value;
            if (root->parent == NULL) {
                predecessor->parent->right = predecessor->left;
                predecessor = NULL;
            }// if
            else {
                if(predecessor->parent == root) {
                    predecessor->parent->left = predecessor->left;
                    predecessor = NULL;
                }// if
                else {
                    predecessor->parent->right = predecessor->left;
                    predecessor = NULL;
                }// else
            }// else
        }// else
    }// if
    else if (root->value < x)
        deleteElement(x, root->right);
    else if (root->value > x)
        deleteElement(x, root->left);
}// deleteElement

template<class T>
void BST<T>::preorderTraversal() {
    preorderTraversal(root);
}// preorderTraversal

template<class T>
void BST<T>::preorderTraversal(TreeNodeRecord<T>*& root) {
    if(root!=NULL) {
        cout<<root->value<<", ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }// if
}// preorderTraversal

template<class T>
void BST<T>::postorderTraversal() {
    postorderTraversal(root);
}// postorderTraversal

template<class T>
void BST<T>::postorderTraversal(TreeNodeRecord<T>*& root) {
    if(root!=NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout<<root->value<<", ";
    }// if
}// postorderTraversal

template<class T>
int BST<T>::maxTreeHeight() {
    return maxTreeHeight(root)-1;// -1 corrects the counting problem
}// maxTreeHeight

template<class T>
int BST<T>::maxTreeHeight(TreeNodeRecord<T>*& root) {
    if(root == NULL)
        return 0;
    else {
        int l = maxTreeHeight(root->left);
        int r = maxTreeHeight(root->right);
        if(l > r)
            return (l + 1);
        else
            return (r + 1);
    }// else
}// maxTreeHeight

template<class T>
int BST<T>::numberOfLeaves() {
    return numberOfLeaves(root);
}// numberOfLeaves

template<class T>
int BST<T>::numberOfLeaves(TreeNodeRecord<T>*& root) {
    if(root == NULL)
        return 0;
    else if(root->left == NULL && root->right == NULL)
        return 1;
    else
        return numberOfLeaves(root->left) + numberOfLeaves(root->right);
}// numberOfLeaves

template<class T>
T& BST<T>::inorderPredecessor(T& x) {
    TreeNodeRecord<T>* hold = inorderPredecessor(root);
    return hold->value;
}// public inorderPredecessor

template<class T>
TreeNodeRecord<T>* BST<T>::inorderPredecessor(TreeNodeRecord<T>*& root) {
    // variables
    int lowestNode;
    int paramNode = root->value;
    int i;
    TreeNodeRecord<T>* hold = this->root; // traverses tree without messing it up


    while (hold->left != NULL)  
        hold = hold->left;
    
    lowestNode = hold->value;

    if (paramNode == lowestNode)
        return hold;

    for (i = paramNode - 1; i >= lowestNode; i--) { 
        hold = this->root;
        while (hold != NULL) {
            if (hold->value == i)
                return hold;
            else if (hold->value < i)
                hold = hold->right;
            else if (hold->value > i)
                hold = hold->left;
        }// while 

    }// for
}// inOrderPredecessor

