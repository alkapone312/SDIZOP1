namespace SDIZO {
    struct IntegerDoubleSidedListNode {
        IntegerDoubleSidedListNode* prev;
        IntegerDoubleSidedListNode* next;
        int value;
    };

    class IntegerDoubleSidedList {
        private:
            IntegerDoubleSidedListNode head;
            IntegerDoubleSidedListNode tail;
            int length = 0;
        public:
            IntegerDoubleSidedList();
            ~IntegerDoubleSidedList();
            virtual void pushBack(int value);
            virtual void pushFront(int value);
            virtual int popBack();
            virtual int popFront();
            virtual int get(int index);
            virtual IntegerDoubleSidedList* find(int value);
    };
}