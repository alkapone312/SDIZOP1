#include "structures/IntegerBinarySearchTree.h"

using namespace SDIZO;

IntegerBinarySearchTree::~IntegerBinarySearchTree() {
    while(this->root) {
        this->remove(this->root);
    }
}

IntegerBinaryTreeNode* IntegerBinarySearchTree::add(int value) {
    //new node as root if empty
    IntegerBinaryTreeNode* newNode = new IntegerBinaryTreeNode;
    newNode->value = value;
    newNode->count = 1;

    return this->add(newNode);
}

IntegerBinaryTreeNode* IntegerBinarySearchTree::remove(IntegerBinaryTreeNode* node) {
    IntegerBinaryTreeNode* successor;
    IntegerBinaryTreeNode* successorsChild;

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

IntegerBinaryTreeNode* IntegerBinarySearchTree::find(int value) {
    IntegerBinaryTreeNode* actual = this->root;
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

IntegerBinaryTreeNode* IntegerBinarySearchTree::getRoot() {
    return this->root;
}

IntegerBinaryTreeNode* IntegerBinarySearchTree::getMin() {
    return this->getMinKey(this->root);
}

IntegerBinaryTreeNode* IntegerBinarySearchTree::getMax() {
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

void IntegerBinarySearchTree::rotateLeft(IntegerBinaryTreeNode* node) {
    if(!node->right) {
        return;
    }

    IntegerBinaryTreeNode* right = node->right;
    node->right = right->left;
    if(right->left != nullptr)
        right->left->parent = node;
    right->parent = node->parent;
    if(node->parent == nullptr)
        this->root = right;
    else if(node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    
    right->left = node;
    node->parent = right;
}

void IntegerBinarySearchTree::rotateRight(IntegerBinaryTreeNode* node) {
    if(!node->left) {
        return;
    }

    IntegerBinaryTreeNode* left = node->left;
    node->left = left->right;
    if(left->right != nullptr)
        left->right->parent = node;
    left->parent = node->parent;
    if(node->parent == nullptr)
        this->root = left;
    else if(node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    
    left->right = node;
    node->parent = left;
}

IntegerBinaryTreeNode* IntegerBinarySearchTree::add(IntegerBinaryTreeNode* node) {
    if(this->root == nullptr) {
            this->root = node;
            return node;
        }

    // search for new node position
    IntegerBinaryTreeNode* oneBehindActual;
    IntegerBinaryTreeNode* actual = this->root;
    while (actual != nullptr) {
        oneBehindActual = actual;
        if(actual->value < node->value) {
            actual = actual->right;
            continue;
        }
        if(actual->value > node->value) {
            actual = actual->left;
            continue;
        }
        if(actual->value == node->value)
            actual->count++;
            return actual;
    }

    // insert new node
    if(oneBehindActual->value < node->value) {
        oneBehindActual->right = node;
        node->parent = oneBehindActual;
    }
    if(oneBehindActual->value > node->value) {
        oneBehindActual->left = node;
        node->parent = oneBehindActual;
    }

    return node;
}


void IntegerBinarySearchTree::preOrder(const std::function<void(int)>& func, IntegerBinaryTreeNode* node) {
    if(node == nullptr)
        return;
    func(node->value);
    preOrder(func, node->left);
    preOrder(func, node->right);
}

void IntegerBinarySearchTree::inOrder(const std::function<void(int)>& func, IntegerBinaryTreeNode* node) {
    if(node == nullptr)
        return;
    inOrder(func, node->left);
    func(node->value);
    inOrder(func, node->right);
}

void IntegerBinarySearchTree::postOrder(const std::function<void(int)>& func, IntegerBinaryTreeNode* node) {
    if(node == nullptr)
        return;
    postOrder(func, node->left);
    postOrder(func, node->right);
    func(node->value);
}


IntegerBinaryTreeNode* IntegerBinarySearchTree::findSuccessor(IntegerBinaryTreeNode* node) {
    if(node->right) 
        return getMinKey(node->right);
    IntegerBinaryTreeNode* buff = node->parent;
    while(buff != nullptr && buff->left != node) {
        node = buff;
        buff = buff->parent;
    } 

    return buff;
}

IntegerBinaryTreeNode* IntegerBinarySearchTree::findPredecessor(IntegerBinaryTreeNode* node) {
    if(node->left) 
        return getMaxKey(node->left);
    IntegerBinaryTreeNode* buff = node->parent;
    while(buff != nullptr && buff->right != node) {
        node = buff;
        buff = buff->parent;
    } 

    return buff;
}

IntegerBinaryTreeNode* IntegerBinarySearchTree::getMinKey(IntegerBinaryTreeNode* node) {
    IntegerBinaryTreeNode* buff;
    while(node->left != nullptr) {
        buff = node;
        node = node->left;
    }

    return node;
}

IntegerBinaryTreeNode* IntegerBinarySearchTree::getMaxKey(IntegerBinaryTreeNode* node) {
    IntegerBinaryTreeNode* buff;
    while(node->right != nullptr) {
        buff = node;
        node = node->right;
    }

    return node;
}

void IntegerBinarySearchTree::transplant(IntegerBinaryTreeNode* node, IntegerBinaryTreeNode* child) {
    if(!node->parent) {
        this->root = child;
    } else if(node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    if(child) {
        child->parent = node->parent;
    }
}
