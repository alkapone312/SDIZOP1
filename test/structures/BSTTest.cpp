#include <iostream>
#include "ui/UserInterface.h"
#include "structures/IntegerBinarySearchTree.h"
#include "Tests.h"

using namespace SDIZO;
using namespace std;

void _testBSTPerformance();
void _testBSTInteractive();
void _printBSTree(IntegerBinarySearchTreeNode* root, int space = 0);
void _printNodePath(IntegerBinarySearchTreeNode* node);

UserInterface* bstUi;

void testBinarySearchTree() {
    bstUi = UserInterface::getInstance();
    string options[] = {
        "What would you like to do:",
        "1. Performance test",
        "2. Interactive test",
        "3. Generate test file",
        "4. Exit"
    };
    bool run = true;
    while(run) {
        bstUi->menu(options);
        switch(bstUi->getNumber()) {
            case 1:
                _testBSTPerformance();
            break;
            case 2:
                _testBSTInteractive();
            break;
            case 3:
                testFileGeneration("bst");
            break;
            case 4:
                run = false;
            break;
        }
    }
}

void _testBSTPerformance() {

}

void _testBSTInteractive() {
    string options[] = {
        "What would you like to do:",
        "1. Add to tree",
        "2. Find element in tree",
        "3. Remove element from tree",
        "4. Print tree",
        "5. Exit"
    };
    IntegerBinarySearchTree* tree = new IntegerBinarySearchTree;
    IntegerBinarySearchTreeNode* buff;
    string sbuff = "";
    bool run = true;
    while(run) {
        bstUi->menu(options);
        switch (bstUi->getNumber()) {
        case 1:
            tree->add(bstUi->getNumber());
            _printBSTree(tree->getRoot());
        break;
        case 2:
        try {
            _printBSTree(tree->getRoot());
            buff = tree->find(bstUi->getNumber());
            bstUi->info("Found node: " + to_string(buff->value));
            _printNodePath(buff);
        } catch(Exception* e) {
            bstUi->error(e->getMessage());
        }
        break;
        case 3:
        try {
            _printBSTree(tree->getRoot());
            buff = tree->find(bstUi->getNumber());
            buff = tree->remove(buff);
            bstUi->info("Deleted node: " + to_string(buff->value));
            _printNodePath(buff);
            _printBSTree(tree->getRoot());
        } catch(Exception* e) {
            bstUi->error(e->getMessage());
        }
        break;
        case 4:
            _printBSTree(tree->getRoot());
        break;
        case 5:
            run = false;
        break;
        }
    }
}

void _printBSTree(IntegerBinarySearchTreeNode* root, int space) {
    const int COUNT = 10;
    if (root == nullptr)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    _printBSTree(root->right, space);
 
    // Print current node after space
    // count
    string sbuff = "";
    for (int i = COUNT; i < space; i++)
        sbuff += " ";
    sbuff += to_string(root->value);
    bstUi->info("");
    bstUi->info(sbuff);
    bstUi->info("");
 
    // Process left child
    _printBSTree(root->left, space);
}

void _printNodePath(IntegerBinarySearchTreeNode* node) {
    string buff = "";
    buff = "";
    while(node != nullptr) {
        buff = to_string(node->value) + " " + buff;
        node = node->parent;
    }
    bstUi->info("Path to node:" + buff);
}
