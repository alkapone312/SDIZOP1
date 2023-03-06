#include <iostream>
#include "ui/ConsoleUI.h"

using namespace SDIZO;
using namespace std;

ConsoleUI::ConsoleUI() {}

ConsoleUI::~ConsoleUI() {}

int ConsoleUI::getNumber() {
    string potentialNumber;
    this->info("Please provide a number:");
    cin >> potentialNumber;

    return this->stringToNumber(potentialNumber);
}

void ConsoleUI::menu(string* options) {
    try {
        int i = 0;
        while(true) {
            this->info(options[i]);
            i++;
        }
    } catch (...) {}
}

void ConsoleUI::info(string messsage) {
    cout << "Info message: " << messsage << endl;
}

void ConsoleUI::error(string errorMessage) {
    cout << "ERROR: " << errorMessage << endl;
}

int ConsoleUI::stringToNumber(string potentialNumber) {
    try {
        return stoi(potentialNumber);
    } catch(...) {
        return -1;
    }
}

void ConsoleUI::wait() {
    this->info("Click enter to continue...");
    cin.ignore();
    cin.get();
}