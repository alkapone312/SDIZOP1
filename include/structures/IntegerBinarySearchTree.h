#include "exception/Exception.h"
#include <functional>

namespace SDIZO {
    struct IntegerBinarySearchTreeNode
    {
        IntegerBinarySearchTreeNode* left = nullptr;
        IntegerBinarySearchTreeNode* right = nullptr;
        IntegerBinarySearchTreeNode* parent = nullptr;
        int value;
    };
    

    class IntegerBinarySearchTree {
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
             * @throws SDIZO::Exception
             * @return int 
             */
            IntegerBinarySearchTreeNode* find(int value);

            /**
             * @brief Get the Root node
             * 
             * @return IntegerBinarySearchTreeNode* 
             */
            IntegerBinarySearchTreeNode* getRoot();

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
            void forEach(const std::function<void(int)>& func, int type = IntegerBinarySearchTree::INORDER);

        private:
            /**
             * @brief Pre order iteration method
             * 
             * @param func 
             * @param node 
             */
            void preOrder(const std::function<void(int)>& func, IntegerBinarySearchTreeNode* node);

            /**
             * @brief In order iteration method
             * 
             * @param func 
             * @param node 
             */
            void inOrder(const std::function<void(int)>& func, IntegerBinarySearchTreeNode* node);

            /**
             * @brief Post order iteration method
             * 
             * @param func 
             * @param node 
             */
            void postOrder(const std::function<void(int)>& func, IntegerBinarySearchTreeNode* node);

            /**
             * @brief Get the Min Key object get the minimal node in subtree
             * 
             * @param node 
             * @return IntegerBinarySearchTreeNode* 
             */
            IntegerBinarySearchTreeNode* getMinKey(IntegerBinarySearchTreeNode* node);

            /**
             * @brief Get the Maximal node in the sub tree
             * 
             * @param node 
             * @return IntegerBinarySearchTreeNode* 
             */
            IntegerBinarySearchTreeNode* getMaxKey(IntegerBinarySearchTreeNode* node);

            /**
             * @brief Find node successor
             * 
             * @param node 
             * @return IntegerBinarySearchTreeNode* 
             */
            IntegerBinarySearchTreeNode* findSuccessor(IntegerBinarySearchTreeNode* node);

            /**
             * @brief Find node predecessor
             * 
             * @param node 
             * @return IntegerBinarySearchTreeNode* 
             */
            IntegerBinarySearchTreeNode* findPredecessor(IntegerBinarySearchTreeNode* node);
    };
}
