#include "stdafx.h"
#include <binary_heap/binary_heap.h>


class BinaryHeapTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        boost::random::mt19937 gen(std::time(0L));
        boost::random::uniform_int_distribution<> dist(
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max());

        for (int i = 0; i < 100000; ++i)
        {
            randArray.push_back(dist(gen));
        }
    }

    std::vector<int> randArray;
};


TEST_F(BinaryHeapTest, BinaryHeapCtor)
{
    heap::BinaryHeap<int> heap(randArray.begin(), randArray.end());

    std::vector<int> sorted;
    while (!heap.Empty())
    {
        sorted.push_back(heap.Min());
        heap.DeleteMin();
    }

    EXPECT_EQ(randArray.size(), sorted.size());

    EXPECT_EQ(sorted.end(), std::adjacent_find(sorted.begin(), sorted.end(),
        std::greater<int>()));
}


TEST_F(BinaryHeapTest, BinaryHeapInsert)
{
    heap::BinaryHeap<int> heap;
    for (auto it = randArray.begin(); it != randArray.end(); ++it)
    {
        heap.Insert(*it);
    }

    std::vector<int> sorted;
    while (!heap.Empty())
    {
        sorted.push_back(heap.Min());
        heap.DeleteMin();
    }

    EXPECT_EQ(randArray.size(), sorted.size());

    EXPECT_EQ(sorted.end(), std::adjacent_find(sorted.begin(), sorted.end(),
        std::greater<int>()));
}


TEST_F(BinaryHeapTest, BinaryHeapInsertViaFwdIter)
{
    heap::BinaryHeap<int> heap(randArray.begin(), randArray.begin() + randArray.size() / 2);
    heap.Insert(randArray.begin() + randArray.size() / 2, randArray.end());

    std::vector<int> sorted;
    while (!heap.Empty())
    {
        sorted.push_back(heap.Min());
        heap.DeleteMin();
    }

    EXPECT_EQ(randArray.size(), sorted.size());

    EXPECT_EQ(sorted.end(), std::adjacent_find(sorted.begin(), sorted.end(),
        std::greater<int>()));
}


TEST_F(BinaryHeapTest, HeapSort)
{
    heap::HeapSort(randArray.begin(), randArray.end());

    EXPECT_EQ(randArray.end(), std::adjacent_find(randArray.begin(), randArray.end(),
        std::greater<int>()));
}


TEST_F(BinaryHeapTest, HeapSortDescending)
{
    heap::HeapSort(randArray.begin(), randArray.end(), std::greater<int>());

    EXPECT_EQ(randArray.end(), std::adjacent_find(randArray.begin(), randArray.end()));
}
