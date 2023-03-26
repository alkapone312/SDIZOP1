#include "structures/IntegerBinarySearchTree.h"
#include <iostream>

using namespace SDIZO;

void IntegerBinarySearchTree::add(int value) {
    //new node as root if empty
    IntegerBinarySearchTreeNode* newNode = new IntegerBinarySearchTreeNode;
    newNode->value = value;
    newNode->count = 1;
    if(this->root == nullptr) {
        this->root = newNode;
        return;
    }

    // search for new node position
    IntegerBinarySearchTreeNode* oneBehindActual;
    IntegerBinarySearchTreeNode* actual = this->root;
    while (actual != nullptr) {
        oneBehindActual = actual;
        if(actual->value < value) {
            actual = actual->right;
            continue;
        }
        if(actual->value > value) {
            actual = actual->left;
            continue;
        }
        if(actual->value == value)
            actual->count++;
            return;
    }

    // insert new node
    if(oneBehindActual->value < value) {
        oneBehindActual->right = newNode;
        newNode->parent = oneBehindActual;
        return;
    }
    if(oneBehindActual->value > value) {
        oneBehindActual->left = newNode;
        newNode->parent = oneBehindActual;
        return;
    }
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::remove(IntegerBinarySearchTreeNode* node) {
    IntegerBinarySearchTreeNode* successor;
    IntegerBinarySearchTreeNode* successorsChild;

    if(node->count > 1) {
        node->count--;

        return node;
    }

    // if tree is empty
    if(this->root == nullptr) {
        throw new Exception((char*)"Tried to remove out of empty tree!");
    }

    // find successor, itself if dont have children
    if(node->left == nullptr || node->right == nullptr) {
        successor = node;
    } else {
        successor = findSuccessor(node);
    }

    // get succesor child if any
    successorsChild = successor->right;
    if(successor->left != nullptr) 
        successorsChild = successor->left;

    //make parent of the child parent of the successor
    if(successorsChild != nullptr)
        successorsChild->parent = successor->parent;

    // swap with root if successor is root    
    if(successor->parent == nullptr) {
        delete this->root;
        this->root = successorsChild;
    }
    else {
        // swap and delete nodes
        if(successor == successor->parent->left) {
            delete successor->parent->left;
            successor->parent->left = successorsChild;
        }
        else {
            delete successor->parent->right;
            successor->parent->right = successorsChild;
        }
    }

    //copy old node value
    if(successor != node) {
        node->value = successor->value;
        node->count = successor->count;
    }

    return successor;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::find(int value) {
    IntegerBinarySearchTreeNode* actual = this->root;
    while(actual != nullptr && actual->value != value) {
        if(actual->value < value) {
            actual = actual->right;
            continue;
        }
        if(actual->value > value) {
            actual = actual->left;
            continue;
        }
        if(actual->value == value)
            break;
    }

    if(actual == nullptr) {
        throw new Exception((char*)"Value not found!");
    }

    return actual;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::getRoot() {
    return this->root;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::getMin() {
    return this->getMinKey(this->root);
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::getMax() {
    return this->getMaxKey(this->root);
}

void IntegerBinarySearchTree::forEach(const std::function<void(int)>& func, int type) {
    switch (type) {
    case IntegerBinarySearchTree::PREORDER:
        preOrder(func, this->root);
        break;
    case IntegerBinarySearchTree::INORDER:
        inOrder(func, this->root);
        break;
    case IntegerBinarySearchTree::POSTORDER:
        postOrder(func, this->root);
        break;
    }
}

void IntegerBinarySearchTree::preOrder(const std::function<void(int)>& func, IntegerBinarySearchTreeNode* node) {
    if(node == nullptr)
        return;
    func(node->value);
    preOrder(func, node->left);
    preOrder(func, node->right);
}

void IntegerBinarySearchTree::inOrder(const std::function<void(int)>& func, IntegerBinarySearchTreeNode* node) {
    if(node == nullptr)
        return;
    inOrder(func, node->left);
    func(node->value);
    inOrder(func, node->right);
}

void IntegerBinarySearchTree::postOrder(const std::function<void(int)>& func, IntegerBinarySearchTreeNode* node) {
    if(node == nullptr)
        return;
    postOrder(func, node->left);
    postOrder(func, node->right);
    func(node->value);
}


IntegerBinarySearchTreeNode* IntegerBinarySearchTree::findSuccessor(IntegerBinarySearchTreeNode* node) {
    if(node->right) 
        return getMinKey(node->right);
    IntegerBinarySearchTreeNode* buff = node->parent;
    while(buff != nullptr && buff->left != node) {
        node = buff;
        buff = buff->parent;
    } 

    return buff;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::findPredecessor(IntegerBinarySearchTreeNode* node) {
    if(node->left) 
        return getMaxKey(node->left);
    IntegerBinarySearchTreeNode* buff = node->parent;
    while(buff != nullptr && buff->right != node) {
        node = buff;
        buff = buff->parent;
    } 

    return buff;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::getMinKey(IntegerBinarySearchTreeNode* node) {
    IntegerBinarySearchTreeNode* buff;
    while(node->left != nullptr) {
        buff = node;
        node = node->left;
    }

    return node;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::getMaxKey(IntegerBinarySearchTreeNode* node) {
    IntegerBinarySearchTreeNode* buff;
    while(node->right != nullptr) {
        buff = node;
        node = node->right;
    }

    return node;
}
