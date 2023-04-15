namespace SDIZO {   
    struct IntegerBinaryTreeNode {
        IntegerBinaryTreeNode* left = nullptr;
        IntegerBinaryTreeNode* right = nullptr;
        IntegerBinaryTreeNode* parent = nullptr;
        int count = 1;
        int value;
    };
}