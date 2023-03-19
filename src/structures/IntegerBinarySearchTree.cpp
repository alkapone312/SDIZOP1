#include "structures/IntegerBinarySearchTree.h"

using namespace SDIZO;

void IntegerBinarySearchTree::add(int value) {
    //new node as root if empty
    IntegerBinarySearchTreeNode* newNode = new IntegerBinarySearchTreeNode;
    newNode->value = value;
    if(this->root == nullptr) {
        this->root = newNode;
    }

    // search for new node position
    IntegerBinarySearchTreeNode* oneBehindActual = this->root;
    IntegerBinarySearchTreeNode* actual = this->root;
    while (actual != nullptr) {
        oneBehindActual = actual;
        if(actual->value < value)
            actual = actual->right;
        if(actual->value > value)
            actual = actual->left;
        if(actual->value == value)
            return;
    }

    // insert new node
    if(oneBehindActual->value < value)
        oneBehindActual->right = newNode;
        newNode->parent = oneBehindActual->right;
    if(oneBehindActual->value > value)
        oneBehindActual->left = newNode;
        newNode->parent = oneBehindActual->left;
    if(oneBehindActual->value == value)
        return;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::remove(IntegerBinarySearchTreeNode* node) {
    IntegerBinarySearchTreeNode* successor;
    IntegerBinarySearchTreeNode* successorsChild;
    if(node->left == nullptr || node->right == nullptr) {
        successor = node;
    } else {
        successor = findSuccessor(node);
    }

    if(successor->left != nullptr) 
        successorsChild = successor->left;
    else 
        successorsChild = successor->right;
    if(successorsChild != nullptr)
        successor->parent = successorsChild->parent;
    if(successorsChild->parent == nullptr)
        this->root = successor;
    else {
        if(successorsChild == successorsChild->parent->left)
            successorsChild->parent->left = successor;
        else
            successorsChild->parent->right = successor;
    }
    if(successorsChild != node)
        node->value = successorsChild->value;

    return successorsChild;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::find(int value) {
    IntegerBinarySearchTreeNode* actual = this->root;
    while(actual != nullptr && actual->value != value) {
        if(actual->value < value)
            actual = actual->right;
        if(actual->value > value)
            actual = actual->left;
        if(actual->value == value)
            break;
    }


    return actual;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::getMin() {
    IntegerBinarySearchTreeNode* actual = this->root;
    while(actual->left) {
        actual = actual->left;
    }

    return actual;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::getMax() {
    IntegerBinarySearchTreeNode* actual = this->root;
    while(actual->right) {
        actual = actual->right;
    }

    return actual;
}

void IntegerBinarySearchTree::forEach(
    void (*func)(int), 
    int type = IntegerBinarySearchTree::PREORDER
) {
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

void IntegerBinarySearchTree::preOrder(void (*func)(int), IntegerBinarySearchTreeNode* node) {
    if(node == nullptr)
        return;
    func(node->value);
    preOrder(func, node->left);
    preOrder(func, node->right);
}

void IntegerBinarySearchTree::inOrder(void (*func)(int), IntegerBinarySearchTreeNode* node) {
    if(node == nullptr)
        return;
    inOrder(func, node->left);
    func(node->value);
    inOrder(func, node->right);
}

void IntegerBinarySearchTree::postOrder(void (*func)(int), IntegerBinarySearchTreeNode* node) {
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
