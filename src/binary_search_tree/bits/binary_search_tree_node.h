#pragma once


namespace tree {


template <typename T>
class BSTNode
{
public:
    typedef T               value_type;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef BSTNode         node_type;
    typedef BSTNode*        node_pointer;
    typedef BSTNode*&       node_pointer_ref;

    BSTNode()
        : leftPtr_(0L), rightPtr_(0L) {}

    BSTNode(const_reference value)
        : value_(value), leftPtr_(0L), rightPtr_(0L) {}

    ~BSTNode()
    {
        // Deleting a 'root' node deletes the whole tree
        if (leftPtr_ != 0L) delete leftPtr_;
        if (rightPtr_ != 0L) delete rightPtr_;
    }

    reference Value()
    { return value_; }

    const_reference Value() const
    { return value_; }

    node_pointer_ref LeftPtr()
    { return leftPtr_; }

    node_pointer LeftPtr() const
    { return leftPtr_; }

    node_pointer_ref RightPtr()
    { return rightPtr_; }

    node_pointer RightPtr() const
    { return rightPtr_; }
    
private:
    T value_;
    node_pointer leftPtr_;
    node_pointer rightPtr_;
};


} // tree
