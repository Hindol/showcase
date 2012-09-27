#include "stdafx.h"
#include <binary_tree/binary_tree.h>


TEST(BinaryTreeTest, BuildTreeFromInOrderPreOrder)
{
    int inOrder[] = { 8, 9, 2, 4, 11, 13, 5 };
    int preOrder[] = { 4, 9, 8, 2, 5, 11, 13 };

    binary_tree::BinaryTree<int> btree(
        std::begin(inOrder), std::end(inOrder),
        binary_tree::BinaryTree<int>::PRE_ORDER, std::begin(preOrder), std::end(preOrder)
        );

    auto inOrderIt = btree.InOrderBegin();
    for (auto value : inOrder)
    {
        EXPECT_EQ(value, inOrderIt->Data());
        ++inOrderIt;
    }

    auto preOrderIt = btree.PreOrderBegin();
    for (auto value: preOrder)
    {
        EXPECT_EQ(value, preOrderIt->Data());
        ++preOrderIt;
    }
}
