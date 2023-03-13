#include "exception/Exception.h"
#include "structures/IntegerDynamicArray.h"
#include <iostream>

using namespace SDIZO;
using namespace std;

IntegerDynamicArray::IntegerDynamicArray() {}
IntegerDynamicArray::~IntegerDynamicArray() {}

void IntegerDynamicArray::pushBack(int value) {
    this->add(this->length, value);
}

void IntegerDynamicArray::pushFront(int value) {
    this->add(0, value);
}

void IntegerDynamicArray::add(int index, int value) {
    this->checkIndex(index);
    int* buff = new int[this->length + 1];
    buff[index] = value;
    for(int i = 0 ; i < index; i++) {
        buff[i] = this->dynamicArray[i];
    }
    for(int i = index; i < this->length; i++) {
        buff[i+1] = this->dynamicArray[i];
    }
    delete this->dynamicArray;
    this->dynamicArray = buff;
    this->length++;
}

int IntegerDynamicArray::popBack() {
    if(!this->dynamicArray) {
        throw new Exception((char*)"Tried to popBack() out of empty array!");
    }
    this->length--;
    int value = this->dynamicArray[this->length];
    int* buff = new int[this->length];
    for(int i = 0 ; i < this->length; i++) {
        buff[i] = this->dynamicArray[i];
    }
    delete[] this->dynamicArray;
    this->dynamicArray = buff;
    if(!this->length) {
        this->dynamicArray = nullptr;
    }

    return value;
}

int IntegerDynamicArray::popFront() {
    if(!this->dynamicArray) {
        throw new Exception((char*)"Tried to popFront() out of empty array!");
    }
    this->length--;
    int value = this->dynamicArray[0];
    int* buff = new int[this->length];
    for(int i = 0; i < this->length; i++) {
        buff[i] = this->dynamicArray[i+1];
    }
    delete[] this->dynamicArray;
    this->dynamicArray = buff;
    if(!this->length) {
        this->dynamicArray = nullptr;
    }

    return value;
}

int IntegerDynamicArray::remove(int index) {
    this->checkIndex(index);
    this->length--;
    int value = this->dynamicArray[index];
    int* buff = new int[this->length];
    for(int i = 0; i < index; i++) {
        buff[i] = this->dynamicArray[i];
    }
    for(int i = 0; i < this->length; i++) {
        buff[i] = this->dynamicArray[i+1];
    }
    delete[] this->dynamicArray;
    this->dynamicArray = buff;
    if(!this->length) {
        this->dynamicArray = nullptr;
    }

    return value;
}

int IntegerDynamicArray::find(int value) {
    for(int i = 0 ; i < this->length; i++) {
        if(this->dynamicArray[i] == value) {
            return i;
        }
    }

    return -1;
}

int IntegerDynamicArray::get(int index) {
    this->checkIndex(index);
    
    return this->dynamicArray[index];
}

int IntegerDynamicArray::getLength() {
    return this->length;
}

bool IntegerDynamicArray::isItem() {
    return this->actualIndex >= 0 && this->actualIndex < this->length;
}

void IntegerDynamicArray::next() {
    this->actualIndex++;
}

void IntegerDynamicArray::prev() {
    this->actualIndex--;
}

int IntegerDynamicArray::getActual() {
    return this->dynamicArray[this->actualIndex];
}

void IntegerDynamicArray::first() {
    this->actualIndex = 0;
}

void IntegerDynamicArray::last() {
    this->actualIndex = this->length - 1;
}

void IntegerDynamicArray::checkIndex(int index) {
    if(index != 0 && index > this->length || index < 0) {
        throw new Exception((char*)"Index out of bounds!"); 
    }
}