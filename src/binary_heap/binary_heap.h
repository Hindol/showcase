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
        typedef typename std::iterator_traits<RandIt>::value_type T;

        std::size_t size = std::distance( begin, end );

        while (IndexOfRightChild(offset) < size)
        {
            T& minChild = const_cast<T&>(
                        std::min( begin[IndexOfLeftChild(offset)],
                                  begin[IndexOfRightChild(offset)],
                                  comp )
                        );

            if ( comp(minChild, begin[offset]) )
            {
                std::swap( minChild, begin[offset] );
                offset = std::distance( begin, &minChild );
            }
            else
            {
                break;
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

        for (int i = static_cast<int>( IndexOfParent(size) );
             i >= 0; --i)
        {
            SiftDown(begin, end, i, comp);
        }
    }

    template < typename RandIt, class Comp >
    void HeapSort(RandIt begin, RandIt end, Comp comp)
    {
        for (RandIt it = begin; it != end; ++it)
        {
            heap::Heapify(it, end, comp);
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

        template <typename Iter>
        BinaryHeap(Iter begin, Iter end)
        {
            std::copy( begin, end, std::back_inserter(elems) );
            Heapify();
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
            SiftDown(0);
        }

        void Insert(const T& elem)
        {
            elems.push_back(elem);
            SiftUp(elems.size() - 1);
        }

        friend void swap(BinaryHeap& left, BinaryHeap& right)
        {
            std::swap( left.elems, right.elems );
        }

    private:
        void Heapify()
        {
            for (int i = static_cast<int>( IndexOfParent(elems.size()) );
                 i >= 0; --i)
            {
                SiftDown(i);
            }
        }

        void SiftUp(std::size_t index)
        {
            while (index > 0 && comp( elems[index], elems[IndexOfParent(index)] ))
            {
                std::swap( elems[IndexOfParent(index)], elems[index] );
                index = IndexOfParent(index);
            }
        }

        void SiftDown(std::size_t index)
        {
            while (IndexOfRightChild(index) < elems.size())
            {
                T& minChild = const_cast<T&>(
                            std::min( elems[IndexOfLeftChild(index)],
                                      elems[IndexOfRightChild(index)],
                                      comp )
                            );

                if ( comp(minChild, elems[index]) )
                {
                    std::swap( minChild, elems[index] );
                    index = std::distance( &elems.front(), &minChild );
                }
                else
                {
                    break;
                }
            }

            if (IndexOfLeftChild(index) < elems.size())
            {
                if ( comp(elems[IndexOfLeftChild(index)], elems[index]) )
                {
                    std::swap( elems[IndexOfLeftChild(index)], elems[index] );
                }
            }
        }

        std::deque<T> elems;
        Comp comp;
    };


}
