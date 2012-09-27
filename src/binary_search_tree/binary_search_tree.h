#pragma once


#include "bits/binary_search_tree_node.h"
#include "bits/binary_search_tree_iterator.h"


namespace tree {


template <typename T>
class BinarySearchTree
{
public:
    typedef T                                   value_type;
    typedef T&                                  reference;
    typedef const T&                            const_reference;
    typedef BSTNode<T>                          node_type;
    typedef BSTNode<T>&                         node_reference;
    typedef BSTNode<T>*                         node_pointer;
    typedef BSTIteratorBase<BSTNode<T> >        iterator;
    typedef BSTIteratorBase<const BSTNode<T> >  const_iterator;

    BinarySearchTree(void)
        : root_(0L) {}

    template <typename FwdIt>
    BinarySearchTree(FwdIt begin, FwdIt end)
        : root_(0L)
    {
        // TODO: FwdIt comcept check

        for (FwdIt it = begin; it != end; ++it)
        {
            Insert(*it);
        }
    }

    ~BinarySearchTree(void)
    { delete root_; /* Deleting the root frees up the whole tree */ }

    iterator Find(const_reference value)
    {
        if (root_ == 0L)
            return End();

        node_pointer ptr = root_;
        iterator it;
        while (true)
        {
            if (value < ptr->Value())
            {
                if (ptr->LeftPtr() != 0L)
                {
                    it.stack_.push(ptr);
                    ptr = ptr->LeftPtr();
                }
                else
                {
                    return End();
                }
            }
            else if (value > ptr->Value())
            {
                if (ptr->RightPtr() != 0L)
                {
                    ptr = ptr->RightPtr();
                }
                else
                {
                    return End();
                }
            }
            else
            {
                it.nodePtr_ = ptr;
                return it;
            }
        }
    }

    void Insert(const_reference value)
    {
        if (root_ == 0L)
        {
            root_ = new node_type(value);
            return;
        }

        node_pointer ptr = root_;
        while (true)
        {
            if (value < ptr->Value())
            {
                if (ptr->LeftPtr() != 0L)
                {
                    ptr = ptr->LeftPtr();
                }
                else
                {
                    ptr->LeftPtr() = new node_type(value);
                    return;
                }
            }
            else if (value > ptr->Value())
            {
                if (ptr->RightPtr() != 0L)
                {
                    ptr = ptr->RightPtr();
                }
                else
                {
                    ptr->RightPtr() = new node_type(value);
                    return;
                }
            }
            else
            {
                return; // No duplicates
            }
        }
    }

    void Remove(const_reference value)
    {
        if (root_ != 0L)
        {
            if (value > root_->Value())
            {
                root_->RightPtr() = Remove(root_->RightPtr(), value);
            }
            else if (value < root_->Value())
            {
                root_->LeftPtr() = Remove(root_->LeftPtr(), value);
            }
            else
            {
                root_ = Remove(root_, value);
            }
        }
        else
        {
            return;
        }
    }

    const_iterator CBegin() const
    { return const_iterator(*this); }

    const_iterator CEnd() const
    { return const_iterator(); }
    
    iterator Begin()
    { return iterator(*this); }

    iterator End()
    { return iterator(); }

private:
    template <class> friend class BSTIteratorBase;

    // Remove value (if found) from the sub-tree held by root and return
    // the possibly new root of the subtree.
    node_pointer Remove(node_pointer root, const_reference value)
    {
        if (root != 0L)
        {
            if (value > root->Value())
            {
                root->RightPtr() = Remove(root->RightPtr(), value);
                return root;
            }
            else if (value < root->Value())
            {
                root->LeftPtr() = Remove(root->LeftPtr(), value);
                return root;
            }
            else // We have found the element
            {
                if (root->LeftPtr() != 0L && root->RightPtr() != 0L)
                {
                    node_pointer parentOfLeftMax = root;
                    node_pointer leftMax = root->LeftPtr();
                    if (leftMax->RightPtr() != 0L)
                    {
                        while (leftMax->RightPtr() != 0L)
                        {
                            parentOfLeftMax = leftMax;
                            leftMax = leftMax->RightPtr();
                        }

                        parentOfLeftMax->RightPtr() = leftMax->LeftPtr();

                        // leftMax is now completely detached from tree except that
                        // it has a redundant LeftPtr().
                        leftMax->LeftPtr() = root->LeftPtr();
                        leftMax->RightPtr() = root->RightPtr();

                        root->LeftPtr() = 0L;
                        root->RightPtr() = 0L;
                        delete root;
                        return leftMax;
                    }
                    else // root->LeftPtr() == leftMax and leftMax has only LeftPtr()
                    {
                        leftMax->RightPtr() = root->RightPtr();
                        root->LeftPtr() = 0L;
                        delete root;
                        return leftMax;
                    }
                }
                else if (root->LeftPtr() != 0L)
                {
                    node_pointer newRoot = root->LeftPtr();
                    root->LeftPtr() = 0L;
                    delete root;
                    return newRoot;
                }
                else if (root->RightPtr() != 0L)
                {
                    node_pointer newRoot = root->RightPtr();
                    root->RightPtr() = 0L;
                    delete root;
                    return newRoot;
                }
                else
                {
                    delete root;
                    return 0L;
                }
            }
        }
        else
        {
            return 0L;
        }
    }

    /* Member variables. */
    node_pointer root_;
};


template <typename T>
std::ostream& operator <<(std::ostream& os, tree::BinarySearchTree<T>& bst)
{
    typedef typename tree::BinarySearchTree<T>::const_iterator const_iterator;
    for (const_iterator it = bst.CBegin(); it != bst.CEnd(); ++it)
    {
        os << *it << ", ";
    }
    return os;
}


} // tree

