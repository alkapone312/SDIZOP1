#include "structures/Iterable.h"

namespace SDIZO {
    struct IntegerDoubleSidedListNode {
        IntegerDoubleSidedListNode* prev = nullptr;
        IntegerDoubleSidedListNode* next = nullptr;
        int value;
    };

    class IntegerDoubleSidedList : public SDIZO::Iterable {
        private:
            IntegerDoubleSidedListNode* head = nullptr;
            IntegerDoubleSidedListNode* tail = nullptr;
            IntegerDoubleSidedListNode* actual = head;
            int length = 0;
        public:
            IntegerDoubleSidedList();
            ~IntegerDoubleSidedList();

            /**
             * @brief Pushes value at the end of the list
             * 
             * @param value 
             */
            void pushBack(int value);

            /**
             * @brief Pushes value at the front of the list.
             * 
             * @param value 
             */
            void pushFront(int value);

            /**
             * @brief Pops value out of back of the list.
             * 
             * @throw SDIZO::Exception
             * @return int 
             */
            int popBack();

            /**
             * @brief Pops value out of front of the list.
             * 
             * @throw SDIZO::Exception
             * @return int 
             */
            int popFront();

            /**
             * @brief Gets value of list item at specified index
             * 
             * @throw SDIZO::Exception
             * @param index 
             * @return int 
             */
            int get(int index);

            /**
             * @brief Removes item with specified index
             * 
             * @throw SDIZO::Exception
             * @param index 
             * @return int 
             */
            int remove(int index);
            
            /**
             * @brief Adds an item to the specific index
             * 
             * @param index 
             * @param value 
             */
            void add(int index, int value);

            /**
             * @brief Get the length list.
             * 
             * @return int 
             */
            int getLength();

            /**
             * @brief Finds an index of a value.
             * 
             * @param value 
             * @return int 
             */
            int find(int value);

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
             * @brief Deletes connection between two nodes in given order.
             * 
             * @param item1 
             * @param item2 
             */
            void deleteConnection(IntegerDoubleSidedListNode* item1, IntegerDoubleSidedListNode* item2);
            
            /**
             * @brief Set the head and tail if list is empty. 
             * 
             * @param node 
             * @return true 
             * @return false 
             */
            bool setIfEmpty(IntegerDoubleSidedListNode* node);

            /**
             * @brief Get the value and free object memory.
             * 
             * @param node 
             * @return int 
             */
            int getValueAndDelete(IntegerDoubleSidedListNode* node);

            /**
             * @brief Throws SDIZO::Exception if index is out of bounds.
             * 
             * @throw SDIZO::Exception
             * @param index 
             */
            void checkIndex(int index);
    };
}