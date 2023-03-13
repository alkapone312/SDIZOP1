#include "structures/IntegerBinaryHeap.h"

using namespace SDIZO;

IntegerBinaryHeap::IntegerBinaryHeap() {}
IntegerBinaryHeap::~IntegerBinaryHeap() {}

void IntegerBinaryHeap::push(int value) {
    this->heap->pushBack(value);
    this->bubbleUp(this->heap->getLength());
}

int IntegerBinaryHeap::pop() {
    this->heap->first();
    int value = this->heap->getActual();
    this->heap->set(0, this->heap->popBack());
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
        int smallerChildIndex = leftChildIndex;
        int rightChildIndex = this->rightChildIndex(actualIndex);
        if(
            rightChildIndex != -1 && 
            this->heap->get(leftChildIndex) > this->heap->get(rightChildIndex) 
        ) {
            smallerChildIndex = rightChildIndex;
        }
        int smallerChildValue = this->heap->get(smallerChildIndex);
        int actualValue = this->heap->get(actualIndex);
        if(smallerChildValue < actualValue) {
            break;
        }
        this->heap->set(smallerChildIndex, actualValue);
        this->heap->set(actualIndex, smallerChildValue);
        actualIndex = smallerChildIndex;
        leftChildIndex = this->leftChildIndex(smallerChildIndex);
    }
}

void IntegerBinaryHeap::bubbleUp(int index) {
    int parent = this->parentIndex(index);
    while(parent != -1 && this->heap->get(parent) > this->heap->get(index)) {
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