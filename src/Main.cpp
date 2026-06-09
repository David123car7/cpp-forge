#include "cppforge/VectorManager.h"
#include <iostream>

int main() {
  cppforge::vector::VectorManager<int> vector;
  vector.push_back(1);
  vector.push_back(2);

  std::cout << vector;
  return 0;
}
