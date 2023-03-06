#include <iostream>
#include <string>
#include "list/IntegerDoubleSidedList.h"
#include "exception/Exception.h"
#include "ui/UserInterface.h"
#include "file/FileReader.h"
#include "Tests.h"

using namespace std;
using namespace SDIZO;

void _testPerformance();
void _testInteractive();
void _displayListFromFront(IntegerDoubleSidedList* list);
void _displayListFromBack(IntegerDoubleSidedList* list);
UserInterface* ui;

void testDoubleSidedList() {
    ui = UserInterface::getInstance();
    string options[] = {
        "What would you like to do:",
        "1. Performance test",
        "2. Interactive test",
        "3. Exit"
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
                run = false;
            break;
        }
    }
}

void _testPerformance() {
    string options[] = {
        "What would you like to do:",
        "1. Test appending to list from front."
    };
    ui->info("Performance tests are run from testfiles folder under testfiles/list/test{index}.txt. Each testfile will be run through the command that you would like to test. Please note that test file data should be integers separated by white spaces where first integer is the number of incoming data.");
    ui->wait();
    bool run = true;
    while(run) {
        ui->menu(options);
        switch(ui->getNumber()) {
            case 2:
                run = false;
            break;
        }
        run = false;
    }

}

void readData(string fileName, IntegerDoubleSidedList* list) {
    int i = 0;
    FileReader* reader = new FileReader(fileName);
    reader->getData();
    try {
    while (reader->isData()) {
        list->pushBack(stoi(reader->getData()));
    }
    } catch (...) {
        ui->error("Test file " + fileName + " is corrupted!");
    }
    
    i++;
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
                    ui->message("Popped value: " + to_string(list->popFront()));
                } catch(Exception* e) {
                    ui->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 4:
                try {
                    ui->message("Popped value: " + to_string(list->popBack()));
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
                try {
                    buff = ui->getNumber();
                    ui->message("Found index: " + to_string(list->get(buff))); 
                } catch (Exception* e) {
                    ui->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 8:
                try {
                    buff = ui->getNumber();
                    ui->message("Number under index: " + to_string(list->get(buff))); 
                } catch (Exception* e) {
                    ui->error(e->getMessage());
                }
                _displayListFromFront(list);
            break;
            case 9:
                try {
                    buff = ui->getNumber();
                    ui->message("Deleted number: " + to_string(list->remove(buff))); 
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
    for(list->setActual(0); list->isItem(); list->next()) {
        sbuff += to_string(list->getActual()) + " ";
    }
    ui->message("List: " + sbuff);
    ui->wait();
}

void _displayListFromBack(IntegerDoubleSidedList* list) {
    string sbuff = "";
    for(list->setActual(list->getLength()-1); list->isItem(); list->prev()) {
        sbuff += to_string(list->getActual()) + " ";
    }
    ui->message("List backwards: " + sbuff);
    ui->wait();
}