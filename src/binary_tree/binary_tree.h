#pragma once


#include "bits/binary_tree_node.h"
#include "bits/binary_tree_iterator.h"


namespace binary_tree {


template <class T>
class BinaryTree
{
public:
    typedef BinaryTreeNodeBase<T>       Node;

    typedef IteratorBase<Node>          Iterator;
    typedef PreOrderIteratorBase<Node>  PreOrderIterator;
    typedef InOrderIteratorBase<Node>   InOrderIterator;
    typedef PostOrderIteratorBase<Node> PostOrderIterator;

    typedef IteratorBase<Node const>          ConstIterator;
    typedef PreOrderIteratorBase<Node const>  ConstPreOrderIterator;
    typedef InOrderIteratorBase<Node const>   ConstInOrderIterator;
    typedef PostOrderIteratorBase<Node const> ConstPostOrderIterator;

    BinaryTree()
        : root_(0L) {}

    explicit BinaryTree(Node* node)
        : root_(node) {}

    ~BinaryTree()
    { if (root_ != 0L) delete root_; }

    Node*& Root()
    {
        return root_;
    }

    PreOrderIterator PreOrderBegin()
    { return PreOrderIterator(*this); }

    PreOrderIterator PreOrderEnd()
    { return PreOrderIterator(); }

    InOrderIterator InOrderBegin()
    { return InOrderIterator(*this); }

    InOrderIterator InOrderEnd()
    { return InOrderIterator(); }

    PostOrderIterator PostOrderBegin()
    { return PostOrderIterator(*this); }

    PostOrderIterator PostOrderEnd()
    { return PostOrderIterator(); }

private:
    Node* root_;
};


} // binary_tree
