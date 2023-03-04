#include <iostream>
#include "list/IntegerDoubleSidedList.h"
#include "exception/Exception.h"

using namespace std;
using namespace SDIZO;

int main (int argc, char* argv[]) {   
    IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
    
    for(int i = 0 ; i < 5000; i++) {
        list->pushBack(i);
    }

    return 0;
} 