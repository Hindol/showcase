Binary Tree (C++)
=================

### Let's build a tree, :)

## Using in-order and pre-order traversal

```c++
#include "binary_tree.h"

int main()
{
    using binary_tree::BinaryTree;

    int inOrderTraversal[] = { 8, 9, 2, 4, 11, 13, 5 };
    int preOrderTraversal[] = { 4, 9, 8, 2, 5, 11, 13 };
    int postOrderTraversal[] = { 8, 2, 9, 13, 11, 5, 4 };

    binary_tree::BinaryTree<int> tree(
        std::begin(inOrderTraversal), std::end(inOrderTraversal),
        binary_tree::BinaryTree<int>::PRE_ORDER, std::begin(preOrderTraversal), std::end(preOrderTraversal)
        );

    ...

    return 0;
}
```

## Using in-order and post-order traversal

```c++
#include "binary_tree.h"

int main()
{
    using binary_tree::BinaryTree;

    int inOrderTraversal[] = { 8, 9, 2, 4, 11, 13, 5 };
    int preOrderTraversal[] = { 4, 9, 8, 2, 5, 11, 13 };
    int postOrderTraversal[] = { 8, 2, 9, 13, 11, 5, 4 };

    binary_tree::BinaryTree<int> tree(
        std::begin(inOrderTraversal), std::end(inOrderTraversal),
        binary_tree::BinaryTree<int>::POST_ORDER, std::begin(postOrderTraversal), std::end(postOrderTraversal)
        );

    ...

    return 0;
}
```

### Start monkeying around...

```c++
BinaryTree<int>::PreOrderIterator it = tree.PreOrderBegin();
for (; it != tree.PreOrderEnd(); ++it)
{
    std::cout << it->Data() << ", ";
}
std::cout << "\n";
```

```c++
BinaryTree<int>::InOrderIterator it = tree.InOrderBegin();
```

```c++
BinaryTree<int>::PostOrderIterator it = tree.PostOrderBegin();
```

### Impressive, huh?

If you still find it lacking, just submit a bug report. I'll be right on it, :)