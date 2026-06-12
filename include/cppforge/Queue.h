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

  const T *getFirst() const {
    if (first == nullptr)
      return nullptr;
    else
      return &first->data;
  }

  const T *getLast() const {
    if (last == nullptr)
      return nullptr;
    else
      return &last->data;
  }

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

  void clear() {
    while (!isEmpty())
      pop();
  }

  bool isEmpty() { return first == nullptr; }

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

  friend std::ostream &operator<<(std::ostream &ostream,
                                  const Queue<T> &queue) {
    Node<T> *aux = queue.first;
    while (aux != nullptr) {
      ostream << aux->data;
      aux = aux->next;
    }
    return ostream;
  }

  ~Queue() { clear(); }
};
} // namespace cppforge
