#pragma once

#include "cppforge/Models/Node.h"
#include <cstddef>
#include <iostream>
#include <ostream>

using cppforge::models::Node;

namespace cppforge {
template <typename T> class Stack {
private:
  Node<T> *top;

public:
  Stack() : top{nullptr} {}

  // Copy Constructor
  Stack(const Stack &stack) {
    if (stack.top == nullptr) {
      top = nullptr;
      return;
    }
    Node<T> *parameter = stack.top;
    top = new Node<T>(stack.top->data);
    Node<T> *x = top;
    while (parameter->next != nullptr) {
      parameter = parameter->next;
      x->next = new Node<T>(parameter->data);
      x = x->next;
    }
  }

  // Adds a value on the top of the stack
  void push(const T &value) {
    Node<T> *x = new Node<T>(value);
    x->next = top;
    top = x;
  }

  // Removes a value on the top of the stack
  void pop() {
    if (isEmpty())
      return;
    Node<T> *x = top;
    top = x->next;
    delete x;
  }

  // Clears stack
  void clear() {
    while (!isEmpty())
      pop();
  }

  // Gets the value on top of the stack
  const T *peek() const {
    if (isEmpty()) {
      return nullptr;
    }
    return &top->data;
  }

  T *peek() {
    if (isEmpty()) {
      return nullptr;
    }
    return &top->data;
  }

  // Checks if the stack is empty
  bool isEmpty() const { return top == nullptr; }

  // Gets the size of the stack
  size_t size() {
    if (isEmpty())
      return 0;
    Node<T> *x = top;
    size_t count = 0;
    while (x != nullptr) {
      count++;
      x = x->next;
    }
    return count;
  }

  // Overloads the << operator
  friend std::ostream &operator<<(std::ostream &ostream,
                                  const Stack<T> &stack) {
    Node<T> *x = stack.top; // how do i have acess to top?
    while (x != nullptr) {
      ostream << x->data;
      x = x->next;
    }
    return ostream;
  }

  // Destructor
  ~Stack() { clear(); }
};
} // namespace cppforge
