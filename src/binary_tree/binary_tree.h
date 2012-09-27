#pragma once


#include "bits/binary_tree_node.h"
#include "bits/binary_tree_iterator.h"
#include <type_traits>


namespace binary_tree {


template <class T>
class BinaryTree
{
public:
    typedef T                           value_type;
    typedef BinaryTreeNodeBase<T>       Node;

    typedef IteratorBase<Node>          Iterator;
    typedef PreOrderIteratorBase<Node>  PreOrderIterator;
    typedef InOrderIteratorBase<Node>   InOrderIterator;
    typedef PostOrderIteratorBase<Node> PostOrderIterator;

    typedef IteratorBase<Node const>          ConstIterator;
    typedef PreOrderIteratorBase<Node const>  ConstPreOrderIterator;
    typedef InOrderIteratorBase<Node const>   ConstInOrderIterator;
    typedef PostOrderIteratorBase<Node const> ConstPostOrderIterator;

    enum Order { PRE_ORDER, POST_ORDER, LEVEL_ORDER };

    BinaryTree()
        : root_(0L) {}

    explicit BinaryTree(Node* node)
        : root_(node) {}

    template <typename FwdItFirst, typename FwdItSecond>
    BinaryTree(FwdItFirst beginInOrder, FwdItFirst endInOrder,
        Order otherOrder, FwdItSecond beginOtherOrder, FwdItSecond endOtherOrder)
    {
        static_assert(
            std::is_same<value_type, typename std::iterator_traits<FwdItFirst>::value_type>::value,
            "Value types do not match."
            );

        static_assert(
            std::is_same<value_type, typename std::iterator_traits<FwdItSecond>::value_type>::value,
            "Value types do not match."
            );

        switch (otherOrder)
        {
        case PRE_ORDER:
            root_ = BuildTreeFromInOrderPreOrder(beginInOrder, endInOrder, beginOtherOrder, endOtherOrder);
            break;
        case POST_ORDER:
            break;
        case LEVEL_ORDER:
            break;
        default:
            break;
        }
    }

    ~BinaryTree()
    { if (root_ != 0L) delete root_; }

    Node*& Root()
    {
        return root_;
    }

    // Iterators
    // Pre-order
    ConstPreOrderIterator PreOrderBegin() const
    { return ConstPreOrderIterator(*this); }

    ConstPreOrderIterator PreOrderEnd() const
    { return ConstPreOrderIterator(); }

    PreOrderIterator PreOrderBegin()
    { return PreOrderIterator(*this); }

    PreOrderIterator PreOrderEnd()
    { return PreOrderIterator(); }

    // In-order
    ConstInOrderIterator InOrderBegin() const
    { return ConstInOrderIterator(*this); }

    ConstInOrderIterator InOrderEnd() const
    { return ConstInOrderIterator(); }

    InOrderIterator InOrderBegin()
    { return InOrderIterator(*this); }

    InOrderIterator InOrderEnd()
    { return InOrderIterator(); }

    // Post-order
    ConstPostOrderIterator PostOrderBegin() const
    { return ConstPostOrderIterator(*this); }

    ConstPostOrderIterator PostOrderEnd() const
    { return ConstPostOrderIterator(); }

    PostOrderIterator PostOrderBegin()
    { return PostOrderIterator(*this); }

    PostOrderIterator PostOrderEnd()
    { return PostOrderIterator(); }

private:
    template <typename FwdItFirst, typename FwdItSecond>
    Node* BuildTreeFromInOrderPreOrder(FwdItFirst beginInOrder, FwdItFirst endInOrder,
        FwdItSecond beginPreOrder, FwdItSecond endPreOrder)
    {
        if (beginInOrder != endInOrder)
        {
            Node* root = MakeNode(*beginPreOrder);
            FwdItFirst it = std::find(beginInOrder, endInOrder, *beginPreOrder);
            auto leftSize = std::distance(beginInOrder, it);

            if (beginInOrder != it)
            {
                root->Left() = BuildTreeFromInOrderPreOrder(
                    beginInOrder, it,
                    beginPreOrder + 1, beginPreOrder + 1 + leftSize
                    );
            }

            if (it + 1 != endInOrder)
            {
                root->Right() = BuildTreeFromInOrderPreOrder(
                    it + 1, endInOrder,
                    beginPreOrder + 1 + leftSize, endPreOrder
                    );
            }

            return root;
        }
        else
        {
            return 0L;
        }
    }

private:
    Node* root_;
};


} // binary_tree
