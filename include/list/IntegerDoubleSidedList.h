namespace SDIZO {
    struct IntegerDoubleSidedListNode {
        IntegerDoubleSidedListNode* prev = nullptr;
        IntegerDoubleSidedListNode* next = nullptr;
        int value;
    };

    class IntegerDoubleSidedList {
        private:
            IntegerDoubleSidedListNode* head;
            IntegerDoubleSidedListNode* tail;
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
            virtual void pushBack(int value);

            /**
             * @brief Pushes value at the front of the list.
             * 
             * @param value 
             */
            virtual void pushFront(int value);

            /**
             * @brief Pops value out of back of the list.
             * 
             * @throw SDIZO::Exception
             * @return int 
             */
            virtual int popBack();

            /**
             * @brief Pops value out of front of the list.
             * 
             * @throw SDIZO::Exception
             * @return int 
             */
            virtual int popFront();

            /**
             * @brief Gets value of list item at specified index
             * 
             * @throw SDIZO::Exception
             * @param index 
             * @return int 
             */
            virtual int get(int index);

            /**
             * @brief Removes item with specified index
             * 
             * @throw SDIZO::Exception
             * @param index 
             * @return int 
             */
            virtual int remove(int index);

            /**
             * @brief Get the length list.
             * 
             * @return int 
             */
            virtual int getLength();

            /**
             * @brief Finds an index of a value.
             * 
             * @param value 
             * @return int 
             */
            virtual int find(int value);

            /**
             * @brief Checks whether actual item is not null
             * 
             * @return true 
             * @return false 
             */
            virtual bool isItem();

            /**
             * @brief Changes actual pointer to next member.
             * 
             */
            virtual void next();

            /**
             * @brief Changes actual pointer to previous member.
             * 
             */
            virtual void prev();

            /**
             * @brief Gets the actual list item
             * 
             * @return int
             */
            virtual int getActual();

            /**
             * @brief Sets the actual pointer to an index
             * 
             * @param index 
             */
            virtual void setActual(int index);
        private:
    
            /**
             * @brief Deletes connection between two nodes in given order.
             * 
             * @param item1 
             * @param item2 
             */
            virtual void deleteConnection(IntegerDoubleSidedListNode* item1, IntegerDoubleSidedListNode* item2);
            
            /**
             * @brief Set the head and tail if list is empty. 
             * 
             * @param node 
             * @return true 
             * @return false 
             */
            virtual bool setIfEmpty(IntegerDoubleSidedListNode* node);

            /**
             * @brief Get the value and free object memory.
             * 
             * @param node 
             * @return int 
             */
            virtual int getValueAndDelete(IntegerDoubleSidedListNode* node);

            /**
             * @brief Throws SDIZO::Exception if index is out of bounds.
             * 
             * @throw SDIZO::Exception
             * @param index 
             */
            virtual void checkIndex(int index);
    };
}