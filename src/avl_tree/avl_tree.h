#pragma once


#include <binary_search_tree/binary_search_tree.h>


namespace binary_tree {


template <typename T>
class AVLTree : public BinarySearchTree<T>
{
private:
    class AVLTreeNode : public BinarySearchTree<T>::BinaryTreeNodeBase
    {
    public:
    };
};


} // binary_tree
