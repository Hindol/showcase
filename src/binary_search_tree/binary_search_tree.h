#pragma once


#include <binary_tree/binary_tree.h>


namespace binary_tree {


template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public:
    typedef T ValueType;

    typedef typename BinaryTree<ValueType>::Reference Reference;
    typedef typename BinaryTree<ValueType>::ConstReference ConstReference;

    typedef typename BinaryTree<ValueType>::Pointer Pointer;
    typedef typename BinaryTree<ValueType>::ConstPointer ConstPointer;

    typedef typename BinaryTree<ValueType>::PreOrderIterator PreOrderIterator;
    typedef typename BinaryTree<ValueType>::ConstPreOrderIterator ConstPreOrderIterator;

    typedef typename BinaryTree<ValueType>::InOrderIterator InOrderIterator;
    typedef typename BinaryTree<ValueType>::ConstInOrderIterator ConstInOrderIterator;

    typedef typename BinaryTree<ValueType>::PostOrderIterator PostOrderIterator;
    typedef typename BinaryTree<ValueType>::ConstPostOrderIterator ConstPostOrderIterator;

private:
    typedef typename BinaryTree<ValueType>::Node Node;
    typedef typename BinaryTree<ValueType>::NodePointer NodePointer;

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
            root_ = new Node(value);
            return;
        }

        NodePointer ptr = root_;
        while (true)
        {
            if (value < ptr->data_)
            {
                if (ptr->leftPtr_ != 0L)
                {
                    ptr = ptr->leftPtr_;
                }
                else
                {
                    ptr->leftPtr_ = new Node(value);
                    return;
                }
            }
            else if (value > ptr->data_)
            {
                if (ptr->rightPtr_ != 0L)
                {
                    ptr = ptr->rightPtr_;
                }
                else
                {
                    ptr->rightPtr_ = new Node(value);
                    return;
                }
            }
            else
            {
                return; // No duplicates
            }
        }
    }

    /**
     * @brief           Remove value (if found) from the tree
     * @param[in] value The value to remove
     */
    void Remove(ConstReference value)
    {
        if (root_ != 0L)
        {
            if (value > root_->data_)
            {
                root_->rightPtr_ = Remove(root_->rightPtr_, value);
            }
            else if (value < root_->data_)
            {
                root_->leftPtr_ = Remove(root_->leftPtr_, value);
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
    /**
     * @brief           Find a value (if exists), by starting at the root and going down the tree.
     * @param[in] value The value to search for.
     * @return          An in-order iterator pointing to the value (if found) OR InOrderEnd().
     */
    InOrderIterator Find(ConstReference value)
    {
        if (root_ == 0L)
            return this->InOrderEnd();

        NodePointer ptr = root_;
        InOrderIterator it;
        while (true)
        {
            if (value < ptr->data_)
            {
                if (ptr->leftPtr_ != 0L)
                {
                    it.stack_.push(ptr);
                    ptr = ptr->leftPtr_;
                }
                else
                {
                    return this->InOrderEnd();
                }
            }
            else if (value > ptr->data_)
            {
                if (ptr->rightPtr_ != 0L)
                {
                    ptr = ptr->rightPtr_;
                }
                else
                {
                    return this->InOrderEnd();
                }
            }
            else
            {
                it.nodePtr_ = ptr;
                return it;
            }
        }
    }

    /**
     * @brief           Remove value (if found) from the sub-tree held by root
     * @param[in] root  Root of the sub-tree
     * @param[in] value The value to remove
     * @return          New root of the subtree after removal
     */
    NodePointer Remove(NodePointer root, ConstReference value)
    {
        if (root != 0L)
        {
            if (value > root->data_)
            {
                root->rightPtr_ = Remove(root->rightPtr_, value);
                return root;
            }
            else if (value < root->data_)
            {
                root->leftPtr_ = Remove(root->leftPtr_, value);
                return root;
            }
            else // We have found the element
            {
                if (root->leftPtr_ != 0L && root->rightPtr_ != 0L)
                {
                    NodePointer parentOfLeftMax = root;
                    NodePointer leftMax = root->leftPtr_;
                    if (leftMax->rightPtr_ != 0L)
                    {
                        while (leftMax->rightPtr_ != 0L)
                        {
                            parentOfLeftMax = leftMax;
                            leftMax = leftMax->rightPtr_;
                        }

                        parentOfLeftMax->rightPtr_ = leftMax->leftPtr_;

                        // leftMax is now completely detached from tree except that
                        // it has a redundant leftPtr_.
                        leftMax->leftPtr_ = root->leftPtr_;
                        leftMax->rightPtr_ = root->rightPtr_;

                        root->leftPtr_ = 0L;
                        root->rightPtr_ = 0L;
                        delete root;
                        return leftMax;
                    }
                    else // root->leftPtr_ == leftMax and leftMax has only leftPtr_
                    {
                        leftMax->rightPtr_ = root->rightPtr_;
                        root->leftPtr_ = 0L;
                        delete root;
                        return leftMax;
                    }
                }
                else if (root->leftPtr_ != 0L)
                {
                    NodePointer newRoot = root->leftPtr_;
                    root->leftPtr_ = 0L;
                    delete root;
                    return newRoot;
                }
                else if (root->rightPtr_ != 0L)
                {
                    NodePointer newRoot = root->rightPtr_;
                    root->rightPtr_ = 0L;
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
    for (auto it = bst.InOrderBegin(); it != bst.InOrderEnd(); ++it)
    {
        os << *it << ", ";
    }
    return os;
}


} // binary_tree
