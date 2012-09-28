#include "stdafx.h"


TEST(BSTTest, OstreamOverloadTest)
{
    binary_tree::BinarySearchTree<int> bst;
    std::cout << bst << std::endl;
}
