#include <iostream>
#include <fstream>
#include "Tests.h"
#include "ui/UserInterface.h"
#include "ui/ConsoleUI.h"
#include "exception/Exception.h"
#include "structures/IntegerDynamicArray.h"

using namespace std;

int main (int argc, char* argv[]) {   
    SDIZO::UserInterface::setInstance(new SDIZO::ConsoleUI());
    testDoubleSidedList();
    testDynamicArray();
    
    return 0;
} 