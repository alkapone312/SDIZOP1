#include "list/IntegerDoubleSidedList.h"
#include "exception/Exception.h"
#include <iostream>

using namespace SDIZO;

IntegerDoubleSidedList::IntegerDoubleSidedList() {}

IntegerDoubleSidedList::~IntegerDoubleSidedList() {}

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

void IntegerDoubleSidedList::deleteConnection(IntegerDoubleSidedListNode* item1, IntegerDoubleSidedListNode* item2) {
    if(item1 != nullptr) {
        item1->next = nullptr;
    }

    if(item2 != nullptr) {
        item2->prev = nullptr;
    }
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

void IntegerDoubleSidedList::checkIndex(int index) {
    if(index >= this->length && index < 0) {
        throw new Exception((char*)"Index out of bounds!"); 
    }
}

int IntegerDoubleSidedList::getValueAndDelete(IntegerDoubleSidedListNode* node) {
    int value = node->value;
    delete node;

    return value;
}