Binary Heap (C++)
=================

## Example usage

### The heap interface

```c++
#include "binary_heap.h"
...
int main()
{
    /* Test heap-sort using heap. */
    heap::BinaryHeap<int> heap;

    for (int i = 0; i < 10; ++i)
    {
        heap.Insert(static_cast<int>( rand() % 100 ));
    }

    while (!heap.Empty())
    {
        std::cout << heap.Min() << ", ";
        heap.DeleteMin();
    }
    std::cout << "\n";
    ...
}
```

    Output: Integers in increasing order.

### Hooray! It supports custom comparators

```c++
/* This time use a max-heap. */
heap::BinaryHeap< int, std::greater<int> > maxHeap;

for (int i = 0; i < 10; ++i)
{
    maxHeap.Insert(static_cast<int>( rand() % 100 ));
}

while (!maxHeap.Empty())
{
    std::cout << maxHeap.Min() << ", ";
    maxHeap.DeleteMin();
}
std::cout << "\n";
```

    Output: Integers in decreasing order.

### Heap out of arbitrary sequence

_This works,_

```c++
/* Test the any-iterator constructor. */
int array[] = { 1, 36, 43, 45, 65, 66, 68, 77, 94, 85 };
heap::BinaryHeap<int> anotherHeap(array, array + 10);

while (!anotherHeap.Empty())
{
    std::cout << anotherHeap.Min() << ", ";
    anotherHeap.DeleteMin();
}
std::cout << "\n";
```

_This too,_

```c++
/* Test the any-iterator constructor. */
std::vector<int> vec = { ... }; // Or std::list, std::deque, std::forward_list
                                // Anything that supports forward-iterators will do
heap::BinaryHeap<int> anotherHeap(std::begin(vec), std::end(vec));
```

### What if you don't want a heap, just heap-sort?

_Without custom comparator,_

```c++
/* Test heap::HeapSort(). */
int array2[] = { 1, 36, 43, 45, 65, 66, 68, 77, 94, 85 };

heap::HeapSort(std::begin(array2), std::end(array2));
```

_With custom comparator,_

```c++
/* Test heap::HeapSort(). */
int array2[] = { 1, 36, 43, 45, 65, 66, 68, 77, 94, 85 };

heap::HeapSort(std::begin(array2), std::end(array2), std::less<int>());
```