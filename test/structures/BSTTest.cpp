#include <iostream>
#include "ui/UserInterface.h"
#include "structures/IntegerBinarySearchTree.h"
#include "utils/FileReader.h"
#include "utils/Timer.h"
#include "Tests.h"

using namespace SDIZO;
using namespace std;

void _testBSTPerformance();
void _testBSTInteractive();
void _testAddingToBST();
void _testDeletingFromBST();
void _testFindingInBST();
void _printBSTree(IntegerBinarySearchTreeNode* root, int space = 0);
void _printNodePath(IntegerBinarySearchTreeNode* node);
int _readBSTData(string fileName, IntegerBinarySearchTree* bst);

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
    string options[] = {
        "What would you like to do:",
        "1. Add to tree",
        "2. Find element in tree",
        "3. Remove element from tree",
        "4. Exit"
    };
    bool run = true;
    while(run) {
            bstUi->menu(options);
            switch (bstUi->getNumber()) {
            case 1:
                _testAddingToBST();
            break;
            case 2:
                _testFindingInBST();
            break;
            case 3:
                _testDeletingFromBST();
            break;
            case 4:
                run = false;
            break;
        }
    }
}

void _testAddingToBST() {
    int fileNumber = getNewFileIndex("bst");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerBinarySearchTree* bst = new IntegerBinarySearchTree();
        t->start();
        _readBSTData(testFileName("bst", i), bst);
        t->stop();
        bstUi->info("Elapsed time: " + to_string(t->getResult()));
        delete bst;
    }
    delete t;
}

void _testDeletingFromBST() {
    int fileNumber = getNewFileIndex("bst");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerBinarySearchTree* bst = new IntegerBinarySearchTree();
        int fileLength = _readBSTData(testFileName("bst", i), bst);
        t->start();
            for(int i = 0 ; i < fileLength; i++) {
                bst->remove(bst->getRoot());
            }
        t->stop();
        bstUi->info("Elapsed time: " + to_string(t->getResult()));
        delete bst;
    }
    delete t;
}

void _testFindingInBST() {
    int fileNumber = getNewFileIndex("bst");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerBinarySearchTree* bst = new IntegerBinarySearchTree();
        _readBSTData(testFileName("bst", i), bst);
        int max = bst->getMax()->value;
        t->start();
            bst->find(max);
        t->stop();
        bstUi->info("Elapsed time: " + to_string(t->getResult()));
        delete bst;
    }
    delete t;
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

int _readBSTData(string fileName, IntegerBinarySearchTree* bst) {   
    int fileLength; 
    try {
        FileReader* reader = new FileReader(fileName);
        fileLength = reader->getData();
        bstUi->info("File contains " + to_string(fileLength) + " numbers");
        while (reader->isData()) {
            bst->add(reader->getData());
        }
    } catch (...) {
        bstUi->error("Test file " + fileName + " is corrupted!");
    }

    return fileLength;
}