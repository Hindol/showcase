#pragma once


#include <deque>
#include <functional>
#include <stdexcept>


namespace heap {


inline std::size_t IndexOfParent(std::size_t index)
{ return (index - 1) / 2; }

inline std::size_t IndexOfLeftChild(std::size_t index)
{ return 2 * index + 1; }

inline std::size_t IndexOfRightChild(std::size_t index)
{ return 2 * index + 2; }

template < typename RandIt, class Comp >
void SiftUp(RandIt begin, RandIt end, std::size_t offset, Comp comp)
{
    if (offset > (end - begin))
        throw std::out_of_range("SiftUp(): Offset out of range!");

    while (offset > 0 && comp( begin[offset], begin[IndexOfParent(offset)] ))
    {
        std::swap( begin[IndexOfParent(offset)], begin[offset] );
        offset = IndexOfParent(offset);
    }
}

template < typename RandIt, class Comp >
void SiftDown(RandIt begin, RandIt end, std::size_t offset, Comp comp)
{
    std::size_t size = std::distance( begin, end );

    while (IndexOfRightChild(offset) < size)
    {
        RandIt leftChild = begin + IndexOfLeftChild(offset);
        RandIt rightChild = begin + IndexOfRightChild(offset);

        RandIt minChild = std::min( leftChild, rightChild,
            [&comp](const RandIt first, const RandIt second) { return comp(*first, *second); } );

        if ( comp(*minChild, begin[offset]) )
        {
            std::swap( *minChild, begin[offset] );
            offset = std::distance( begin, minChild );
        }
        else
        {
            return;
        }
    }

    if (IndexOfLeftChild(offset) < size)
    {
        if ( comp(begin[IndexOfLeftChild(offset)], begin[offset]) )
        {
            std::swap( begin[IndexOfLeftChild(offset)], begin[offset] );
        }
    }
}

template < typename RandIt, class Comp >
void Heapify(RandIt begin, RandIt end, Comp comp)
{
    std::size_t size = std::distance( begin, end );

    for (int i = static_cast<int>( IndexOfParent(size - 1) );
            i >= 0; --i)
    {
        SiftDown(begin, end, i, comp);
    }
}

template < typename RandIt, class Comp >
void HeapSort(RandIt begin, RandIt end, Comp comp)
{
    std::reverse_iterator<RandIt> rbegin(end);
    std::reverse_iterator<RandIt> rend(begin);
    Heapify(rbegin, rend, comp);

    while (rend != rbegin)
    {
        std::swap(*rbegin, *--rend);
        SiftDown(rbegin, rend, 0, comp);
    }
}

template < typename RandIt >
inline void HeapSort(RandIt begin, RandIt end)
{
    typedef typename std::iterator_traits<RandIt>::value_type T;
    std::less<T> comp;

    HeapSort(begin, end, comp);
}


template < class T, class Comp = std::less<T> >
class BinaryHeap
{
public:
    BinaryHeap()
    {}

    template <typename FwdIter>
    BinaryHeap(const FwdIter begin, const FwdIter end)
    {
        Insert(begin, end);
    }

    BinaryHeap& operator =(BinaryHeap other)
    {
        swap( *this, other );
        return *this;
    }

    bool Empty() const
    { return elems.empty(); }

    std::size_t Size() const
    { return elems.size(); }

    void Clear()
    { swap( *this, BinaryHeap() ); }

    T Min() const
    { return elems.front(); }

    void DeleteMin()
    {
        std::swap( elems.front(), elems.back() );
        elems.pop_back();
        ::heap::SiftDown(elems.begin(), elems.end(), 0, comp);
    }

    void Insert(const T& elem)
    {
        elems.push_back(elem);
        ::heap::SiftUp(elems.begin(), elems.end(), elems.size() - 1, comp);
    }

    template <typename FwdIter>
    void Insert(const FwdIter begin, const FwdIter end)
    {
        std::copy( begin, end, std::back_inserter(elems) );
        ::heap::Heapify(elems.begin(), elems.end(), comp);
    }

    friend void swap(BinaryHeap& left, BinaryHeap& right)
    {
        std::swap( left.elems, right.elems );
    }

private:
    std::deque<T> elems;
    Comp comp;
};


}
