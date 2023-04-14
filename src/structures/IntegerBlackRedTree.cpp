#include "structures/IntegerBlackRedTree.h"

using namespace SDIZO;

IntegerBlackRedTree::~IntegerBlackRedTree() {
    while (this->root) {
        this->remove(this->getRoot());
    }
}

void IntegerBlackRedTree::add(int key) {
    IntegerBlackRedTreeNode* newNode = new IntegerBlackRedTreeNode;
    newNode->value = key;
    IntegerBinarySearchTree::add(newNode);
    this->insertFix(newNode);
}

void IntegerBlackRedTree::remove(IntegerBlackRedTreeNode* node) {
    
}

IntegerBlackRedTreeNode* IntegerBlackRedTree::getRoot() {
    return (IntegerBlackRedTreeNode*) this->root;
}

void IntegerBlackRedTree::deleteFix(IntegerBlackRedTreeNode* &node) {

}

void IntegerBlackRedTree::insertFix(IntegerBlackRedTreeNode* &newNode) {
    //no parent => newNode is root
    if(!hasParent(newNode)) {
        newNode->color = BLACK;
        return;
    }

    while(color(parent(newNode)) == RED) {
        if(parent(newNode) == left(grandparent(newNode))) {
            if(color(right(grandparent(newNode))) == RED) {
                setColor(right(grandparent(newNode)), BLACK);
                setColor(left(grandparent(newNode)), BLACK);
                setColor(grandparent(newNode), RED);
                newNode = grandparent(newNode);
            } else if(newNode == right(parent(newNode))) {
                newNode = parent(newNode);
                rotateLeft(newNode);
            } else {
                setColor(parent(newNode), BLACK);
                setColor(grandparent(newNode), RED);
                rotateRight(grandparent(newNode));
            }
        } else {
            if(color(left(grandparent(newNode))) == RED) {
                setColor(right(grandparent(newNode)), BLACK);
                setColor(left(grandparent(newNode)), BLACK);
                setColor(grandparent(newNode), RED);
                newNode = grandparent(newNode);
            } else if(newNode == left(parent(newNode))) {
                newNode = parent(newNode);
                rotateRight(newNode);
            } else {
                setColor(parent(newNode), BLACK);
                setColor(grandparent(newNode), RED);
                rotateLeft(grandparent(newNode));
            }
        }
        setColor(this->getRoot(), BLACK);
    }
}

int IntegerBlackRedTree::color(IntegerBlackRedTreeNode* node) {
    if(node == nullptr) {
        return BLACK;
    }

    return node->color;
}

void IntegerBlackRedTree::setColor(IntegerBlackRedTreeNode* node, int color) {
    if(node == nullptr) {
        return;
    }

    node->color = color;
}

IntegerBlackRedTreeNode* IntegerBlackRedTree::left(IntegerBlackRedTreeNode* node) {
    return (IntegerBlackRedTreeNode*) node->left;
}

IntegerBlackRedTreeNode* IntegerBlackRedTree::right(IntegerBlackRedTreeNode* node) {
    return (IntegerBlackRedTreeNode*) node->right;
}

IntegerBlackRedTreeNode* IntegerBlackRedTree::parent(IntegerBlackRedTreeNode* node) {
    return (IntegerBlackRedTreeNode*) node->parent;
}

IntegerBlackRedTreeNode* IntegerBlackRedTree::grandparent(IntegerBlackRedTreeNode* node) {
    if(this->hasGrandparent(node)) {
        return (IntegerBlackRedTreeNode*) node->parent->parent;
    }

    return nullptr;
}

IntegerBlackRedTreeNode* IntegerBlackRedTree::uncle(IntegerBlackRedTreeNode* node) {
    if(this->hasUncle(node)) {
        IntegerBinaryTreeNode* grandparent = node->parent->parent;
        return (IntegerBlackRedTreeNode*) (
            grandparent->left == node->parent ? 
            grandparent->right : 
            grandparent->left
        );
    }

    return nullptr;
}

bool IntegerBlackRedTree::hasParent(IntegerBinaryTreeNode* node) {
    return !!node->parent;
}

bool IntegerBlackRedTree::hasGrandparent(IntegerBinaryTreeNode* node) {
    if(hasParent(node)) {
        return !!node->parent->parent;
    }

    return false;
}

bool IntegerBlackRedTree::hasUncle(IntegerBinaryTreeNode* node) {
    if(hasGrandparent(node)) {
        IntegerBinaryTreeNode* grandparent = node->parent->parent;
        return (
            grandparent->left == node->parent ? 
            !!grandparent->right : 
            !!grandparent->left
        );
    }

    return false;
}