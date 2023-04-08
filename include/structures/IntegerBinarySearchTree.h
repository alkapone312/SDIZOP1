#include "structures/IntegerBinaryTreeNode.h"
#include "exception/Exception.h"
#include <functional>

using SDIZO::IntegerBinaryTreeNode;

namespace SDIZO {
    class IntegerBinarySearchTree {
        protected: 
            IntegerBinaryTreeNode* root = nullptr;

        public:
            enum IterationTypes {PREORDER, INORDER, POSTORDER};

            ~IntegerBinarySearchTree();

            /**
             * @brief Adds element to the BST
             * 
             * @param value 
             */
            IntegerBinaryTreeNode* add(int value);
            
            /**
             * @brief Removes node from tree
             * 
             * @return int 
             */
            IntegerBinaryTreeNode* remove(IntegerBinaryTreeNode* node);

            /**
             * @brief Finds node with provided value
             * 
             * @throws SDIZO::Exception
             * @return int 
             */
            IntegerBinaryTreeNode* find(int value);

            /**
             * @brief Get the Root node
             * 
             * @return IntegerBinaryTreeNode* 
             */
            IntegerBinaryTreeNode* getRoot();

            /**
             * @brief Get the Min value in tree
             * 
             * @return IntegerBinaryTreeNode* 
             */
            IntegerBinaryTreeNode* getMin();

            /**
             * @brief Get the Max value in tree
             * 
             * @return IntegerBinaryTreeNode* 
             */
            IntegerBinaryTreeNode* getMax();
            
            /**
             * @brief Apply action for each element with some iterating strategy
             * 
             * @param func 
             * @param type 
             */
            void forEach(const std::function<void(int)>& func, int type = IntegerBinarySearchTree::INORDER);

            /**
             * @brief Rotate tree at node right
             * 
             * @param node 
             */
            void rotateRight(IntegerBinaryTreeNode* node);

            /**
             * @brief Rotate tree at node left
             * 
             * @param node 
             */
            void rotateLeft(IntegerBinaryTreeNode* node);

        protected:
            /**
             * @brief Add node
             * 
             * @param node 
             * @return IntegerBinaryTreeNode* 
             */
            IntegerBinaryTreeNode* add(IntegerBinaryTreeNode* node);

            /**
             * @brief Pre order iteration method
             * 
             * @param func 
             * @param node 
             */
            void preOrder(const std::function<void(int)>& func, IntegerBinaryTreeNode* node);

            /**
             * @brief In order iteration method
             * 
             * @param func 
             * @param node 
             */
            void inOrder(const std::function<void(int)>& func, IntegerBinaryTreeNode* node);

            /**
             * @brief Post order iteration method
             * 
             * @param func 
             * @param node 
             */
            void postOrder(const std::function<void(int)>& func, IntegerBinaryTreeNode* node);

            /**
             * @brief Get the Min Key object get the minimal node in subtree
             * 
             * @param node 
             * @return IntegerBinaryTreeNode* 
             */
            IntegerBinaryTreeNode* getMinKey(IntegerBinaryTreeNode* node);

            /**
             * @brief Get the Maximal node in the sub tree
             * 
             * @param node 
             * @return IntegerBinaryTreeNode* 
             */
            IntegerBinaryTreeNode* getMaxKey(IntegerBinaryTreeNode* node);

            /**
             * @brief Find node successor
             * 
             * @param node 
             * @return IntegerBinaryTreeNode* 
             */
            IntegerBinaryTreeNode* findSuccessor(IntegerBinaryTreeNode* node);

            /**
             * @brief Find node predecessor
             * 
             * @param node 
             * @return IntegerBinaryTreeNode* 
             */
            IntegerBinaryTreeNode* findPredecessor(IntegerBinaryTreeNode* node);

            /**
             * @brief transplant
             * 
             * @param node 
             * @param child 
             */
            void transplant(IntegerBinaryTreeNode* node, IntegerBinaryTreeNode* child);
    };
}
