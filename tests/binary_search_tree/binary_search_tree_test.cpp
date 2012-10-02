#include "stdafx.h"


class BSTTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        boost::random::mt19937 gen(std::time(0L));
        boost::random::uniform_int_distribution<> dist(
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max());

        for (int i = 0; i < 1000000; ++i)
        {
            randArray.push_back(dist(gen));
        }
    }

    std::vector<int> randArray;
};


TEST_F(BSTTest, SortedOutputTest)
{
    binary_tree::BinarySearchTree<int> bst;

    for (auto& elem : randArray)
    {
        bst.Insert(elem);
    }

    EXPECT_TRUE(std::is_sorted(bst.InOrderBegin(), bst.InOrderEnd(), std::less<int>()));
}


TEST(BSTTest, OstreamOverloadTest)
{
    binary_tree::BinarySearchTree<int> bst;
    std::cout << bst << std::endl;
}
