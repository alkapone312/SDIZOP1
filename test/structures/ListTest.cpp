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

void _testListPerformance();
void _testListInteractive();
void _displayListFromFront(IntegerDoubleSidedList* list);
void _displayListFromBack(IntegerDoubleSidedList* list);
void _testAddingToListFromBack();
void _testAddingToListFromFront();
void _testDeletingFromListFromFront();
void _testDeletingFromListFromBack();
void _testSearchingInList();
void _testAddingToListAtIndex();
void _testFromListAtIndex();
int _readListDataFront(string fileName, IntegerDoubleSidedList* list);
int _readListDataBack(string fileName, IntegerDoubleSidedList* list);
void _popListDataFront(IntegerDoubleSidedList* list);
void _popListDataBack(IntegerDoubleSidedList* list);
UserInterface* listUi;

void testDoubleSidedList() {
    listUi = UserInterface::getInstance();
    string options[] = {
        "What would you like to do:",
        "1. Performance test",
        "2. Interactive test",
        "3. Generate test file",
        "4. Exit"
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
                testFileGeneration("list");
            break;
            case 4:
                run = false;
            break;
        }
    }
}

void _testListPerformance() {
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
        _readListDataFront(testFileName("list", i), list);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
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
        _readListDataBack(testFileName("list", i), list);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
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
        _popListDataFront(list);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
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
        _popListDataBack(list);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
        delete list;
    }
    delete t;
}

void _testAddingToListAtIndex() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    listUi->info("Please provide a index to add a value.");
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        int size = _readListDataBack(testFileName("list", i), list);
        listUi->info("Please provide a value below " + to_string(size));
        int index = listUi->getNumber();
        index = index < size ? index : size-1;
        t->start();
        list->add(index, 0);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
        delete list;
    }
}

void _testFromListAtIndex() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    listUi->info("Please provide an index to delete.");
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        int size = _readListDataBack(testFileName("list", i), list);
        listUi->info("Please provide a value below " + to_string(size));
        int numberToDelete = listUi->getNumber();
        numberToDelete = numberToDelete < size ? numberToDelete : size-1;
        t->start();
        list->remove(numberToDelete);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
        delete list;
    }
}

void _testSearchingInList() {
    int fileNumber = getNewFileIndex("list");
    Timer* t = new Timer();
    listUi->info("Please provide a number to find.");
    int numberToFind = listUi->getNumber();
    for(int i = 0 ; i < fileNumber; i++) {
        IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
        _readListDataBack(testFileName("list", i), list);
        t->start();
        list->find(numberToFind);
        t->stop();
        listUi->info("Elapsed time: " + to_string(t->getResult()));
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

void _popListDataBack(IntegerDoubleSidedList* list) {  
    try {  
    list->first();
    while(list->isItem()) {
        list->popBack();
        list->first();
    }
    } catch (Exception* e) {
        listUi->error(e->getMessage());
    }
}

void _popListDataFront(IntegerDoubleSidedList* list) {    
    list->first();
    while(list->isItem()) {
        list->popFront();
        list->first();
    }
}


void _testListInteractive() {
    string options[] = {
        "What would you like to do:",
        "1. Add to list from front.",
        "2. Add to list from back.",
        "3. Add to list at any index.",
        "4. Pop from list from front.",
        "5. Pop from list from back.",
        "6. Display list from front.",
        "7. Display list from back.",
        "8. Find element index.",
        "9. Get element under index.",
        "10. Remove element under index.",
        "11. Exit."
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
                _displayListFromFront(list);
            break;
            case 7:
                _displayListFromBack(list);
            break;
            case 8:
                buff = listUi->getNumber();
                listUi->info("Found index: " + to_string(list->find(buff))); 
                _displayListFromFront(list);
            break;
            case 9:
                try {
                    buff = listUi->getNumber();
                    listUi->info("Number under index: " + to_string(list->get(buff))); 
                } catch (Exception* e) {
                    listUi->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 10:
                try {
                    buff = listUi->getNumber();
                    listUi->info("Deleted number: " + to_string(list->remove(buff))); 
                } catch (Exception* e) {
                    listUi->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 11:
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