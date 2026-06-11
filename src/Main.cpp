#include "cppforge/Stack.h"
#include "cppforge/Vector.h"
#include <iostream>

int main() {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  if (const int *peek = stack.peek(); peek != nullptr)
    std::cout << "Top: " << *peek << "\n";
  std::cout << "Size: " << stack.size() << "\n";
  std::cout << stack;
  return 0;
}
