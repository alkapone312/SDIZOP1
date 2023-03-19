#include "structures/Iterable.h"

namespace SDIZO {
    struct IntegerBinarySearchTreeNode
    {
        IntegerBinarySearchTreeNode* left = nullptr;
        IntegerBinarySearchTreeNode* right = nullptr;
        IntegerBinarySearchTreeNode* parent = nullptr;
        int value;
    };
    

    class IntegerBinarySearchTree : public Iterable {
        private: 
            IntegerBinarySearchTreeNode* root = nullptr;

        public:
            enum IterationTypes {PREORDER, INORDER, POSTORDER};

            /**
             * @brief Adds element to the BST
             * 
             * @param value 
             */
            void add(int value);
            
            /**
             * @brief Removes node from tree
             * 
             * @return int 
             */
            IntegerBinarySearchTreeNode* remove(IntegerBinarySearchTreeNode* node);

            /**
             * @brief Finds node with provided value
             * 
             * @return int 
             */
            IntegerBinarySearchTreeNode* find(int value);

            /**
             * @brief Get the Min value in tree
             * 
             * @return IntegerBinarySearchTreeNode* 
             */
            IntegerBinarySearchTreeNode* getMin();

            /**
             * @brief Get the Max value in tree
             * 
             * @return IntegerBinarySearchTreeNode* 
             */
            IntegerBinarySearchTreeNode* getMax();
            
            /**
             * @brief Apply action for each element with some iterating strategy
             * 
             * @param func 
             * @param type 
             */
            void forEach(void (*func)(int), int type = IntegerBinarySearchTree::INORDER);

        private:
            void preOrder(void (*func)(int), IntegerBinarySearchTreeNode* node);
            void inOrder(void (*func)(int), IntegerBinarySearchTreeNode* node);
            void postOrder(void (*func)(int), IntegerBinarySearchTreeNode* node);
            IntegerBinarySearchTreeNode* getMinKey(IntegerBinarySearchTreeNode* node);
            IntegerBinarySearchTreeNode* getMaxKey(IntegerBinarySearchTreeNode* node);
            IntegerBinarySearchTreeNode* findSuccessor(IntegerBinarySearchTreeNode* node);
            IntegerBinarySearchTreeNode* findPredecessor(IntegerBinarySearchTreeNode* node);
    };
}
