#include "list/IntegerForwardList.h"

using namespace SDIZO;

IntegerForwardList::IntegerForwardList() {}
IntegerForwardList::~IntegerForwardList() {}

void IntegerForwardList::push(int value) {
    IntegerForwardListNode* buff = this->head;
    this->head = new IntegerForwardListNode;
    this->head->value = value;
    this->head->next = buff;
    this->length++;
}

int IntegerForwardList::pop() {
    IntegerForwardListNode* buff = this->head;
    if(this->head == nullptr) {
        throw this->LIST_EMPTY;
    }
    int value  = this->head->value;
    this->head = this->head->next;
    this->length--;
    delete buff;

    return value;
}

int IntegerForwardList::get(int index) {
    return 0;
}

IntegerForwardListNode* IntegerForwardList::find() {
    return new IntegerForwardListNode();
}