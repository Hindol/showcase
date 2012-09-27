Binary Tree (C++)
=================

### Let's build a tree, :)

```c++
#include "binary_tree.h"

int main()
{
    using binary_tree::BinaryTree;
    using binary_tree::BinaryTreeNode;
    using binary_tree::MakeNode;

    BinaryTree<int> tree;
    tree.Root() = MakeNode<int>(5);

    BinaryTreeNode<int>* leftSubtree = tree.Root()->Left() = MakeNode<int>(3);
    BinaryTreeNode<int>* rightSubtree = tree.Root()->Right() = MakeNode<int>(7);

    leftSubtree->Left() = MakeNode<int>(2);
    leftSubtree->Right() = MakeNode<int>(4);
    rightSubtree->Left() = MakeNode<int>(6);

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