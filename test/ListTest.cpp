#include "list/IntegerDoubleSidedList.h"
#include <iostream>
#include "Tests.h"

using namespace std;
using namespace SDIZO;


void _testDoubleSidedListPushFrontPopFront();

void testDoubleSidedList() {
    _testDoubleSidedListPushFrontPopFront();
}

void _testDoubleSidedListPushFrontPopFront() {
    IntegerDoubleSidedList* list = new IntegerDoubleSidedList();
    for(int i = 0 ; i < 10; i++) {
        list->pushFront(i);
    }

    cout << "Push at front, pop from front:" << endl;

    for(int i = 0; i < list->getLength(); i++) {
        cout << list->popFront() << " ";
    }

    cout << endl;
}