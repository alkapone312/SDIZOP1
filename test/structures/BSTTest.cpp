#include "Tests.h"
#include "ui/UserInterface.h"

using namespace SDIZO;
using namespace std;

void _testBSTPerformance();
void _testBSTInteractive();

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

}