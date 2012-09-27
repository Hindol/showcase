#pragma once


#include "binary_search_tree_node.h"
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility/enable_if.hpp>
#include <stack>


namespace tree {


template <typename T>
class BinarySearchTree; // Forward declaration


template<class T>
struct ValueTypeOf
{
    typedef typename T::value_type type;
};

template<class T>
struct ValueTypeOf<T const>
{
    typedef typename T::value_type const type;
};


template <typename Node>
class BSTIteratorBase : public boost::iterator_facade<
    BSTIteratorBase<Node>,
    typename ValueTypeOf<Node>::type,
    boost::forward_traversal_tag
>
{
private:
    struct enabler {};

public:
    typedef Node*                               node_pointer;
    typedef typename ValueTypeOf<Node>::type    value_type;

    BSTIteratorBase()
        : nodePtr_(0L) {}

    BSTIteratorBase(node_pointer ptr)
        : nodePtr_(ptr) {}

    template <typename OtherValue>
    BSTIteratorBase(const BinarySearchTree<OtherValue>& bst)
    {
        nodePtr_ = bst.root_;
        if (nodePtr_ != 0L)
        {
            while (nodePtr_->LeftPtr() != 0L)
            {
                stack_.push(nodePtr_);
                nodePtr_ = nodePtr_->LeftPtr();
            }
        }
    }

    // When coupled with enabler(), allows one-way conversion from
    // iterator to const_iterator, boost magic!
    template <class OtherNode>
    BSTIteratorBase(
        const BSTIteratorBase<OtherNode>& other,
        typename boost::enable_if<
            boost::is_convertible<OtherNode*,Node*>,
            enabler
            >::type = enabler()
        )
        : nodePtr_(other.nodePtr_) {}

private:
    friend class boost::iterator_core_access;
    template <class> friend class BSTIteratorBase;

    // A templated equal() allows comparison of iterator and const_iterator types
    template <class OtherNode>
    bool equal(const BSTIteratorBase<OtherNode>& other) const
    { return nodePtr_ == other.nodePtr_; }

    void increment()
    {
        if (nodePtr_->RightPtr() != 0L)
        {
            nodePtr_ = nodePtr_->RightPtr();

            while (nodePtr_->LeftPtr() != 0L)
            {
                stack_.push(nodePtr_);
                nodePtr_ = nodePtr_->LeftPtr();
            }
        }
        else if (!stack_.empty())
        {
            nodePtr_ = stack_.top();
            stack_.pop();
        }
        else
        {
            nodePtr_ = 0L;
        }
    }

    value_type& dereference() const
    { return nodePtr_->Value(); }

    /* Member variables. */
    node_pointer nodePtr_;
    std::stack<node_pointer> stack_;
};


} // tree
