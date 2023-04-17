#include <iostream>
#include <string>
#include "structures/IntegerDoubleSidedList.h"
#include "exception/Exception.h"
#include "ui/UserInterface.h"
#include "utils/FileReader.h"
#include "utils/FileWriter.h"
#include "utils/Timer.h"
#include "Tests.h"

using namespace std;
using namespace SDIZO;

void _testListPerformance();
void _testListInteractive();
void _testListPerformanceAutomatic();
void _displayListFromFront(IntegerDoubleSidedList* list);
void _displayListFromBack(IntegerDoubleSidedList* list);
void _testAddingToListFromBack();
void _testAddingToListFromFront();
void _testDeletingFromListFromFront();
void _testDeletingFromListFromBack();
void _testSearchingInList();
void _testAddingToListAtIndex();
void _testDeletingFromListAtIndex();
int _readListDataFront(string fileName, IntegerDoubleSidedList* list);
int _readListDataBack(string fileName, IntegerDoubleSidedList* list);
UserInterface* listUi;

void testDoubleSidedList() {
    listUi = UserInterface::getInstance();
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
        listUi->menu(options);
        switch(listUi->getNumber()) {
            case 1:
                _testListPerformance();
            break;
            case 2:
                _testListInteractive();
            break;
            case 3:
                _testListPerformanceAutomatic();
            break;
            case 4:
                testFileGeneration("list");
            break;
            case 5:
                run = false;
            break;
        }
    }
}

void _testListPerformanceAutomatic() {
    int lengths[] = {10000, 100000, 1000000, 2000000, 3000000, 4000000, 5000000, 7000000, 8000000, 10000000};
    for(int h = 0 ; h < 10; h++) {
        listUi->info("Generating new test files...");
        _deleteTestFiles("list");
        for(int i = 0 ; i < sizeof(lengths)/sizeof(lengths[0]); i++) {
            _generateTestFile("list", lengths[i]);
        }
        listUi->info("Testing adding to list from front");
        _testAddingToListFromFront();
        listUi->info("Testing adding to list from back");
        _testAddingToListFromBack();
        listUi->info("Testing adding to list at middle");
        _testAddingToListAtIndex();
        listUi->info("Testing deleting from list from front");
        _testDeletingFromListFromFront();
        listUi->info("Testing deleting from list from back");
        _testDeletingFromListFromBack();
        listUi->info("Testing deleting from list from middle");
        _testDeletingFromListAtIndex();
        listUi->info("Testing searching in list");
    }
    _deleteTestFiles("list");
}

void _testListPerformance() {
    string options[] = {
        "What would you like to do:",
        "1. Test appending to list from front.",
        "2. Test appending to list from back.",
        "3. Test appendig to list at index.",
        "4. Test deleting from list from front.",
        "5. Test deleting from list from back.",
        "6. Test deleting from list at index.",
        "7. Test searching in list.",
        "8. Exit.",
        "\0"
    };
    listUi->info("Performance tests are run from testfiles folder under testfiles/list/test{index}.txt. Each testfile will be run through the command that you would like to test. Please note that test file data should be integers separated by white spaces where first integer is the number of incoming data.");
    listUi->wait();

    bool run = true;
    while(run) {
        listUi->menu(options);
        switch(listUi->getNumber()) {
            case 1:
                _testAddingToListFromFront();
            break;
            case 2:
                _testAddingToListFromBack();
            break;
            case 3:
                _testAddingToListAtIndex();
            break;
            case 4:
                _testDeletingFromListFromFront();
            break;
            case 5:
                _testDeletingFromListFromBack();
            break;
            case 6:
                _testDeletingFromListAtIndex();
            break;
            case 7:
                _testSearchingInList();
            case 8:
                run = false;
            break;
        }
    }
}

void _testAddingToListFromFront() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        _readListDataFront(testFileName("list", i), list);
        t->start();
        list->pushFront(0);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete list;
    }
    delete t;
}

void _testAddingToListFromBack() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        _readListDataBack(testFileName("list", i), list);
        t->start();
        list->pushBack(0);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete list;
    }
    delete t;
}

void _testDeletingFromListFromFront() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        _readListDataFront(testFileName("list", i), list);
        t->start();
        list->popFront();
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete list;
    }
    delete t;
}

void _testDeletingFromListFromBack() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        _readListDataBack(testFileName("list", i), list);
        t->start();
        list->popBack();
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete list;
    }
    delete t;
}

