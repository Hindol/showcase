#include "binary_search_tree.h"
#include <iostream>


int main()
{
    int array[] = { 5, 2, 8, 6, 4, 1, 9, 0, 3, 7 };
    tree::BinarySearchTree<int> bst(array, array + 10);

    std::cout << bst << "\n";

    bst.Remove(6);
    std::cout << bst << "\n";

    bst.Remove(0);
    std::cout << bst << "\n";

    bst.Remove(9);
    std::cout << bst << "\n";

    return 0;
}
