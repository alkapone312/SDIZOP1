#include <math.h>
#include "exception/Exception.h"
#include "structures/IntegerBinaryHeap.h"
#include "ui/UserInterface.h"
#include "utils/FileReader.h"
#include "utils/FileWriter.h"
#include "utils/Timer.h"
#include "Tests.h"

using namespace SDIZO;
using namespace std;

void _drawHeap(IntegerBinaryHeap* heap);
void _testHeapPerformance();
void _testHeapPerformanceAutomatic();
void _testPushingToHeap();
void _testPoppingFromHeap();
void _testFindingInHeap();
int _readHeapData(string fileName, IntegerBinaryHeap* heap);
void _testHeapInteractive();

UserInterface* heapUi;

void testMaxHeap() {
    heapUi = UserInterface::getInstance();
    string options[] = {
        "What would you like to do:",
        "1. Performance test",
        "2. Interactive test",
        "3. Automatic performance test",
        "4. Generate test file",
        "5. Exit",
        "\0"
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
                _testHeapPerformanceAutomatic();
            break;
            case 4:
                testFileGeneration("heap");
            break;
            case 5:
                run = false;
            break;
        }
    }
}

void _testHeapPerformanceAutomatic() {
    int lengths[] = {10, 100, 500, 1000, 2000, 5000, 10000, 50000, 100000};
    for(int h = 0 ; h < 10; h++) {
        heapUi->info("Generating new test files...");
        _deleteTestFiles("heap");
        for(int i = 0 ; i < sizeof(lengths)/sizeof(lengths[0]); i++) {
            _generateTestFile("heap", lengths[i]);
        }
        heapUi->info("Testing adding to heap.");
        _testPushingToHeap();
        heapUi->info("Testing deleting from heap.");
        _testPoppingFromHeap();
        heapUi->info("Testing finding in heap.");
        _testFindingInHeap();
    }
    _deleteTestFiles("heap");
}

void _testHeapPerformance() {
    string options[] = {
        "What would you like to do:",
        "1. Test adding to hip",
        "2. Test popping from heap",
        "3. Test finding in heap",
        "4. Exit",
        "\0"
    };
    bool run = true;
    while(run) {
        heapUi->menu(options);
        switch (heapUi->getNumber()) {
            case 1:
                _testPushingToHeap();
            break;
            case 2:
                _testPoppingFromHeap();
            break;
            case 3:
                _testFindingInHeap();
            break;
            case 4:
                run = false;
            break;
        }
    }
}

void _testPushingToHeap() {
    int fileNumber = getNewFileIndex("heap");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerBinaryHeap* heap = new IntegerBinaryHeap();
        _readHeapData(testFileName("heap", i), heap);
        t->start();
        heap->push(1);
        t->stop();
        heapUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete heap;
    }
    delete t;
}

void _testPoppingFromHeap() {
    int fileNumber = getNewFileIndex("heap");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerBinaryHeap* heap = new IntegerBinaryHeap();
        _readHeapData(testFileName("heap", i), heap);
        int length = heap->getLength();
        t->start();
            heap->pop();
        t->stop();
        heapUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete heap;
    }
    delete t;
}

void _testFindingInHeap() {
    int fileNumber = getNewFileIndex("heap");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerBinaryHeap* heap = new IntegerBinaryHeap();
        _readHeapData(testFileName("heap", i), heap);
        int length = heap->getLength();
        t->start();
            heap->find(-1);
        t->stop();
        heapUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete heap;
    }
    delete t;
}

int _readHeapData(string fileName, IntegerBinaryHeap* heap) {   
    int fileLength; 
    try {
        FileReader* reader = new FileReader(fileName);
        fileLength = reader->getData();
        heapUi->info("File contains " + to_string(fileLength) + " numbers");
        while (reader->isData()) {
            heap->push(reader->getData());
        }
    } catch (...) {
        heapUi->error("Test file " + fileName + " is corrupted!");
    }

    return fileLength;
}

void _testHeapInteractive() {
    string options[] = {
        "What would you like to do:",
        "1. Test adding to hip",
        "2. Test deleting from heap",
        "3. Test finding in heap",
        "4. Print heap",
        "5. Read from test file",
        "6. Exit",
        "\0"
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
                heapUi->message("From wich testfile you would like to read?");
                _readHeapData(testFileName("heap", heapUi->getNumber()), heap);
            break;
            case 6:
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