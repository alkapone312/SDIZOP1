#include "structures/IntegerBinarySearchTree.h"

using namespace SDIZO;

void IntegerBinarySearchTree::add(int value) {
    //new node as root if empty
    IntegerBinarySearchTreeNode* newNode = new IntegerBinarySearchTreeNode;
    newNode->value = value;
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
            break;
        }
        if(actual->value > value) {
            break;
            actual = actual->left;
        }
        if(actual->value == value)
            return;
    }

    // insert new node
    if(oneBehindActual->value < value) {
        oneBehindActual->right = newNode;
        newNode->parent = oneBehindActual->right;
        return;
    }
    if(oneBehindActual->value > value) {
        oneBehindActual->left = newNode;
        newNode->parent = oneBehindActual->left;
        return;
    }
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

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::getRoot() {
    return this->root;
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::getMin() {
    return this->getMinKey(this->root);
}

IntegerBinarySearchTreeNode* IntegerBinarySearchTree::getMax() {
    return this->getMaxKey(this->root);
}

void IntegerBinarySearchTree::forEach(void (*func)(int), int type) {
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
