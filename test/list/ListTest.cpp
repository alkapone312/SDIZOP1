#include <iostream>
#include <string>
#include "structures/IntegerDoubleSidedList.h"
#include "exception/Exception.h"
#include "ui/UserInterface.h"
#include "utils/FileReader.h"
#include "utils/Timer.h"
#include "Tests.h"

using namespace std;
using namespace SDIZO;

void _testPerformance();
void _testInteractive();
void _displayListFromFront(IntegerDoubleSidedList* list);
void _displayListFromBack(IntegerDoubleSidedList* list);
void _testAddingToListFromBack();
void _testAddingToListFromFront();
void _testDeletingFromListFromFront();
void _testDeletingFromListFromBack();
void _testSearchingInList();
void _testAddingToListAtIndex();
void _testFromListAtIndex();
int _readDataFront(string fileName, IntegerDoubleSidedList* list);
int _readDataBack(string fileName, IntegerDoubleSidedList* list);
void _popDataFront(IntegerDoubleSidedList* list);
void _popDataBack(IntegerDoubleSidedList* list);
UserInterface* ui;

void testDoubleSidedList() {
    ui = UserInterface::getInstance();
    string options[] = {
        "What would you like to do:",
        "1. Performance test",
        "2. Interactive test",
        "3. Generate test file",
        "4. Exit"
    };
    bool run = true;
    while(run) {
        ui->menu(options);
        switch(ui->getNumber()) {
            case 1:
                _testPerformance();
            break;
            case 2:
                _testInteractive();
            break;
            case 3:
                testFileGeneration("list");
            break;
            case 4:
                run = false;
            break;
        }
    }
}

void _testPerformance() {
    string options[] = {
        "What would you like to do:",
        "1. Test appending to list from front.",
        "2. Test appending to list from back.",
        "3. Test deleting from list from front.",
        "4. Test deleting from list from back.",
        "5. Test adding to list at index.",
        "6. Test deleting from list at index.",
        "7. Test searching in list.",
        "8. Exit."
    };
    ui->info("Performance tests are run from testfiles folder under testfiles/list/test{index}.txt. Each testfile will be run through the command that you would like to test. Please note that test file data should be integers separated by white spaces where first integer is the number of incoming data.");
    ui->wait();

    bool run = true;
    while(run) {
        ui->menu(options);
        switch(ui->getNumber()) {
            case 1:
                _testAddingToListFromFront();
            break;
            case 2:
                _testAddingToListFromBack();
            break;
            case 3:
                _testDeletingFromListFromFront();
            break;
            case 4:
                _testDeletingFromListFromBack();
            break;
            case 5:
                _testAddingToListAtIndex();
            break;
            case 6:
                _testFromListAtIndex();
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
        t->start();
        _readDataFront(testFileName("list", i), list);
        t->stop();
        ui->info("Elapsed time: " + to_string(t->getResult()));
        delete list;
    }
    delete t;
}

void _testAddingToListFromBack() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        t->start();
        _readDataBack(testFileName("list", i), list);
        t->stop();
        ui->info("Elapsed time: " + to_string(t->getResult()));
        delete list;
    }
    delete t;
}

void _testDeletingFromListFromFront() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        _readDataFront(testFileName("list", i), list);
        t->start();
        _popDataFront(list);
        t->stop();
        ui->info("Elapsed time: " + to_string(t->getResult()));
        delete list;
    }
    delete t;
}

void _testDeletingFromListFromBack() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        _readDataBack(testFileName("list", i), list);
        t->start();
        _popDataBack(list);
        t->stop();
        ui->info("Elapsed time: " + to_string(t->getResult()));
        delete list;
    }
    delete t;
}

void _testAddingToListAtIndex() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    ui->info("Please provide a index to add a value.");
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        int size = _readDataBack(testFileName("list", i), list);
        ui->info("Please provide a value below " + to_string(size));
        int index = ui->getNumber();
        index = index < size ? index : size-1;
        t->start();
        list->add(index, 0);
        t->stop();
        ui->info("Elapsed time: " + to_string(t->getResult()));
        delete list;
    }
}

