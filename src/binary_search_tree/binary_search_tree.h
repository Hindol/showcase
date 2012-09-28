#pragma once


#include <binary_tree/binary_tree.h>


namespace binary_tree {


template <typename ValueType>
class BinarySearchTree : public BinaryTree<ValueType>
{
public:
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

    void Insert(ConstReference value)
    {
        if (root_ == 0L)
        {
            root_ = new node_type(value);
            return;
        }

        NodePointer ptr = root_;
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

    void Remove(ConstReference value)
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

private:
    template <class> friend class BSTIteratorBase;

    Iterator Find(ConstReference value)
    {
        if (root_ == 0L)
            return End();

        NodePointer ptr = root_;
        Iterator it;
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

    // Remove value (if found) from the sub-tree held by root and return
    // the possibly new root of the subtree.
    NodePointer Remove(NodePointer root, ConstReference value)
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
                    NodePointer parentOfLeftMax = root;
                    NodePointer leftMax = root->LeftPtr();
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
                    NodePointer newRoot = root->LeftPtr();
                    root->LeftPtr() = 0L;
                    delete root;
                    return newRoot;
                }
                else if (root->RightPtr() != 0L)
                {
                    NodePointer newRoot = root->RightPtr();
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
    NodePointer root_;
};


template <typename T>
std::ostream& operator <<(std::ostream& os, const BinarySearchTree<T>& bst)
{
    BinarySearchTree<T>::ConstInOrderIterator it;
    for (it = bst.InOrderBegin(); it != bst.InOrderBegin(); ++it)
    {
        os << *it << ", ";
    }
    return os;
}


} // binary_tree

