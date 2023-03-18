#include <math.h>
#include "exception/Exception.h"
#include "structures/IntegerBinaryHeap.h"
#include "ui/UserInterface.h"
#include "Tests.h"

using namespace SDIZO;
using namespace std;

void _drawHeap(IntegerBinaryHeap* heap);
void _testHeapPerformance();
void _testHeapInteractive();

UserInterface* heapUi;

void testMaxHeap() {
    heapUi = UserInterface::getInstance();
    string options[] = {
        "What would you like to do:",
        "1. Performance test",
        "2. Interactive test",
        "3. Generate test file",
        "4. Exit"
    };
    bool run = true;
    while(run) {
        heapUi->menu(options);
        switch(heapUi->getNumber()) {
            case 1:
                _testHeapPerformance();
            break;
            case 2:
                _testHeapInteractive();
            break;
            case 3:
                testFileGeneration("heap");
            break;
            case 4:
                run = false;
            break;
        }
    }
}

void _testHeapPerformance() {

}

void _testHeapInteractive() {
    string options[] = {
        "What would you like to do:",
        "1. Test adding to hip",
        "2. Test deleting from heap",
        "3. Test finding in heap",
        "4. Print heap",
        "5. Exit"
    };
    bool run = true;
    IntegerBinaryHeap* heap = new IntegerBinaryHeap;
    while(run) {
        heapUi->menu(options);
        switch (heapUi->getNumber()) {
            case 1:
                heap->push(heapUi->getNumber());
                _drawHeap(heap);
            break;
            case 2:
                try {
                    heapUi->info("Popped value: " + to_string(heap->pop()));
                    _drawHeap(heap);
                } catch (Exception* e) {
                    heapUi->error(e->getMessage());
                }
            break;
            case 3:
                heapUi->info(
                    "Found index: " + to_string(
                        heap->find(heapUi->getNumber())
                    )
                );
                _drawHeap(heap);
            break;
            case 4:
                _drawHeap(heap);
            break;
            case 5:
                run = false;
            break;
        }
    }
}

void _drawHeap(IntegerBinaryHeap* heap) {
    const int digitSpaceAround = 5;
    const int length = heap->getLength();
    const int numberOfLevels = log2(length) + 1;
    int numberOfItems = 1;
    int maxRowLength = numberOfLevels * 2 * numberOfItems * digitSpaceAround * 2;
    string digitString;
    int numberOfDigits;
    string heapString = "";
    string line = "";
    heap->first();
    for(int i = 0 ; i < numberOfLevels; i++) {
        int acc = 0;
        line = "";
        int actualItems;
        int spaceBetweenElements = maxRowLength / (numberOfItems + 1);
        for(int j = 0 ; j < numberOfItems; j++) {
            if(!heap->isItem()) {
                break;
            }
            digitString = to_string(heap->getActual());
            numberOfDigits = digitString.length();
            line.append(spaceBetweenElements - numberOfDigits / 2, ' ');
            line += digitString;
            heap->next();
            actualItems = j + 1;
        }
        numberOfItems *= 2;
        heapString += "\n" + line + "\n";
    }

    heapUi->message(heapString);
}