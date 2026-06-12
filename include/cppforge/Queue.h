#pragma once

#include "cppforge/Models/Node.h"
#include <cstddef>
#include <ostream>

using cppforge::models::Node;

namespace cppforge {
template <typename T> class Queue {
private:
  Node<T> *first;
  Node<T> *last;

public:
  Queue() : first{nullptr}, last{nullptr} {}

  // Gets a pointer to the first element of the queue
  const T *getFirst() const {
    if (first == nullptr)
      return nullptr;
    else
      return &first->data;
  }

  // Gets a pointer to the last element of the queue
  const T *getLast() const {
    if (last == nullptr)
      return nullptr;
    else
      return &last->data;
  }

  // Adds a value on the end of the queue
  void add(const T &data) {
    Node<T> *x = new Node<T>(data);
    if (first == nullptr) {
      first = x;
      last = x;
    } else {
      last->next = x;
      last = x;
    }
  }

  // Removes a value from the start of the queue
  void pop() {
    if (isEmpty())
      return;

    if (first == last) {
      delete first;
      first = nullptr;
      last = nullptr;
    } else {
      Node<T> *aux = first->next;
      delete first;
      first = aux;
    }
  }

  // Clears the queue
  void clear() {
    while (!isEmpty())
      pop();
  }

  // Checks if the queue is empty
  bool isEmpty() { return first == nullptr; }

  // Gets the size of the queue
  size_t size() {
    if (isEmpty())
      return 0;
    else {
      size_t count = 0;
      Node<T> *aux = first;
      while (aux != nullptr) {
        count++;
        aux = aux->next;
      }
      return count;
    }
  }

  // Overloads the << operator
  friend std::ostream &operator<<(std::ostream &ostream,
                                  const Queue<T> &queue) {
    Node<T> *aux = queue.first;
    while (aux != nullptr) {
      ostream << aux->data;
      aux = aux->next;
    }
    return ostream;
  }

  // Destructor
  ~Queue() { clear(); }
};
} // namespace cppforge
