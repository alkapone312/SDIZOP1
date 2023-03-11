#include "structures/IntegerDoubleSidedList.h"
#include "exception/Exception.h"

using namespace SDIZO;

IntegerDoubleSidedList::IntegerDoubleSidedList() {}

IntegerDoubleSidedList::~IntegerDoubleSidedList() {
    while(this->head) {
        IntegerDoubleSidedListNode* buff = this->head;
        this->head = this->head->next;
        delete buff;
    }
}

void IntegerDoubleSidedList::pushFront(int value) {
    IntegerDoubleSidedListNode* newNode = new IntegerDoubleSidedListNode;
    newNode->value = value;
    if(this->setIfEmpty(newNode)) {
        return;
    }
    this->head->prev = newNode;
    this->head->prev->next = this->head;
    this->head = newNode;
    this->length++;
}

void IntegerDoubleSidedList::pushBack(int value) {
    IntegerDoubleSidedListNode* newNode = new IntegerDoubleSidedListNode;
    newNode->value = value;
    if(this->setIfEmpty(newNode)) {
        return;
    }
    this->tail->next = newNode;
    this->tail->next->prev = this->tail;
    this->tail = newNode;
    this->length++;
}

int IntegerDoubleSidedList::popFront() {
    if(!this->length) {
        throw new Exception((char*)"Tried to popFront() out of empty array!");
    }

    IntegerDoubleSidedListNode* oldHead = this->head;
    this->head = this->head->next;
    this->deleteConnection(oldHead, this->head);
    this->length--;

    if(!this->length) {
        this->head = nullptr;
        this->tail = nullptr;
    }
    
    return this->getValueAndDelete(oldHead);
}

int IntegerDoubleSidedList::popBack() {
    if(!this->length) {
        throw new Exception((char*)"Tried to popBack() out of empty array!");
    }

    IntegerDoubleSidedListNode* oldTail = this->tail;
    this->tail = this->tail->prev;
    this->deleteConnection(this->tail, oldTail);
    this->length--;

    if(!this->length) {
        this->head = nullptr;
        this->tail = nullptr;
    }

    return this->getValueAndDelete(oldTail);
}

int IntegerDoubleSidedList::get(int index) {
    this->checkIndex(index);
    IntegerDoubleSidedListNode* actual = this->head;
    for(int i = 0 ; i < index; i++) {
        actual = actual->next;
    }

    return actual->value;
}

int IntegerDoubleSidedList::remove(int index) {
    this->checkIndex(index);
    IntegerDoubleSidedListNode* actual = this->head;
    for(int i = 0 ; i < index; i++) {
        actual = actual->next;
    }
    if(actual->next) {
        actual->next->prev = actual->prev ? actual->prev : nullptr;
    }
    if(actual->prev) {
        actual->prev->next = actual->next ? actual->next : nullptr;
    }
    this->length--;

    return this->getValueAndDelete(actual);
}

void IntegerDoubleSidedList::add(int index, int value) {
    this->checkIndex(index);
    IntegerDoubleSidedListNode* newNode = new IntegerDoubleSidedListNode;
    newNode->value = value;
    if(this->setIfEmpty(newNode)) {
        return;
    }
    IntegerDoubleSidedListNode* actual = this->head;
    for(int i = 0 ; i < index; i++) {
        actual = actual->next;
    }
    if(actual->next) {
        newNode->prev = actual;
        newNode->next = actual->next;
        actual->next->prev = newNode;
        actual->next = newNode;

        return;
    }

    newNode->prev = actual;
    actual->next = newNode;
}

int IntegerDoubleSidedList::getLength() {
    return this->length;
}

int IntegerDoubleSidedList::find(int value) {
    IntegerDoubleSidedListNode* actual = this->head;
    for(int i = 0 ; i < this->length; i++) {
        if(actual->value == value) {
            return i;
        }
        actual = actual->next;
    }
    
    return -1;
}

void IntegerDoubleSidedList::checkIndex(int index) {
    if(index >= this->length || index < 0) {
        throw new Exception((char*)"Index out of bounds!"); 
    }
}

bool IntegerDoubleSidedList::isItem() {
    return this->actual != nullptr;
}

void IntegerDoubleSidedList::next() {
    this->actual = this->actual->next;
}

void IntegerDoubleSidedList::prev() {
    this->actual = this->actual->prev;
}

int IntegerDoubleSidedList::getActual() {
    return this->actual->value;
}

void IntegerDoubleSidedList::first() {
    this->actual = this->head;
}

void IntegerDoubleSidedList::last() {
    this->actual = this->tail;
}


int IntegerDoubleSidedList::getValueAndDelete(IntegerDoubleSidedListNode* node) {
    int value = node->value;
    delete node;

    return value;
}

bool IntegerDoubleSidedList::setIfEmpty(IntegerDoubleSidedListNode* node) {
    if(!this->length) {
        this->head = node; 
        this->tail = node;
        this->length++;

        return true;
    }

    return false;
}

void IntegerDoubleSidedList::deleteConnection(IntegerDoubleSidedListNode* item1, IntegerDoubleSidedListNode* item2) {
    if(item1 != nullptr) {
        item1->next = nullptr;
    }

    if(item2 != nullptr) {
        item2->prev = nullptr;
    }
}
