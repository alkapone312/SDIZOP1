#pragma once
#include "structures/Iterable.h"

namespace SDIZO {
    class IntegerDynamicArray : public SDIZO::Iterable {
        private:
            int* dynamicArray = new int[0];
            int length = 0;
            int actualIndex = 0;
        public:
            IntegerDynamicArray();
            ~IntegerDynamicArray();

            /**
             * @brief Push to the back of array
             * 
             * @param value 
             */
            void pushBack(int value);

            /**
             * @brief Push to the front of array
             * 
             * @param value 
             */
            void pushFront(int value);

            /**
             * @brief Add value at specific index
             * 
             * @param index 
             */
            void add(int index, int value);

            /**
             * @brief Remove value from last position
             * 
             * @return int 
             */
            int popBack();

            /**
             * @brief Remove value from the first position
             * 
             * @return int 
             */
            int popFront();

            /**
             * @brief Remove value at specific index
             * 
             * @param index 
             * @return int 
             */
            int remove(int index);

            /**
             * @brief Find value index at specific index
             * 
             * @param value
             * @return int | -1 if no value found
             */
            int find(int value);

            /**
             * @brief Get value from specific index
             * 
             * @param index
             * @return int
             */
            int get(int index);

            /**
             * @brief Set value at specified index.
             * 
             * @param index 
             * @param value 
             */
            void set(int index, int value);

            /**
             * @brief Get the Length of array
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
             * @brief Instantiare
             * 
             * @param value 
             */
            bool fillIfEmpty(int value);

            /**
             * @brief Checks if index is not out of bounds
             * 
             * @param index 
             */
            void checkIndex(int index);
    };
}