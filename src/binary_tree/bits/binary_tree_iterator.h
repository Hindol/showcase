#pragma once


#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <deque>
#include <iterator>


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
class BinaryTreeIteratorBase
{
    template <class> friend class BinaryTreeIteratorBase;

public:
    typedef typename ValueTypeOf<Node>::Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

protected:
    typedef Node node_type;
    typedef node_type* node_pointer;

    BinaryTreeIteratorBase()
        : nodePtr_(0L) {}

    explicit BinaryTreeIteratorBase(node_pointer node)
        : nodePtr_(node) {}

    ~BinaryTreeIteratorBase() // A protected destructor prevents deletion of derived class via base class ptr
    {}

private:
    struct enabler {};

public:
    template <class OtherNode>
    BinaryTreeIteratorBase(
        const BinaryTreeIteratorBase<OtherNode>& other,
        typename boost::enable_if<
            boost::is_convertible<OtherNode*,Node*>,
            enabler
        >::type = enabler()
        )
        : nodePtr_(other.nodePtr_)
    {
        std::copy(std::begin(other.stack_), std::end(other.stack_), std::begin(stack_));
    }

    template <class Tree>
    node_pointer GetRoot(Tree& tree)
    { return tree.root_; }

    template <class OtherNode>
    bool equal(const BinaryTreeIteratorBase<OtherNode>& other) const
    { return nodePtr_ == other.nodePtr_; }

    void increment()
    {}

    reference dereference() const
    { return nodePtr_->data_; }

protected:
    node_pointer nodePtr_;
    std::deque<node_pointer> stack_;
};


template <class Node>
class PreOrderIteratorBase : public BinaryTreeIteratorBase<Node>, public boost::iterator_facade<
        PreOrderIteratorBase<Node>,
        typename ValueTypeOf<Node>::Type,
        boost::forward_traversal_tag
    >
{
public:
    typedef typename ValueTypeOf<Node>::Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

private:
    typedef typename BinaryTreeIteratorBase<Node>::node_type node_type;
    typedef typename BinaryTreeIteratorBase<Node>::node_pointer node_pointer;

public:
    PreOrderIteratorBase()
    {}

    explicit PreOrderIteratorBase(node_pointer node)
        : BinaryTreeIteratorBase<Node>(node) {}

    template <class OtherNode>
    PreOrderIteratorBase(const PreOrderIteratorBase<OtherNode>& other)
        : BinaryTreeIteratorBase<Node>(other) {}

    template <class Tree>
    explicit PreOrderIteratorBase(Tree& tree)
    { nodePtr_ = this->GetRoot(tree); }

private:
    friend class boost::iterator_core_access;

    using BinaryTreeIteratorBase<Node>::nodePtr_;
    using BinaryTreeIteratorBase<Node>::stack_;

    void increment()
    {
        if (nodePtr_->leftPtr_ != 0L)
        {
            stack_.push_back(nodePtr_);
            nodePtr_ = nodePtr_->leftPtr_;
        }
        else
        {
            if (nodePtr_->rightPtr_ != 0L)
            {
                nodePtr_ = nodePtr_->rightPtr_;
            }
            else
            {
                if (!stack_.empty())
                {
                    nodePtr_ = stack_.back()->rightPtr_;
                    stack_.pop_back();
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
class InOrderIteratorBase : public BinaryTreeIteratorBase<Node>, public boost::iterator_facade<
        InOrderIteratorBase<Node>,
        typename ValueTypeOf<Node>::Type,
        boost::forward_traversal_tag
    >
{
public:
    typedef typename ValueTypeOf<Node>::Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

private:
    typedef typename BinaryTreeIteratorBase<Node>::node_type node_type;
    typedef typename BinaryTreeIteratorBase<Node>::node_pointer node_pointer;

public:
    InOrderIteratorBase()
    {}

    explicit InOrderIteratorBase(node_pointer node)
        : BinaryTreeIteratorBase<Node>(node) {}

    template <class OtherNode>
    InOrderIteratorBase(const InOrderIteratorBase<OtherNode>& other)
        : BinaryTreeIteratorBase<Node>(other) {}

    template <class Tree>
    explicit InOrderIteratorBase(Tree& tree)
    {
        nodePtr_ = this->GetRoot(tree);
        while (nodePtr_->leftPtr_ != 0L)
        {
            stack_.push_back(nodePtr_);
            nodePtr_ = nodePtr_->leftPtr_;
        }
    }

private:
    friend class boost::iterator_core_access;

    using BinaryTreeIteratorBase<Node>::nodePtr_;
    using BinaryTreeIteratorBase<Node>::stack_;

    void increment()
    {
        if (nodePtr_->rightPtr_ != 0L)
        {
            nodePtr_ = nodePtr_->rightPtr_;

            while (nodePtr_->leftPtr_ != 0L)
            {
                stack_.push_back(nodePtr_);
                nodePtr_ = nodePtr_->leftPtr_;
            }
        }
        else if (!stack_.empty())
        {
            nodePtr_ = stack_.back();
            stack_.pop_back();
        }
        else
        {
            nodePtr_ = 0L;
        }
    }

    reference dereference() const
    {
        return nodePtr_->data_;
    }
};


template <class Node>
class PostOrderIteratorBase : public BinaryTreeIteratorBase<Node>, public boost::iterator_facade<
        PostOrderIteratorBase<Node>,
        typename ValueTypeOf<Node>::Type,
        boost::forward_traversal_tag
    >
{
public:
    typedef typename ValueTypeOf<Node>::Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

private:
    typedef typename BinaryTreeIteratorBase<Node>::node_type node_type;
    typedef typename BinaryTreeIteratorBase<Node>::node_pointer node_pointer;

public:
    PostOrderIteratorBase()
    {}

    explicit PostOrderIteratorBase(node_pointer node)
        : BinaryTreeIteratorBase<Node>(node) {}

    template <class Tree>
    explicit PostOrderIteratorBase(Tree& tree)
    {
        nodePtr_ = this->GetRoot(tree);

        while (nodePtr_->leftPtr_ != 0L)
        {
            stack_.push_back(nodePtr_);
            nodePtr_ = nodePtr_->leftPtr_;
        }

        while (nodePtr_->rightPtr_ != 0L)
        {
            stack_.push_back(nodePtr_);
            nodePtr_ = nodePtr_->rightPtr_;
        }
    }

private:
    friend class boost::iterator_core_access;

    using BinaryTreeIteratorBase<Node>::nodePtr_;
    using BinaryTreeIteratorBase<Node>::stack_;

    void increment()
    {
        if (!stack_.empty())
        {
            if (stack_.back()->rightPtr_ != 0L && stack_.back()->rightPtr_ != nodePtr_)
            {
                nodePtr_ = stack_.back()->rightPtr_;
                while (true)
                {
                    if (nodePtr_->leftPtr_ != 0L)
                    {
                        stack_.push_back(nodePtr_);
                        nodePtr_ = nodePtr_->leftPtr_;
                    }
                    else if (nodePtr_->rightPtr_ != 0L)
                    {
                        stack_.push_back(nodePtr_);
                        nodePtr_ = nodePtr_->rightPtr_;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                nodePtr_ = stack_.back();
                stack_.pop_back();
            }
        }
        else
        {
            nodePtr_ = 0L;
        }
    }
};


} // binary_tree
