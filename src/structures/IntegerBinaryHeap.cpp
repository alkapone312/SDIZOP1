#include "exception/Exception.h"
#include "structures/IntegerBinaryHeap.h"

using namespace SDIZO;

IntegerBinaryHeap::IntegerBinaryHeap() {}
IntegerBinaryHeap::~IntegerBinaryHeap() {}

void IntegerBinaryHeap::push(int value) {
    this->heap->pushBack(value);
    this->bubbleUp(this->heap->getLength() - 1);
}

int IntegerBinaryHeap::pop() {
    if(this->getLength() == 0) {
        throw new Exception((char*)"Tried to pop() out of empty heap!");
    }
    this->heap->first();
    int value = this->heap->getActual();
    if(this->getLength() != 1) {
        this->heap->set(0, this->heap->popBack());
    } else {
        return this->heap->popBack();
    }
    this->bubbleDown(0);

    return value;
}

int IntegerBinaryHeap::find(int value) {
    return this->heap->find(value);
}

int IntegerBinaryHeap::get(int index) {
    return this->heap->get(index);
}

int IntegerBinaryHeap::getLength() {
    return this->heap->getLength();
}

bool IntegerBinaryHeap::isItem() {
    return this->heap->isItem();
}

void IntegerBinaryHeap::next() {
    this->heap->next();
}

void IntegerBinaryHeap::prev() {
    this->heap->prev();
}

int IntegerBinaryHeap::getActual() {
    return this->heap->getActual();
}

void IntegerBinaryHeap::first() {
    this->heap->first();
}

void IntegerBinaryHeap::last() {
    this->heap->last();
}

void IntegerBinaryHeap::bubbleDown(int actualIndex) {
    int leftChildIndex = this->leftChildIndex(actualIndex);
    while(leftChildIndex != -1) {
        int biggerChildIndex = leftChildIndex;
        int rightChildIndex = this->rightChildIndex(actualIndex);
        if(
            rightChildIndex != -1 && 
            this->heap->get(leftChildIndex) < this->heap->get(rightChildIndex) 
        ) {
            biggerChildIndex = rightChildIndex;
        }
        int smallerChildValue = this->heap->get(biggerChildIndex);
        int actualValue = this->heap->get(actualIndex);
        if(smallerChildValue < actualValue) {
            break;
        }
        this->heap->set(biggerChildIndex, actualValue);
        this->heap->set(actualIndex, smallerChildValue);
        actualIndex = biggerChildIndex;
        leftChildIndex = this->leftChildIndex(biggerChildIndex);
    }
}

void IntegerBinaryHeap::bubbleUp(int index) {
    int parent = this->parentIndex(index);
    while(parent != -1 && this->heap->get(parent) < this->heap->get(index)) {
        int buff = this->heap->get(parent);
        this->heap->set(parent, this->heap->get(index));
        this->heap->set(index, buff);
        index = parent;
        parent = this->parentIndex(parent);
    }
}

int IntegerBinaryHeap::leftChildIndex(int nodeIndex) {
    int leftChildIndex = nodeIndex * 2 + 1;
    if(leftChildIndex > this->getLength() - 1) {
        return -1;
    }

    return leftChildIndex;
}

int IntegerBinaryHeap::rightChildIndex(int nodeIndex) {
    int rightChildIndex = nodeIndex * 2 + 2;
    if(rightChildIndex > this->getLength() - 1) {
        return -1;
    }

    return rightChildIndex;
}

int IntegerBinaryHeap::parentIndex(int nodeIndex) {
    if(nodeIndex == 0) {
        return -1;
    }

    return (nodeIndex - 1) / 2;
}