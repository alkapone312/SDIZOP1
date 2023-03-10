#include <iostream>
#include <fstream>
#include "Tests.h"
#include "utils/FileReader.h"
#include "ui/UserInterface.h"
#include "ui/ConsoleUI.h"
#include "exception/Exception.h"
#include "utils/RandomNumberGenerator.h"

using namespace std;

int main (int argc, char* argv[]) {   
    SDIZO::RandomNumberGenerator* g = new SDIZO::RandomNumberGenerator();
    SDIZO::UserInterface::setInstance(new SDIZO::ConsoleUI());
    testDoubleSidedList();

    return 0;
} 