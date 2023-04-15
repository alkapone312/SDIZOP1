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
    if(node->count > 1) {
        node->count--;
        return;
    }

    IntegerBlackRedTreeNode* x;
    IntegerBlackRedTreeNode* y;

    y = node;
    int originalColor = color(y);
    if (left(node) == nullptr) {
        x = right(node);
        transplant(node, right(node));
    } else if (right(node) == nullptr) {
        x = left(node);
        transplant(node, left(node));
    } else {
        y = (IntegerBlackRedTreeNode*) getMinKey(right(node));
        originalColor = color(y);
        x = right(y);
        if (parent(y) == node && x) {
            x->parent = y;
        } else {
            transplant(y, right(y));
            y->right = right(node);
            if(y->right) {
                y->right->parent = y;
            }
        }

        transplant(node, y);
        y->left = left(node);
        y->left->parent = y;
        setColor(y, color(node));
    }
    delete node;
    if (originalColor == BLACK) {
        deleteFix(x);
    }
}

IntegerBlackRedTreeNode* IntegerBlackRedTree::getRoot() {
    return (IntegerBlackRedTreeNode*) this->root;
}

void IntegerBlackRedTree::deleteFix(IntegerBlackRedTreeNode* &node) {
    if (node == nullptr)
    return;

    if (node == root) {
        root = nullptr;
        return;
    }

    if (color(node) == RED || color(left(node)) == RED || color(right(node)) == RED) {
        IntegerBlackRedTreeNode* child = left(node) != nullptr ? left(node) : right(node);

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete node;
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete node;
        }
    } else {
        IntegerBlackRedTreeNode* sibling = nullptr;
        IntegerBlackRedTreeNode* p = nullptr;
        IntegerBlackRedTreeNode* ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && color(ptr) == DOUBLE_BLACK) {
            p = parent(ptr);
            if (ptr == p->left) {
                sibling = right(p);
                if (color(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(p, RED);
                    rotateLeft(p);
                } else {
                    if (color(left(sibling)) == BLACK && color(right(sibling)) == BLACK) {
                        setColor(sibling, RED);
                        if(color(p) == RED)
                            setColor(p, BLACK);
                        else
                            setColor(p, DOUBLE_BLACK);
                        ptr = p;
                    } else {
                        if (color(right(sibling)) == BLACK) {
                            setColor(left(sibling), BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = right(p);
                        }
                        setColor(sibling, p->color);
                        setColor(p, BLACK);
                        setColor(right(sibling), BLACK);
                        rotateLeft(p);
                        break;
                    }
                }
            } else {
                sibling = left(p);
                if (color(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(p, RED);
                    rotateRight(p);
                } else {
                    if (color(left(sibling)) == BLACK && color(right(sibling)) == BLACK) {
                        setColor(sibling, RED);
                        if (color(p) == RED)
                            setColor(p, BLACK);
                        else
                            setColor(p, DOUBLE_BLACK);
                        ptr = p;
                    } else {
                        if (color(left(sibling)) == BLACK) {
                            setColor(right(sibling), BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = left(p);
                        }
                        setColor(sibling, color(p));
                        setColor(p, BLACK);
                        setColor(left(sibling), BLACK);
                        rotateRight(p);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete node;
        setColor(getRoot(), BLACK);
    }
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
    if(!node)
        return nullptr;

    return (IntegerBlackRedTreeNode*) node->left;
}

IntegerBlackRedTreeNode* IntegerBlackRedTree::right(IntegerBlackRedTreeNode* node) {
    if(!node)
        return nullptr;
        
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