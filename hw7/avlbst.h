#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { }; 

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here

    //helper function to create a node  
    Node<Key, Value>* makenode(const std::pair<Key, Value>& keyValuePair) const{
        Node<Key, Value>* node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second,NULL);
        return node;
    }
    //helper function to insert in BST
    Node <Key, Value>* insertHelp(const std::pair<Key, Value>& keyValuePair, Node<Key, Value>* root){
        if(root==NULL){
            return makenode(keyValuePair);
        }
        //if key is not found in tree, insert
        if(this->find(keyValuePair.first)==this->end()){
            if(keyValuePair.first > root->getKey()){
                Node<Key, Value>* righty;
                righty = insertHelp(keyValuePair, root->getRight());
                root->setRight(righty);
                righty->setParent(root);
            }
            else if(keyValuePair.first < root->getKey()){
                Node<Key, Value>* lefty;
                lefty = insertHelp(keyValuePair, root->getLeft());
                root->setLeft(lefty);
                lefty->setParent(root);
            }
        }
        //if found set value to found key
        else {
            Node<Key, Value>* temp = this->internalFind(keyValuePair.first);
            temp->setValue(keyValuePair.second);
        }
        return root;
    }
    
    Node<Key, Value>* predecessor(Node<Key, Value>* current){
        Node<Key, Value>* pred = current->getLeft();
        while(pred->getRight() != NULL){
             pred = pred->getRight();
         }
         return pred;
    }

    Node<Key, Value>* internalFind(const Key& key) const{
        return internalFindHelper(key, this->root_);
    }
    //helper functions for internalfind
    Node<Key, Value>* internalFindHelper(const Key& key, Node<Key, Value>* root) const{
        if(root==NULL){
            return root;
        } 
        if(root->getKey()==key){
            return root;
        }
        if(root->getKey()>key){
            return internalFindHelper(key,root->getLeft());
        }
        else{
            return internalFindHelper(key, root->getRight());
        }

    }

};

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    this->root_ = insertHelp(new_item, this->root_);
    //this->insert(new_item);

}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    //this->remove(key);
     if(this->root_==NULL){
        return;
    }
    if(this->find(key)!=this->end()){
        Node<Key, Value>* takeNode = this->internalFind(key);
        //leaf node then just delete
        if (takeNode->getLeft() == NULL && takeNode->getRight() == NULL) {
            if (this->root_ == takeNode){
                this->root_=NULL;
                delete takeNode;
                return;
            }
            if (takeNode->getParent() != NULL) {
                if (takeNode==takeNode->getParent()->getLeft()){
                    takeNode->getParent()->setLeft(NULL);
                }
                else if (takeNode==takeNode->getParent()->getRight()){
                    takeNode->getParent()->setRight(NULL);
                }
                delete takeNode;
            }
        }
        //one right child, then change poiners,then remove
        else if(takeNode->getRight() != NULL && takeNode->getLeft() == NULL){
            //node doesnt have parent node so change ptrs
            if (takeNode->getParent()==NULL) {
                this->root_ = takeNode->getRight();
                takeNode->getRight()->setParent(NULL);  
            }
            else {
                //right node becomes the new node,change ptrs
                if (takeNode->getParent()->getRight() == takeNode){
                    takeNode->getParent()->setRight(takeNode->getRight());
                }
                else{
                    takeNode->getParent()->setLeft(takeNode->getRight());
                }
                takeNode->getRight()->setParent(takeNode->getParent());  
            }
            delete takeNode;
        }
        //one left child, then change poiners,then remove
        else if(takeNode->getRight() == NULL && takeNode->getLeft() != NULL){
              //node doesnt have parent node so change ptrs
            if (takeNode->getParent()==NULL) {
                this->root_ = takeNode->getLeft();
                takeNode->getLeft()->setParent(NULL);  
            }
            else {
                //right node becomes the new node,change ptrs
                if (takeNode->getParent()->getRight() == takeNode){
                    takeNode->getParent()->setRight(takeNode->getLeft());
                }
                else{
                    takeNode->getParent()->setLeft(takeNode->getLeft());
                }
                takeNode->getLeft()->setParent(takeNode->getParent());  
            }
            delete takeNode;

        }
        //node has 2 children
        else{
            Node<Key, Value>* pred = predecessor(takeNode);
            //if node has parent then update ptrs to pred and nodes children
            if (takeNode->getParent()) {
                if (takeNode==takeNode->getParent()->getLeft()){
                    takeNode->getParent()->setLeft(pred);
                } 
                else{
                    takeNode->getParent()->setRight(pred);
                } 
                pred->setParent(takeNode->getParent());
            }
            else { //Remove node is the root node, so swapNode is new root
                this->root_ = pred;
                if (pred->getParent() != takeNode) { //Pass on children to parent node if parent node isn't remove node
                    pred->getParent()->setRight(NULL);
                }
                pred->setParent(NULL);
            }
            //if pred has left child, pred parent is parent to pred's child
            if (pred->getLeft()){
                if(pred->getParent() != takeNode){
                    pred->getParent()->setRight(pred->getLeft());
                    pred->getLeft()->setParent(pred->getParent());
                }
            }
            if (takeNode->getRight() != NULL) {
                takeNode->getRight()->setParent(pred);
                pred->setRight(takeNode->getRight());
            }
            //if left of node is not the pred
            if (takeNode->getLeft() != pred) { 
                takeNode->getLeft()->setParent(pred);
                pred->setLeft(takeNode->getLeft());
            }
            delete takeNode;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
