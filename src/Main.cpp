#include "cppforge/BinarySearchTree.h"
#include <iostream>

int main() {
  cppforge::BinarySearchTree<int> bst;
  bst.insert(10);
  bst.insert(5);
  bst.insert(13);
  bst.insert(7);
  bst.insert(3);
  bst.insert(79);
  bst.remove(3);
  bst.clear();
  std::cout << bst;
  return 0;
}
