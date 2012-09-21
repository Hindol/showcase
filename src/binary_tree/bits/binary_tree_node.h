#pragma once


namespace binary_tree {


template <class T>
struct BinaryTreeNodeBase
{
    typedef T value_type;

    BinaryTreeNodeBase()
        : left_(0L), right_(0L) {}

    BinaryTreeNodeBase(const T& data)
        : left_(0L), right_(0L), data_(data) {}

    ~BinaryTreeNodeBase()
    {
        if (left_ != 0L) delete left_;
        if (right_ != 0L) delete right_;
    }

    T& Data()
    { return data_; }

    BinaryTreeNodeBase*& Left()
    { return left_; }

    BinaryTreeNodeBase*& Right()
    { return right_; }

private:
    T data_;

    BinaryTreeNodeBase* left_;
    BinaryTreeNodeBase* right_;
};


template <class T>
BinaryTreeNodeBase<T>* MakeNode(const T& data)
{
    return new BinaryTreeNodeBase<T>(data);
}


} // binary_tree
