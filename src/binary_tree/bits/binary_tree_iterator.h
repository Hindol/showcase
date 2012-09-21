#pragma once


#include "binary_tree_node.h"
#include <boost/iterator/iterator_facade.hpp>
#include <stack>


namespace binary_tree {


template <class Node>
class IteratorBase : public boost::iterator_facade<
    IteratorBase<Node>,
    Node,
    boost::forward_traversal_tag
>
{
protected:
    IteratorBase()
        : nodePtr_(0L) {}

    explicit IteratorBase(Node* node)
        : nodePtr_(node) {}

    ~IteratorBase() // A protected destructor prevents deletion of derived class via base class ptr
    {}

    friend class boost::iterator_core_access;

    bool equal(const IteratorBase& other) const
    { return nodePtr_ == other.nodePtr_; }

    virtual void increment()
    {}

    Node& dereference() const
    { return *nodePtr_; }

    Node* nodePtr_;
    std::stack<Node*> stack_;
};


template <class Node>
class PreOrderIteratorBase : public IteratorBase<Node>
{
public:
    PreOrderIteratorBase()
    {}

    explicit PreOrderIteratorBase(Node* node)
        : IteratorBase<Node>(node) {}

    template <class Tree>
    explicit PreOrderIteratorBase(Tree& tree)
    { nodePtr_ = tree.Root(); }

private:
    using IteratorBase<Node>::nodePtr_;
    using IteratorBase<Node>::stack_;

    void increment()
    {
        if (nodePtr_->Left() != 0L)
        {
            stack_.push(nodePtr_);
            nodePtr_ = nodePtr_->Left();
        }
        else
        {
            if (nodePtr_->Right() != 0L)
            {
                nodePtr_ = nodePtr_->Right();
            }
            else
            {
                if (!stack_.empty())
                {
                    nodePtr_ = stack_.top()->Right();
                    stack_.pop();
                }
                else
                {
                    nodePtr_ = 0L;
                }
            }
        }
    }
};


template <class Node>
class InOrderIteratorBase : public IteratorBase<Node>
{
public:
    InOrderIteratorBase()
    {}

    explicit InOrderIteratorBase(Node* node)
        : IteratorBase<Node>(node) {}

    template <class Tree>
    explicit InOrderIteratorBase(Tree& tree)
    {
        nodePtr_ = tree.Root();
        while (nodePtr_->Left() != 0L)
        {
            stack_.push(nodePtr_);
            nodePtr_ = nodePtr_->Left();
        }
    }

private:
    using IteratorBase<Node>::nodePtr_;
    using IteratorBase<Node>::stack_;

    void increment()
    {
        if (nodePtr_->Right() != 0L)
        {
            nodePtr_ = nodePtr_->Right();

            while (nodePtr_->Left() != 0L)
            {
                stack_.push(nodePtr_);
                nodePtr_ = nodePtr_->Left();
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
};


template <class Node>
class PostOrderIteratorBase : public IteratorBase<Node>
{
public:
    PostOrderIteratorBase()
    {}

    explicit PostOrderIteratorBase(Node* node)
        : IteratorBase<Node>(node) {}

    template <class Tree>
    explicit PostOrderIteratorBase(Tree& tree)
    {
        nodePtr_ = tree.Root();

        while (nodePtr_->Left() != 0L)
        {
            stack_.push(nodePtr_);
            nodePtr_ = nodePtr_->Left();
        }

        while (nodePtr_->Right() != 0L)
        {
            stack_.push(nodePtr_);
            nodePtr_ = nodePtr_->Right();
        }
    }

private:
    using IteratorBase<Node>::nodePtr_;
    using IteratorBase<Node>::stack_;

    void increment()
    {
        if (!stack_.empty())
        {
            if (stack_.top()->Right() != 0L && stack_.top()->Right() != nodePtr_)
            {
                nodePtr_ = stack_.top()->Right();
                while (nodePtr_->Left() != 0L)
                {
                    stack_.push(nodePtr_);
                    nodePtr_ = nodePtr_->Left();
                }
            }
            else
            {
                nodePtr_ = stack_.top();
                stack_.pop();
            }
        }
        else
        {
            nodePtr_ = 0L;
        }
    }
};


} // binary_tree
