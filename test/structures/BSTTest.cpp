#include <iostream>
#include "ui/UserInterface.h"
#include "structures/IntegerBinarySearchTree.h"
#include "Tests.h"

using namespace SDIZO;
using namespace std;

void _testBSTPerformance();
void _testBSTInteractive();
void _printBSTree(IntegerBinarySearchTree* tree);

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
    bool run = true;
    while(run) {
        bstUi->menu(options);
        switch (bstUi->getNumber()) {
        case 1:
            tree->add(bstUi->getNumber());
            _printBSTree(tree);
        break;
        case 2:
            tree->find(bstUi->getNumber());
        break;
        case 3:
            buff = tree->find(bstUi->getNumber());
            tree->remove(buff);
        break;
        case 4:
            _printBSTree(tree);
        break;
        case 5:
            run = false;
        break;
        }
    }
}

void _printBSTree(IntegerBinarySearchTree* tree) {
    tree->forEach(
        [](int value) {
            cout << value << " ";
        },
        IntegerBinarySearchTree::INORDER
    );
}