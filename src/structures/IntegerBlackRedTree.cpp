#include "structures/IntegerBlackRedTree.h"

using namespace SDIZO;

void IntegerBlackRedTree::remove(IntegerBlackRedTreeNode* node) {
    
}

void IntegerBlackRedTree::add(int value) {
    	// Ordinary Binary Search Insertion
		IntegerBlackRedTreeNode* newNode = new IntegerBlackRedTreeNode;
        newNode->value = value;
        newNode->count = 1;
        newNode = (IntegerBlackRedTreeNode*)IntegerBinarySearchTree::add(newNode);

		// if new node is a root node, simply return
		if (newNode->parent == nullptr){
			newNode->red = false;
			return;
		}

		// if the grandparent is null, simply return
		if (newNode->parent->parent == nullptr) {
			return;
		}

		// Fix the tree
		fixInsert(newNode);
}

// fix the red-black tree
void IntegerBlackRedTree::fixInsert(IntegerBlackRedTreeNode* insertedNode){
    while (insertedNode != root && ((IntegerBlackRedTreeNode*)insertedNode->parent)->red) {
        if (insertedNode->parent == insertedNode->parent->parent->left) {
            IntegerBlackRedTreeNode* uncle = (IntegerBlackRedTreeNode*)insertedNode->parent->parent->right;
            if (uncle != nullptr && uncle->red) {
                // Przypadek 1: wujek jest czerwony
                ((IntegerBlackRedTreeNode*)insertedNode->parent)->red = false;
                uncle->red = false;
                ((IntegerBlackRedTreeNode*)insertedNode->parent->parent)->red = true;
                insertedNode = (IntegerBlackRedTreeNode*)insertedNode->parent->parent;
            } else {
                if (insertedNode == insertedNode->parent->right) {
                    // Przypadek 2: nowy węzeł jest prawym dzieckiem
                    insertedNode = (IntegerBlackRedTreeNode*)insertedNode->parent;
                    this->rotateLeft(insertedNode);
                }
                // Przypadek 3: nowy węzeł jest lewym dzieckiem
                ((IntegerBlackRedTreeNode*)insertedNode->parent)->red = false;
                ((IntegerBlackRedTreeNode*)insertedNode->parent->parent)->red = true;
                this->rotateRight(insertedNode->parent->parent);
            }
        } else {
            IntegerBlackRedTreeNode* uncle = (IntegerBlackRedTreeNode*)insertedNode->parent->parent->left;
            if (uncle != nullptr && uncle->red) {
                // Przypadek 4: wujek jest czerwony
                ((IntegerBlackRedTreeNode*)insertedNode->parent)->red = false;
                uncle->red = false;
                ((IntegerBlackRedTreeNode*)insertedNode->parent->parent)->red = true;
                insertedNode = (IntegerBlackRedTreeNode*)insertedNode->parent->parent;
            } else {
                if (insertedNode == insertedNode->parent->left) {
                    // Przypadek 5: nowy węzeł jest lewym dzieckiem
                    insertedNode = (IntegerBlackRedTreeNode*)insertedNode->parent;
                    this->rotateRight(insertedNode);
                }
                // Przypadek 6: nowy węzeł jest prawym dzieckiem
                ((IntegerBlackRedTreeNode*)insertedNode->parent)->red = false;
                ((IntegerBlackRedTreeNode*)insertedNode->parent->parent)->red = true;
                this->rotateLeft(insertedNode->parent->parent);
            }
        }
    }
    ((IntegerBlackRedTreeNode*)root)->red = false;
}

void IntegerBlackRedTree::fixDelete(IntegerBlackRedTreeNode* node) {
    
}