void _testFromListAtIndex() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    ui->info("Please provide an index to delete.");
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        int size = _readDataBack(testFileName("list", i), list);
        ui->info("Please provide a value below " + to_string(size));
        int numberToDelete = ui->getNumber();
        numberToDelete = numberToDelete < size ? numberToDelete : size-1;
        t->start();
        list->remove(numberToDelete);
        t->stop();
        ui->info("Elapsed time: " + to_string(t->getResult()));
        delete list;
    }
}

void _testSearchingInList() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    ui->info("Please provide a number to find.");
    int numberToFind = ui->getNumber();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        _readDataBack(testFileName("list", i), list);
        t->start();
        list->find(numberToFind);
        t->stop();
        ui->info("Elapsed time: " + to_string(t->getResult()));
        delete list;
    }
}

int _readDataBack(string fileName, IntegerDoubleSidedList* list) {   
    int fileLength; 
    try {
        FileReader* reader = new FileReader(fileName);
        fileLength = reader->getData();
        ui->info("File contains " + to_string(fileLength) + " numbers");
        while (reader->isData()) {
            list->pushBack(reader->getData());
        }
    } catch (...) {
        ui->error("Test file " + fileName + " is corrupted!");
    }

    return fileLength;
}

int _readDataFront(string fileName, IntegerDoubleSidedList* list) {    
    int fileLength; 
    try {
        FileReader* reader = new FileReader(fileName);
        fileLength = reader->getData();
        ui->info("File contains " + to_string(fileLength) + " numbers");
        while (reader->isData()) {
            list->pushFront(reader->getData());
        }
    } catch (...) {
        ui->error("Test file " + fileName + " is corrupted!");
    }

    return fileLength;
}

void _popDataBack(IntegerDoubleSidedList* list) {  
    try {  
    list->first();
    while(list->isItem()) {
        list->popBack();
        list->first();
    }
    } catch (Exception* e) {
        ui->error(e->getMessage());
    }
}

void _popDataFront(IntegerDoubleSidedList* list) {    
    list->first();
    while(list->isItem()) {
        list->popFront();
        list->first();
    }
}


void _testInteractive() {
    string options[] = {
        "What would you like to do:",
        "1. Add to list from front.",
        "2. Add to list from back.",
        "3. Pop from list from front.",
        "4. Pop from list from back.",
        "5. Display list from front.",
        "6. Display list from back.",
        "7. Find element index.",
        "8. Get element under index.",
        "9. Remove element under index.",
        "10. Exit."
    };

    IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
    bool run = true;
    while(run) {
        ui->menu(options);
        int buff;
        string sbuff = "";
        switch(ui->getNumber()) {
            case 1:
                list->pushFront(ui->getNumber());
                _displayListFromFront(list);
            break;
            case 2:
                list->pushBack(ui->getNumber());
                _displayListFromFront(list);
            break;
            case 3:
                try {
                    ui->info("Popped value: " + to_string(list->popFront()));
                } catch(Exception* e) {
                    ui->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 4:
                try {
                    ui->info("Popped value: " + to_string(list->popBack()));
                } catch(Exception* e) {
                    ui->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 5:
                _displayListFromFront(list);
            break;
            case 6:
                _displayListFromBack(list);
            break;
            case 7:
                buff = ui->getNumber();
                ui->info("Found index: " + to_string(list->find(buff))); 
                _displayListFromFront(list);
            break;
            case 8:
                try {
                    buff = ui->getNumber();
                    ui->info("Number under index: " + to_string(list->get(buff))); 
                } catch (Exception* e) {
                    ui->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 9:
                try {
                    buff = ui->getNumber();
                    ui->info("Deleted number: " + to_string(list->remove(buff))); 
                } catch (Exception* e) {
                    ui->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 10:
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
    ui->info("List: " + sbuff);
    ui->wait();
}

void _displayListFromBack(IntegerDoubleSidedList* list) {
    string sbuff = "";
    for(list->last(); list->isItem(); list->prev()) {
        sbuff += to_string(list->getActual()) + " ";
    }
    ui->info("List backwards: " + sbuff);
    ui->wait();
}