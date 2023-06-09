#pragma once
#include "structures/Iterable.h"
#include "structures/IntegerDynamicArray.h"

using SDIZO::IntegerDynamicArray;

namespace SDIZO {
    class IntegerBinaryHeap : public Iterable {
        private:
            IntegerDynamicArray* heap = new IntegerDynamicArray;
        public:
            IntegerBinaryHeap();
            
            ~IntegerBinaryHeap();

            /**
             * @brief Push value at the end of heap
             * 
             * @param value 
             */
            void push(int value);

            /**
             * @brief Pop value out of heap top
             * 
             * @return int
             */
            int pop();

            /**
             * @brief Find index of an element
             * 
             * @param value 
             * @return int 
             */
            int find(int value);

            /**
             * @brief Get element under index
             * 
             * @param index 
             * @return int 
             */
            int get(int index);

            /**
             * @brief Get the length of heap
             * 
             * @return int 
             */
            int getLength();

            /**
             * @brief Checks whether actual item is not null
             * 
             * @return true 
             * @return false 
             */
            bool isItem();

            /**
             * @brief Changes actual pointer to next member.
             * 
             */
            void next();

            /**
             * @brief Changes actual pointer to previous member.
             * 
             */
            void prev();

            /**
             * @brief Gets the actual list item
             * 
             * @return int
             */
            int getActual();

            /**
             * @brief Sets iterator to start of an data structure
             */
            void first();

            /**
             * @brief Sets iterator to end of an data structure
             * 
             */
            void last();

        private:
            /**
             * @brief 
             * 
             */
            void bubbleDown(int index);

            /**
             * @brief 
             * 
             */
            void bubbleUp(int index);

            /**
             * @brief Get the index of left child -1 if don't exist
             * 
             * @param nodeIndex 
             * @return int 
             */
            int leftChildIndex(int nodeIndex);

            /**
             * @brief Get the index of right child -1 if don't exist
             * 
             * @param nodeIndex 
             * @return int 
             */
            int rightChildIndex(int nodeIndex);

            /**
             * @brief Get the index of node parent -1 if don't exist
             * 
             * @return int 
             */
            int parentIndex(int nodeIndex);
    };
}