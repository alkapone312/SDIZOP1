#include <iostream>
#include <string>
#include "structures/IntegerDynamicArray.h"
#include "exception/Exception.h"
#include "ui/UserInterface.h"
#include "utils/FileWriter.h"
#include "utils/FileReader.h"
#include "utils/Timer.h"
#include "Tests.h"

using namespace std;
using namespace SDIZO;

void _testArrayPerformance();
void _testArrayInteractive();
void _testArrayPerformanceAutomatic();
void _displayArrayFromFront(IntegerDynamicArray* array);
void _displayArrayFromBack(IntegerDynamicArray* array);
void _testAddingToArrayFromBack();
void _testAddingToArrayFromFront();
void _testDeletingFromArrayFromFront();
void _testDeletingFromArrayFromBack();
void _testSearchingInArray();
void _testAddingToArrayAtIndex();
void _testDeletingFromArrayAtIndex();
int _readDataFront(string fileName, IntegerDynamicArray* Array);
int _readDataBack(string fileName, IntegerDynamicArray* Array);
void _popDataFront(IntegerDynamicArray* array);
void _popDataBack(IntegerDynamicArray* array);
UserInterface* arrayUi;

void testDynamicArray() {
    arrayUi = UserInterface::getInstance();
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
        arrayUi->menu(options);
        switch(arrayUi->getNumber()) {
            case 1:
                _testArrayPerformance();
            break;
            case 2:
                _testArrayInteractive();
            break;
            case 3:
                _testArrayPerformanceAutomatic();
            break;
            case 4:
                testFileGeneration("array");
            break;
            case 5:
                run = false;
            break;
        }
    }
}

void _testArrayPerformanceAutomatic() {
    int lengths[] = {10, 100, 500, 1000, 2000, 5000, 10000, 50000, 100000};
    for(int h = 0 ; h < 10; h++) {
        arrayUi->info("Generating new test files.");
        _deleteTestFiles("array");
        for(int i = 0 ; i < sizeof(lengths)/sizeof(lengths[0]); i++) {
            _generateTestFile("array", lengths[i]);
        }
        _testAddingToArrayFromFront();
        arrayUi->info("Testing adding to array at front.");
        _testAddingToArrayFromBack();
        arrayUi->info("Testing adding to array at back.");
        _testAddingToArrayAtIndex();
        arrayUi->info("Testing adding to array at the middle.");
        _testDeletingFromArrayFromFront();
        arrayUi->info("Testing deleting from array from front.");
        _testDeletingFromArrayFromBack();
        arrayUi->info("Testing deleting from array from back.");
        _testDeletingFromArrayAtIndex();
        arrayUi->info("Testing deleting from array from middle.");
        _testSearchingInArray();
    }
    _deleteTestFiles("array");
}

void _testArrayPerformance() {
    string options[] = {
        "What would you like to do:",
        "1. Test appending to array from front.",
        "2. Test appending to array from back.",
        "3. Test appending to array from middle.",
        "4. Test deleting from array from front.",
        "5. Test deleting from array from back.",
        "6. Test deleting from array from middle.",
        "7. Test searching in array.",
        "8. Exit."
    };
    arrayUi->info("Performance tests are run from testfiles folder under testfiles/array/test{index}.txt. Each testfile will be run through the command that you would like to test. Please note that test file data should be integers separated by white spaces where first integer is the number of incoming data.");
    arrayUi->wait();

    bool run = true;
    while(run) {
        arrayUi->menu(options);
        switch(arrayUi->getNumber()) {
            case 1:
                _testAddingToArrayFromFront();
            break;
            case 2:
                _testAddingToArrayFromBack();
            break;
            case 3:
                _testAddingToArrayAtIndex();
            break;
            case 4:
                _testDeletingFromArrayFromFront();
            break;
            case 5:
                _testDeletingFromArrayFromBack();
            break;
            case 6:
                _testDeletingFromArrayAtIndex();
            break;
            case 7:
                _testSearchingInArray();
            case 8:
                run = false;
            break;
        }
    }

}

void _testAddingToArrayFromFront() {
    int fileNumber = getNewFileIndex("array");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDynamicArray* array = new IntegerDynamicArray();
        _readDataFront(testFileName("array", i), array);
        t->start();
        array->pushFront(1);
        t->stop();
        arrayUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete array;
    }
    delete t;
}

void _testAddingToArrayFromBack() {
    int fileNumber = getNewFileIndex("array");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDynamicArray* array = new IntegerDynamicArray();
        _readDataBack(testFileName("array", i), array);
        t->start();
        array->pushBack(1);
        t->stop();
        arrayUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete array;
    }
    delete t;
}

void _testDeletingFromArrayFromFront() {
    int fileNumber = getNewFileIndex("array");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDynamicArray* array = new IntegerDynamicArray();
        _readDataFront(testFileName("array", i), array);
        t->start();
        array->popFront();
        t->stop();
        arrayUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete array;
    }
    delete t;
}

void _testDeletingFromArrayFromBack() {
    int fileNumber = getNewFileIndex("array");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDynamicArray* array = new IntegerDynamicArray();
        _readDataBack(testFileName("array", i), array);
        t->start();
        array->popBack();
        t->stop();
        arrayUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete array;
    }
    delete t;
}

