namespace SDIZO {   
    struct IntegerBinaryTreeNode {
        IntegerBinaryTreeNode* left = nullptr;
        IntegerBinaryTreeNode* right = nullptr;
        IntegerBinaryTreeNode* parent = nullptr;
        int count = 0;
        int value;
    };
}