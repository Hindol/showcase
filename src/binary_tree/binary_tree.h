#pragma once


#include "bits/binary_tree_iterator.h"
#include <type_traits>


namespace binary_tree {


enum TraversalOrder { PRE_ORDER, POST_ORDER, LEVEL_ORDER };


template <class ValueType>
class BinaryTree
{
    template <typename> friend class BinaryTreeIteratorBase;
private:
    struct BinaryTreeNodeBase
    {
        typedef typename BinaryTree::ValueType ValueType;

        BinaryTreeNodeBase()
            : left_(0L), right_(0L) {}

        BinaryTreeNodeBase(const ValueType& data)
            : left_(0L), right_(0L), data_(data) {}

        ~BinaryTreeNodeBase()
        {
            if (left_ != 0L) delete left_;
            if (right_ != 0L) delete right_;
        }

        ValueType data_;
        BinaryTreeNodeBase* left_;
        BinaryTreeNodeBase* right_;
    };

public:
    typedef ValueType                          ValueType;
    typedef ValueType&                         Reference;
    typedef const ValueType&                   ConstReference;

protected:
    typedef BinaryTreeNodeBase                 Node;
    typedef BinaryTreeNodeBase*                NodePointer;

public:
    typedef BinaryTreeIteratorBase<Node>       Iterator;
    typedef BinaryTreeIteratorBase<Node const> ConstIterator;

    typedef PreOrderIteratorBase<Node>         PreOrderIterator;
    typedef PreOrderIteratorBase<Node const>   ConstPreOrderIterator;
    
    typedef InOrderIteratorBase<Node>          InOrderIterator;
    typedef InOrderIteratorBase<Node const>    ConstInOrderIterator;
    
    typedef PostOrderIteratorBase<Node>        PostOrderIterator;
    typedef PostOrderIteratorBase<Node const>  ConstPostOrderIterator;

    BinaryTree()
        : root_(0L) {}

    explicit BinaryTree(Node* node)
        : root_(node) {}

    template <typename FwdItFirst, typename FwdItSecond>
    BinaryTree(FwdItFirst beginInOrder, FwdItFirst endInOrder,
        TraversalOrder otherOrder, FwdItSecond beginOtherOrder, FwdItSecond endOtherOrder)
    {
        static_assert(
            std::is_same<ValueType, typename std::iterator_traits<FwdItFirst>::value_type>::value,
            "Value types do not match."
            );

        static_assert(
            std::is_same<ValueType, typename std::iterator_traits<FwdItSecond>::value_type>::value,
            "Value types do not match."
            );

        switch (otherOrder)
        {
        case PRE_ORDER:
            root_ = BuildTreeFromInOrderPreOrder(beginInOrder, endInOrder, beginOtherOrder, endOtherOrder);
            break;
        case POST_ORDER:
            root_ = BuildTreeFromInOrderPostOrder(beginInOrder, endInOrder, beginOtherOrder, endOtherOrder);
            break;
        case LEVEL_ORDER:
            // Not yet supported
            break;
        default:
            break;
        }
    }

    ~BinaryTree()
    { if (root_ != 0L) delete root_; }

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
    NodePointer MakeNode(const ValueType& data)
    {
        return new BinaryTreeNodeBase(data);
    }

    template <typename FwdItFirst, typename FwdItSecond>
    NodePointer BuildTreeFromInOrderPreOrder(FwdItFirst beginInOrder, FwdItFirst endInOrder,
        FwdItSecond beginPreOrder, FwdItSecond endPreOrder)
    {
        if (beginInOrder != endInOrder)
        {
            Node* root = MakeNode(*beginPreOrder);
            FwdItFirst it = std::find(beginInOrder, endInOrder, root->data_);
            auto leftSubtreeSize = std::distance(beginInOrder, it);

            if (beginInOrder != it)
            {
                root->left_ = BuildTreeFromInOrderPreOrder(
                    beginInOrder, it,
                    beginPreOrder + 1, beginPreOrder + 1 + leftSubtreeSize
                    );
            }

            if (it + 1 != endInOrder)
            {
                root->right_ = BuildTreeFromInOrderPreOrder(
                    it + 1, endInOrder,
                    beginPreOrder + 1 + leftSubtreeSize, endPreOrder
                    );
            }

            return root;
        }
        else
        {
            return 0L;
        }
    }

    template <typename FwdItFirst, typename FwdItSecond>
    NodePointer BuildTreeFromInOrderPostOrder(FwdItFirst beginInOrder, FwdItFirst endInOrder,
        FwdItSecond beginPostOrder, FwdItSecond endPostOrder)
    {
        if (beginInOrder != endInOrder)
        {
            Node* root = MakeNode(*(endPostOrder - 1));
            FwdItFirst it = std::find(beginInOrder, endInOrder, root->data_);
            auto leftSubtreeSize = std::distance(beginInOrder, it);

            if (leftSubtreeSize > 0) // If root has left subtree
            {
                root->left_ = BuildTreeFromInOrderPostOrder(
                    beginInOrder, it,
                    beginPostOrder, beginPostOrder + leftSubtreeSize
                    );
            }

            if (it + 1 != endInOrder) // If root has right subtree
            {
                root->right_ = BuildTreeFromInOrderPostOrder(
                    it + 1, endInOrder,
                    beginPostOrder + leftSubtreeSize, endPostOrder - 1
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
    NodePointer root_;
};


} // binary_tree