void _testAddingToArrayAtIndex() {
    int fileNumber = getNewFileIndex("array");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDynamicArray* array = new IntegerDynamicArray();
        int size = _readDataBack(testFileName("array", i), array);
        arrayUi->info("Adding to index at: " + to_string(size/2));
        t->start();
        array->add(size/2, 0);
        t->stop();
        arrayUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete array;
    }
}

void _testDeletingFromArrayAtIndex() {
    int fileNumber = getNewFileIndex("array");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDynamicArray* array = new IntegerDynamicArray();
        int size = _readDataBack(testFileName("array", i), array);
        arrayUi->info("Deleting from index: " + to_string(size/2));
        t->start();
        array->remove(size/2);
        t->stop();
        arrayUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete array;
    }
}

void _testSearchingInArray() {
    int fileNumber = getNewFileIndex("array");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDynamicArray* array = new IntegerDynamicArray();
        _readDataBack(testFileName("array", i), array);
        t->start();
        array->find(-1);
        t->stop();
        arrayUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete array;
    }
}

int _readDataBack(string fileName, IntegerDynamicArray* array) {   
    int fileLength; 
    try {
        FileReader* reader = new FileReader(fileName);
        fileLength = reader->getData();
        arrayUi->info("File contains " + to_string(fileLength) + " numbers");
        while (reader->isData()) {
            array->pushBack(reader->getData());
        }
    } catch (...) {
        arrayUi->error("Test file " + fileName + " is corrupted!");
    }

    return fileLength;
}

int _readDataFront(string fileName, IntegerDynamicArray* array) {    
    int fileLength; 
    try {
        FileReader* reader = new FileReader(fileName);
        fileLength = reader->getData();
        arrayUi->info("File contains " + to_string(fileLength) + " numbers");
        while (reader->isData()) {
            array->pushFront(reader->getData());
        }
    } catch (...) {
        arrayUi->error("Test file " + fileName + " is corrupted!");
    }

    return fileLength;
}

void _popDataBack(IntegerDynamicArray* array) {  
    try {  
    array->first();
    while(array->isItem()) {
        array->popBack();
        array->first();
    }
    } catch (Exception* e) {
        arrayUi->error(e->getMessage());
    }
}

void _popDataFront(IntegerDynamicArray* array) {    
    array->first();
    while(array->isItem()) {
        array->popFront();
        array->first();
    }
}


void _testArrayInteractive() {
    string options[] = {
        "What would you like to do:",
        "1. Add to array from front.",
        "2. Add to array from back.",
        "3. Pop from array from front.",
        "4. Pop from array from back.",
        "5. Display array from front.",
        "6. Display array from back.",
        "7. Find element index.",
        "8. Get element under index.",
        "9. Remove element under index.",
        "10. Exit."
    };

    IntegerDynamicArray* array = new IntegerDynamicArray();
    bool run = true;
    while(run) {
        arrayUi->menu(options);
        int buff;
        string sbuff = "";
        switch(arrayUi->getNumber()) {
            case 1:
                array->pushFront(arrayUi->getNumber());
                _displayArrayFromFront(array);
            break;
            case 2:
                array->pushBack(arrayUi->getNumber());
                _displayArrayFromFront(array);
            break;
            case 3:
                try {
                    arrayUi->info("Popped value: " + to_string(array->popFront()));
                } catch(Exception* e) {
                    arrayUi->error(e->getMessage());
                }
                _displayArrayFromFront(array);
            break;
            case 4:
                try {
                    arrayUi->info("Popped value: " + to_string(array->popBack()));
                } catch(Exception* e) {
                    arrayUi->error(e->getMessage());
                }
                _displayArrayFromFront(array);
            break;
            case 5:
                _displayArrayFromFront(array);
            break;
            case 6:
                _displayArrayFromBack(array);
            break;
            case 7:
                buff = arrayUi->getNumber();
                arrayUi->info("Found index: " + to_string(array->find(buff))); 
                _displayArrayFromFront(array);
            break;
            case 8:
                try {
                    buff = arrayUi->getNumber();
                    arrayUi->info("Number under index: " + to_string(array->get(buff))); 
                } catch (Exception* e) {
                    arrayUi->error(e->getMessage());
                }
                _displayArrayFromFront(array);
            break;
            case 9:
                try {
                    buff = arrayUi->getNumber();
                    arrayUi->info("Deleted number: " + to_string(array->remove(buff))); 
                } catch (Exception* e) {
                    arrayUi->error(e->getMessage());
                }
                _displayArrayFromFront(array);
            break;
            case 10:
                run = false;
            break;
        }
    }
}

void _displayArrayFromFront(IntegerDynamicArray* array) {
    string sbuff = "";
    for(array->first(); array->isItem(); array->next()) {
        sbuff += to_string(array->getActual()) + " ";
    }
    arrayUi->info("Array: " + sbuff);
    arrayUi->wait();
}

void _displayArrayFromBack(IntegerDynamicArray* array) {
    string sbuff = "";
    for(array->last(); array->isItem(); array->prev()) {
        sbuff += to_string(array->getActual()) + " ";
    }
    arrayUi->info("Array backwards: " + sbuff);
    arrayUi->wait();
}