#include <iostream>
#include "ui/UserInterface.h"
#include "structures/IntegerBlackRedTree.h"
#include "utils/FileReader.h"
#include "utils/FileWriter.h"
#include "utils/Timer.h"
#include "Tests.h"

using namespace SDIZO;
using namespace std;

void _testRBTPerformance();
void _testRBTPerformanceAutomatic();
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
        "3. Automatic performance test",
        "4. Generate test file",
        "5. Exit"
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
                _testRBTPerformanceAutomatic();
            break;
            case 4:
                testFileGeneration("rbt");
            break;
            case 5:
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
        IntegerBlackRedTree* rbt = new IntegerBlackRedTree();
        _readRBTData(testFileName("rbt", i), rbt);
        t->start();
        rbt->add(-1);
        t->stop();
        rbtUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete rbt;
    }
    delete t;
}

void _testDeletingFromRBT() {
    int fileNumber = getNewFileIndex("rbt");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerBlackRedTree* rbt = new IntegerBlackRedTree();
        int fileLength = _readRBTData(testFileName("rbt", i), rbt);
        t->start();
        rbt->remove((IntegerBlackRedTreeNode*)rbt->getRoot());
        t->stop();
        rbtUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete rbt;
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
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete RBT;
    }
    delete t;
}

void _testRBTPerformanceAutomatic() {
    int lengths[] = {10000, 100000, 1000000, 2000000, 3000000, 4000000, 5000000, 7000000, 8000000, 10000000};
    for(int h = 0 ; h < 1; h++) {
        rbtUi->info("Generating new test files...");
        _deleteTestFiles("rbt");
        for(int i = 0 ; i < sizeof(lengths)/sizeof(lengths[0]); i++) {
            _generateTestFile("rbt", lengths[i]);
        }
        rbtUi->info("Testing adding to RBT");
        _testAddingToRBT();
        rbtUi->info("Testing deleting from RBT");
        _testDeletingFromRBT();
        rbtUi->info("Testing finding in RBT");
        _testFindingInRBT();
    }
    _deleteTestFiles("rbt");
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