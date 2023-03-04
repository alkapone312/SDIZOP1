#include <iostream>
#include "list/IntegerForwardList.h"

using namespace std;
using namespace SDIZO;

int main (int argc, char* argv[]) {   
    IntegerForwardList* list = new IntegerForwardList();
    for(int i = 0 ; i < 5 ; i ++) {
        list->push(i);
    }

    for(int i = 0 ; i < 5 ; i ++) {
        cout << list->pop() << endl;
    }

    return 0;
} 