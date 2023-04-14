#include "structures/IntegerBinarySearchTree.h"

using namespace std;

namespace SDIZO {
	enum {
		RED, 
		BLACK, 
		DOUBLE_BLACK
	};

	struct IntegerBlackRedTreeNode : public IntegerBinaryTreeNode {
		int color = RED;
	};

	class IntegerBlackRedTree : public IntegerBinarySearchTree {
		public:
		~IntegerBlackRedTree();
		
		/**
		 * @brief Add new key to tree
		 * 
		 * @param key 
		 */
		void add(int key);

		/**
		 * @brief Remove element from tree
		 * 
		 * @param node
		 */
		void remove(IntegerBlackRedTreeNode* node);

		/**
		 * @brief Get the Root of the tree
		 * 
		 * @return IntegerBlackRedTreeNode* 
		 */
		IntegerBlackRedTreeNode* getRoot();

		private:
		/**
		 * @brief Fix br tree after deletion
		 * 
		 * @param node 
		 */
		void deleteFix(IntegerBlackRedTreeNode* &node);

		/**
		 * @brief Fix br tree after insertion
		 * 
		 * @param node 
		 */
		void insertFix(IntegerBlackRedTreeNode* &node);

		/**
		 * @brief Get the color of node
		 * 
		 * @param node 
		 * @return int 
		 */
		int color(IntegerBlackRedTreeNode* node);

		/**
		 * @brief Get the color of node
		 * 
		 * @param node 
		 * @return int 
		 */
		void setColor(IntegerBlackRedTreeNode* node, int color);

		/**
		 * @brief Get left child (typecast)
		 * 
		 * @param node 
		 * @return IntegerBlackRedTreeNode* 
		 */
		IntegerBlackRedTreeNode* left(IntegerBlackRedTreeNode* node);
		
		/**
		 * @brief Get right child (typecast)
		 * 
		 * @param node 
		 * @return IntegerBlackRedTreeNode* 
		 */
		IntegerBlackRedTreeNode* right(IntegerBlackRedTreeNode* node);
		
		/**
		 * @brief Get parent (typecast)
		 * 
		 * @param node 
		 * @return IntegerBlackRedTreeNode* 
		 */
		IntegerBlackRedTreeNode* parent(IntegerBlackRedTreeNode* node);

		/**
		 * @brief Get grandparent of node 
		 * 
		 * @param node 
		 * @return IntegerBlackRedTreeNode* 
		 */
		IntegerBlackRedTreeNode* grandparent(IntegerBlackRedTreeNode* node);

		/**
		 * @brief Get uncle of node 
		 * 
		 * @param node 
		 * @return IntegerBlackRedTreeNode* 
		 */
		IntegerBlackRedTreeNode* uncle(IntegerBlackRedTreeNode* node);

		/**
		 * @brief Does node has parent
		 * 
		 * @param node 
		 * @return true 
		 * @return false 
		 */
		bool hasParent(IntegerBinaryTreeNode* node);

		/**
		 * @brief Does node has grandparent 
		 * 
		 * @param node 
		 * @return true 
		 * @return false 
		 */
		bool hasGrandparent(IntegerBinaryTreeNode* node);

		/**
		 * @brief Does node has uncle
		 * 
		 * @param node 
		 * @return true 
		 * @return false 
		 */
		bool hasUncle(IntegerBinaryTreeNode* node);
	};
};