void _testAddingToListAtIndex() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        int size = _readListDataBack(testFileName("list", i), list);
        listUi->info("Adding to list at index:" + to_string(size/2));
        t->start();
        list->add(size/2, 0);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete list;
    }
}

void _testDeletingFromListAtIndex() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        int size = _readListDataBack(testFileName("list", i), list);
        listUi->info("Deleting from list at index:" + to_string(size/2));
        t->start();
        list->remove(size/2);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete list;
    }
}

void _testSearchingInList() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    listUi->info("Please provide a number to find.");
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        _readListDataBack(testFileName("list", i), list);
        t->start();
        list->find(-1);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
        FileWriter* w = new FileWriter("results", FileWriter::Mode::APPEND); w->write(to_string(t->getResult()) + "\n"); delete w;
        delete list;
    }
}

int _readListDataBack(string fileName, IntegerDoubleSidedList* list) {   
    int fileLength; 
    try {
        FileReader* reader = new FileReader(fileName);
        fileLength = reader->getData();
        listUi->info("File contains " + to_string(fileLength) + " numbers");
        while (reader->isData()) {
            list->pushBack(reader->getData());
        }
    } catch (...) {
        listUi->error("Test file " + fileName + " is corrupted!");
    }

    return fileLength;
}

int _readListDataFront(string fileName, IntegerDoubleSidedList* list) {    
    int fileLength; 
    try {
        FileReader* reader = new FileReader(fileName);
        fileLength = reader->getData();
        listUi->info("File contains " + to_string(fileLength) + " numbers");
        while (reader->isData()) {
            list->pushFront(reader->getData());
        }
    } catch (...) {
        listUi->error("Test file " + fileName + " is corrupted!");
    }

    return fileLength;
}

void _testListInteractive() {
    string options[] = {
        "What would you like to do:",
        "1. Add to list from front.",
        "2. Add to list from back.",
        "3. Add to list at any index.",
        "4. Pop from list from front.",
        "5. Pop from list from back.",
        "6. Remove from list from index",
        "7. Display list from front.",
        "8. Display list from back.",
        "9. Find element index.",
        "10. Get element under index.",
        "11. Remove element under index.",
        "12. Exit.",
        "\0"
    };

    IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
    bool run = true;
    while(run) {
        listUi->menu(options);
        int buff;
        string sbuff = "";
        switch(listUi->getNumber()) {
            case 1:
                list->pushFront(listUi->getNumber());
                _displayListFromFront(list);
            break;
            case 2:
                list->pushBack(listUi->getNumber());
                _displayListFromFront(list);
            break;
            case 3:
                try {
                    listUi->info("Provide index:");
                    buff = listUi->getNumber();
                    listUi->info("Provide value:");
                    list->add(buff, listUi->getNumber());
                        _displayListFromFront(list);
                } catch (Exception* e) {
                    listUi->error(e->getMessage());
                }
            break;
            case 4:
                try {
                    listUi->info("Popped value: " + to_string(list->popFront()));
                } catch(Exception* e) {
                    listUi->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 5:
                try {
                    listUi->info("Popped value: " + to_string(list->popBack()));
                } catch(Exception* e) {
                    listUi->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 6:
                try {
                    listUi->info("Removed value: " + to_string(list->remove(listUi->getNumber())));
                } catch(Exception* e) {
                    listUi->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 7:
                _displayListFromFront(list);
            break;
            case 8:
                _displayListFromBack(list);
            break;
            case 9:
                buff = listUi->getNumber();
                listUi->info("Found index: " + to_string(list->find(buff))); 
                _displayListFromFront(list);
            break;
            case 10:
                try {
                    buff = listUi->getNumber();
                    listUi->info("Number under index: " + to_string(list->get(buff))); 
                } catch (Exception* e) {
                    listUi->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 11:
                try {
                    buff = listUi->getNumber();
                    listUi->info("Deleted number: " + to_string(list->remove(buff))); 
                } catch (Exception* e) {
                    listUi->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 12:
                run = false;
            break;
        }
    }
}

void _displayListFromFront(IntegerDoubleSidedList* list) {
    string sbuff = "";
    for(list->first(); list->isItem(); list->next()) {
        sbuff += to_string(list->getActual()) + " ";
    }
    listUi->info("List: " + sbuff);
    listUi->wait();
}

void _displayListFromBack(IntegerDoubleSidedList* list) {
    string sbuff = "";
    for(list->last(); list->isItem(); list->prev()) {
        sbuff += to_string(list->getActual()) + " ";
    }
    listUi->info("List backwards: " + sbuff);
    listUi->wait();
}