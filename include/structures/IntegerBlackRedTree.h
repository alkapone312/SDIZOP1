#include "structures/IntegerBinarySearchTree.h"

namespace SDIZO {
    struct IntegerBlackRedTreeNode : public IntegerBinaryTreeNode {
        bool red = true;
    };

    class IntegerBlackRedTree : public SDIZO::IntegerBinarySearchTree {
        public:
            /**
             * @brief Adds element to the BRT
             * 
             * @param value 
             */
            void add(int value);

            /**
             * @brief Deletes from black red tree
             * 
             * @param node 
             */
            void remove(IntegerBlackRedTreeNode* node);

        protected:
            /**
             * @brief Fix after insertion
             * 
             * @param node 
             */
            void fixInsert(IntegerBlackRedTreeNode* node);
            
            /**
             * @brief Fix tree after delete
             * 
             */
            void fixDelete(IntegerBlackRedTreeNode* node);
    };
}
