#include <iostream>
#include "ui/ConsoleUI.h"

using namespace SDIZO;
using namespace std;

ConsoleUI::ConsoleUI() {}

ConsoleUI::~ConsoleUI() {}

int ConsoleUI::getNumber() {
    string potentialNumber;
    this->message("Please provide a number:");
    cin >> potentialNumber;

    return this->stringToNumber(potentialNumber);
}

void ConsoleUI::menu(string* options) {
    try {
        int i = 0;
        while(options[i] != "\0") {
            this->message(options[i]);
            i++;
        }
    } catch (...) {}
}

void ConsoleUI::info(string messsage) {
    cout << "\u001b[44mInfo message:\u001b[0m " << messsage << endl;
}

void ConsoleUI::error(string errorMessage) {
    cout << "\u001b[41;1mERROR:\u001b[0m " << errorMessage << endl;
}

void ConsoleUI::message(string message) {
    cout << "\u001b[42mMessage:\u001b[0m " << message << endl;
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