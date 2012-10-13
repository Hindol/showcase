#pragma once


#include <binary_search_tree/binary_search_tree.h>


namespace binary_tree {


template <class T>
class AVLTree : public BinarySearchTree<T>
{
public:
    typedef T ValueType;

    typedef typename BinarySearchTree<ValueType>::Reference Reference;
    typedef typename BinarySearchTree<ValueType>::ConstReference ConstReference;

    typedef typename BinarySearchTree<ValueType>::Pointer Pointer;
    typedef typename BinarySearchTree<ValueType>::ConstPointer ConstPointer;

    typedef typename BinarySearchTree<ValueType>::PreOrderIterator PreOrderIterator;
    typedef typename BinarySearchTree<ValueType>::ConstPreOrderIterator ConstPreOrderIterator;

    typedef typename BinarySearchTree<ValueType>::InOrderIterator InOrderIterator;
    typedef typename BinarySearchTree<ValueType>::ConstInOrderIterator ConstInOrderIterator;

    typedef typename BinarySearchTree<ValueType>::PostOrderIterator PostOrderIterator;
    typedef typename BinarySearchTree<ValueType>::ConstPostOrderIterator ConstPostOrderIterator;

private:
    typedef typename BinarySearchTree<ValueType>::Node Node;
    typedef typename BinarySearchTree<ValueType>::NodePointer NodePointer;
};


} // binary_tree
