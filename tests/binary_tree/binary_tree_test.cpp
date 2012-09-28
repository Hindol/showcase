#include "stdafx.h"
#include <binary_tree/binary_tree.h>


class BinaryTreeTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int inArray[] = { 8, 9, 2, 4, 11, 13, 5 };
        inOrderTraversal.insert(std::begin(inOrderTraversal), std::begin(inArray), std::end(inArray));

        int preArray[] = { 4, 9, 8, 2, 5, 11, 13 };
        preOrderTraversal.insert(std::begin(preOrderTraversal), std::begin(preArray), std::end(preArray));

        int postArray[] = { 8, 2, 9, 13, 11, 5, 4 };
        postOrderTraversal.insert(std::begin(postOrderTraversal), std::begin(postArray), std::end(postArray));
    }

    std::vector<int> inOrderTraversal;
    std::vector<int> preOrderTraversal;
    std::vector<int> postOrderTraversal;
};


TEST_F(BinaryTreeTest, BuildTreeFromInOrderPreOrder)
{
    binary_tree::BinaryTree<int> btree(
        std::begin(inOrderTraversal), std::end(inOrderTraversal),
        binary_tree::PRE_ORDER, std::begin(preOrderTraversal), std::end(preOrderTraversal)
        );

    auto inOrderIt = btree.InOrderBegin();
    for (auto value : inOrderTraversal)
    {
        EXPECT_EQ(value, *inOrderIt);
        ++inOrderIt;
    }

    auto preOrderIt = btree.PreOrderBegin();
    for (auto value: preOrderTraversal)
    {
        EXPECT_EQ(value, *preOrderIt);
        ++preOrderIt;
    }
}


TEST_F(BinaryTreeTest, BuildTreeFromInOrderPostOrder)
{
    binary_tree::BinaryTree<int> btree(
        std::begin(inOrderTraversal), std::end(inOrderTraversal),
        binary_tree::POST_ORDER, std::begin(postOrderTraversal), std::end(postOrderTraversal)
        );

    auto inOrderIt = btree.InOrderBegin();
    for (auto value : inOrderTraversal)
    {
        EXPECT_EQ(value, *inOrderIt);
        ++inOrderIt;
    }

    auto postOrderIt = btree.PostOrderBegin();
    for (auto value: postOrderTraversal)
    {
        EXPECT_EQ(value, *postOrderIt);
        ++postOrderIt;
    }
}
