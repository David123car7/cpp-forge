#include "cppforge/Queue.h"
#include <iostream>

int main() {
  cppforge::Queue<int> queue;
  queue.add(1);
  queue.add(2);
  std::cout << queue << "\n";
  std::cout << "Size: " << queue.size() << "\n";
  if (const int *first = queue.getFirst(); first != nullptr)
    std::cout << "First: " << *first << "\n";
  if (const int *last = queue.getLast(); last != nullptr)
    std::cout << "Last: " << *last << "\n";

  return 0;
}
