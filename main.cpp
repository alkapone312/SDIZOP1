#include <iostream>
#include <fstream>
#include "Tests.h"
#include "ui/UserInterface.h"
#include "ui/ConsoleUI.h"
#include "exception/Exception.h"
#include "structures/IntegerDynamicArray.h"

using namespace std;

int main (int argc, char* argv[]) {   
    SDIZO::UserInterface::setInstance(new SDIZO::ConsoleUI());
    SDIZO::UserInterface* ui = SDIZO::UserInterface::getInstance();
    string options[] = {
        "1. Test double sided list",
        "2. Test dynamic array",
        "3. Test heap",
        "4. Test binary search tree",
        "5. Test black red tree",
        "6. Exit"
    };
    bool run = true;
    while (run) {
        ui->menu(options);
        switch (ui->getNumber()) {
            case 1:
                testDoubleSidedList();
            break;
            case 2:
                testDynamicArray();
            break;
            case 3:
                testMaxHeap();
            break;
            case 4:
                testBinarySearchTree();
            break;
            case 5:
                testBlackRedTree();
            break;
            case 6:
                run = false;
            break;
            
            default:
            break;
        }
    }
    
    return 0;
} 