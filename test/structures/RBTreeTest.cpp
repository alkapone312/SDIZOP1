#include <iostream>
#include "ui/UserInterface.h"
#include "structures/IntegerBlackRedTree.h"
#include "utils/FileReader.h"
#include "utils/Timer.h"
#include "Tests.h"

using namespace SDIZO;
using namespace std;

void _testRBTPerformance();
void _testRBTInteractive();
void _testAddingToRBT();
void _testDeletingFromRBT();
void _testFindingInRBT();
void _printRBTree(IntegerBinaryTreeNode* root, int space = 0);
void _printRBTNodePath(IntegerBinaryTreeNode* node);
int _readRBTData(string fileName, IntegerBlackRedTree* RBT);

UserInterface* rbtUi;

void testBlackRedTree() {
    rbtUi = UserInterface::getInstance();
    string options[] = {
        "What would you like to do:",
        "1. Performance test",
        "2. Interactive test",
        "3. Generate test file",
        "4. Exit"
    };
    bool run = true;
    while(run) {
        rbtUi->menu(options);
        switch(rbtUi->getNumber()) {
            case 1:
                _testRBTPerformance();
            break;
            case 2:
                _testRBTInteractive();
            break;
            case 3:
                testFileGeneration("rbt");
            break;
            case 4:
                run = false;
            break;
        }
    }
}

void _testRBTPerformance() {
    string options[] = {
        "What would you like to do:",
        "1. Add to tree",
        "2. Find element in tree",
        "3. Remove element from tree",
        "4. Exit"
    };
    bool run = true;
    while(run) {
            rbtUi->menu(options);
            switch (rbtUi->getNumber()) {
            case 1:
                _testAddingToRBT();
            break;
            case 2:
                _testFindingInRBT();
            break;
            case 3:
                _testDeletingFromRBT();
            break;
            case 4:
                run = false;
            break;
        }
    }
}

void _testAddingToRBT() {
    int fileNumber = getNewFileIndex("rbt");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerBlackRedTree* RBT = new IntegerBlackRedTree();
        t->start();
        _readRBTData(testFileName("rbt", i), RBT);
        t->stop();
        rbtUi->info("Elapsed time: " + to_string(t->getResult()));
        delete RBT;
    }
    delete t;
}

void _testDeletingFromRBT() {
    int fileNumber = getNewFileIndex("rbt");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerBlackRedTree* RBT = new IntegerBlackRedTree();
        int fileLength = _readRBTData(testFileName("rbt", i), RBT);
        t->start();
            for(int i = 0 ; i < fileLength; i++) {
                RBT->remove((IntegerBlackRedTreeNode*)RBT->getRoot());
            }
        t->stop();
        rbtUi->info("Elapsed time: " + to_string(t->getResult()));
        delete RBT;
    }
    delete t;
}

void _testFindingInRBT() {
    int fileNumber = getNewFileIndex("rbt");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerBlackRedTree* RBT = new IntegerBlackRedTree();
        _readRBTData(testFileName("rbt", i), RBT);
        int max = RBT->getMax()->value;
        t->start();
            RBT->find(max);
        t->stop();
        rbtUi->info("Elapsed time: " + to_string(t->getResult()));
        delete RBT;
    }
    delete t;
}

void _testRBTInteractive() {
    string options[] = {
        "What would you like to do:",
        "1. Add to tree",
        "2. Find element in tree",
        "3. Remove element from tree",
        "4. Print tree",
        "5. Exit"
    };
    IntegerBlackRedTree* tree = new IntegerBlackRedTree;
    IntegerBinaryTreeNode* buff;
    string sbuff = "";
    bool run = true;
    while(run) {
        rbtUi->menu(options);
        switch (rbtUi->getNumber()) {
        case 1:
            tree->add(rbtUi->getNumber());
            _printRBTree(tree->getRoot());
        break;
        case 2:
        try {
            _printRBTree(tree->getRoot());
            buff = tree->find(rbtUi->getNumber());
            rbtUi->info("Found node: " + to_string(buff->value));
            _printRBTNodePath(buff);
        } catch(Exception* e) {
            rbtUi->error(e->getMessage());
        }
        break;
        case 3:
        try {
            _printRBTree(tree->getRoot());
            buff = (IntegerBlackRedTreeNode*)tree->find(rbtUi->getNumber());
            tree->remove((IntegerBlackRedTreeNode*)buff);
            _printRBTree(tree->getRoot());
        } catch(Exception* e) {
            rbtUi->error(e->getMessage());
        }
        break;
        case 4:
            _printRBTree(tree->getRoot());
        break;
        case 5:
            run = false;
        break;
        }
    }
}

void _printRBTree(IntegerBinaryTreeNode* root, int space) {
    const int COUNT = 10;
    if (root == nullptr)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    _printRBTree(root->right, space);
 
    // Print current node after space
    // count
    string sbuff = "";
    for (int i = COUNT; i < space; i++)
        sbuff += " ";
    sbuff += to_string(root->value);
    rbtUi->info("");
    rbtUi->info(sbuff);
    rbtUi->info("");
 
    // Process left child
    _printRBTree(root->left, space);
}

void _printRBTNodePath(IntegerBinaryTreeNode* node) {
    string buff = "";
    buff = "";
    while(node != nullptr) {
        buff = to_string(node->value) + " " + buff;
        node = node->parent;
    }
    rbtUi->info("Path to node:" + buff);
}

int _readRBTData(string fileName, IntegerBlackRedTree* RBT) {   
    int fileLength; 
    try {
        FileReader* reader = new FileReader(fileName);
        fileLength = reader->getData();
        rbtUi->info("File contains " + to_string(fileLength) + " numbers");
        while (reader->isData()) {
            RBT->add(reader->getData());
        }
    } catch (...) {
        rbtUi->error("Test file " + fileName + " is corrupted!");
    }

    return fileLength;
}