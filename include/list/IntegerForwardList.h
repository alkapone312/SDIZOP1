
namespace SDIZO {
    struct IntegerForwardListNode {
        IntegerForwardListNode* next;
        int value;
    };

    class IntegerForwardList {
        private:
            IntegerForwardListNode* head;
            int length = 0;
            int value;
        public:
            IntegerForwardList();
            ~IntegerForwardList();
            virtual void push(int value);
            virtual int get(int index);
            virtual int pop();
            virtual IntegerForwardListNode* find();
    };
}
