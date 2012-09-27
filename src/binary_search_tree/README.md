Binary Search Tree (C++)
========================

### Initialize

Start from the very beginning,

```c++
#include "binary_search_tree.h"

int main()
{
    using namespace tree;

    BinarySearchTree<int> bst; // An empty binary tree
    bst.Insert(5);
    bst.Insert(9);
    bst.Insert(1);
    bst.Insert(5); // No-op! 5 already exists
    ...
}
```

If you have the elements at hand,

```c++
BinarySearchTree<int> bst(array, array + arraySize);
```

```c++
BinarySearchTree<int> bst(vec.cbegin(), vec.cend());
```

### Remove an element

```c++
bst.Remove(9); // Results in no-op if element is not in tree
```

### Print the elements

```c++
typedef typename BinarySearchTree<T>::const_iterator const_iterator;
for (const_iterator it = bst.CBegin(); it != bst.CEnd(); ++it)
{
    std::cout << *it << ", ";
}
```

Or better yet, use the `ostream& operator <<()` provided,

```c++
std::cout << bst << "\n";
```