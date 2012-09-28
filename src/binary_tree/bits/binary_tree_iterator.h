#pragma once


#include <boost/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <stack>


namespace binary_tree {


// Meta-functions that help deduce the type of a node's value
template<class T>
struct ValueTypeOf
{
    typedef typename T::ValueType Type;
};

template<class T>
struct ValueTypeOf<T const>
{
    typedef typename T::ValueType const Type;
};


template <class Node>
class BinaryTreeIteratorBase : public boost::iterator_facade<
    BinaryTreeIteratorBase<Node>,
    typename ValueTypeOf<Node>::Type,
    boost::forward_traversal_tag
>
{
public:
    typedef typename ValueTypeOf<Node>::Type ValueType;
    typedef ValueType& Reference;
    typedef const ValueType& ConstReference;

protected:
    typedef Node* NodePointer;

    BinaryTreeIteratorBase()
        : nodePtr_(0L) {}

    explicit BinaryTreeIteratorBase(NodePointer node)
        : nodePtr_(node) {}

    ~BinaryTreeIteratorBase() // A protected destructor prevents deletion of derived class via base class ptr
    {}

private:
    struct enabler {};

protected:
    template <class OtherNode>
    BinaryTreeIteratorBase(
        const BinaryTreeIteratorBase<OtherNode>& other,
        typename boost::enable_if<
            boost::is_convertible<OtherNode*,Node*>,
            enabler
        >::type = enabler()
        )
        : nodePtr_(other.nodePtr_), stack_(other.stack_) {}

    template <class Tree>
    NodePointer GetRoot(Tree& tree)
    { return tree.root_; }

private:
    friend class boost::iterator_core_access;

    bool equal(const BinaryTreeIteratorBase& other) const
    { return nodePtr_ == other.nodePtr_; }

    void increment()
    {}

    Reference dereference() const
    { return nodePtr_->data_; }

protected:
    NodePointer nodePtr_;
    std::stack<NodePointer> stack_;
};


template <class Node>
class PreOrderIteratorBase : public BinaryTreeIteratorBase<Node>
{
public:
    PreOrderIteratorBase()
    {}

    explicit PreOrderIteratorBase(NodePointer node)
        : BinaryTreeIteratorBase<Node>(node) {}

    template <class Tree>
    explicit PreOrderIteratorBase(Tree& tree)
    { nodePtr_ = GetRoot(tree); }

private:
    using BinaryTreeIteratorBase<Node>::nodePtr_;
    using BinaryTreeIteratorBase<Node>::stack_;

    void increment()
    {
        if (nodePtr_->left_ != 0L)
        {
            stack_.push(nodePtr_);
            nodePtr_ = nodePtr_->left_;
        }
        else
        {
            if (nodePtr_->right_ != 0L)
            {
                nodePtr_ = nodePtr_->right_;
            }
            else
            {
                if (!stack_.empty())
                {
                    nodePtr_ = stack_.top()->right_;
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
class InOrderIteratorBase : public BinaryTreeIteratorBase<Node>
{
    template <class> friend class BinaryTreeIteratorBase;

public:
    InOrderIteratorBase()
    {}

    explicit InOrderIteratorBase(NodePointer node)
        : BinaryTreeIteratorBase<Node>(node) {}

    template <class Tree>
    explicit InOrderIteratorBase(Tree& tree)
    {
        nodePtr_ = GetRoot(tree);
        while (nodePtr_->left_ != 0L)
        {
            stack_.push(nodePtr_);
            nodePtr_ = nodePtr_->left_;
        }
    }

private:
    using BinaryTreeIteratorBase<Node>::nodePtr_;
    using BinaryTreeIteratorBase<Node>::stack_;

    void increment()
    {
        if (nodePtr_->right_ != 0L)
        {
            nodePtr_ = nodePtr_->right_;

            while (nodePtr_->left_ != 0L)
            {
                stack_.push(nodePtr_);
                nodePtr_ = nodePtr_->left_;
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
class PostOrderIteratorBase : public BinaryTreeIteratorBase<Node>
{
public:
    PostOrderIteratorBase()
    {}

    explicit PostOrderIteratorBase(NodePointer node)
        : BinaryTreeIteratorBase<Node>(node) {}

    template <class Tree>
    explicit PostOrderIteratorBase(Tree& tree)
    {
        nodePtr_ = GetRoot(tree);

        while (nodePtr_->left_ != 0L)
        {
            stack_.push(nodePtr_);
            nodePtr_ = nodePtr_->left_;
        }

        while (nodePtr_->right_ != 0L)
        {
            stack_.push(nodePtr_);
            nodePtr_ = nodePtr_->right_;
        }
    }

private:
    using BinaryTreeIteratorBase<Node>::nodePtr_;
    using BinaryTreeIteratorBase<Node>::stack_;

    void increment()
    {
        if (!stack_.empty())
        {
            if (stack_.top()->right_ != 0L && stack_.top()->right_ != nodePtr_)
            {
                nodePtr_ = stack_.top()->right_;
                while (true)
                {
                    if (nodePtr_->left_ != 0L)
                    {
                        stack_.push(nodePtr_);
                        nodePtr_ = nodePtr_->left_;
                    }
                    else if (nodePtr_->right_ != 0L)
                    {
                        stack_.push(nodePtr_);
                        nodePtr_ = nodePtr_->right_;
                    }
                    else
                    {
                        break;
                    }
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
