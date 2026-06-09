#include "cppforge/VectorManager.h"
#include <iostream>

int main() {
  cppforge::vector::VectorManager<int> vector;
  vector.push_back(1);
  vector.push_back(2);

  std::cout << "Size: " << vector.size << "\n";
  if (vector.begin() != nullptr)
    std::cout << "Begin: " << *vector.begin() << "\n";
  if (vector.back() != nullptr)
    std::cout << "End: " << *vector.back() << "\n";
  std::cout << vector;
  return 0;
}
