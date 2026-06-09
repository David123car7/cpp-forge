#include "cppforge/Models/Node.h"
#include <iostream>
#include <ostream>
#include <stdexcept>

namespace cppforge::vector {
template <typename T> class VectorManager {
private:
  Node<T> *start;

public:
  int size;
  VectorManager() : start{nullptr}, size{0} {}

  // Adds a value to the end of the vector.
  void push_back(const T &data) {
    Node<T> *x = new Node<T>(data);
    if (this->start == nullptr)
      this->start = x;
    else {
      Node<T> *aux = start;
      while (aux->next != nullptr) {
        aux = aux->next;
      }
      aux->next = x;
    }
    size++;
  }

  // Removes a value at the end of the vector
  void pop_back() {
    if (size == 0)
      return;
    else if (size == 1) {
      delete start;
      this->start = nullptr;
      size--;
      return;
    } else {
      Node<T> *auxRight = start->next;
      Node<T> *auxLeft = start;
      while (auxRight->next != nullptr) {
        auxLeft = auxLeft->next;
        auxRight = auxRight->next;
      }
      delete auxRight;
      auxLeft->next = nullptr;
      size--;
      return;
    }
  }

  // Inserts a value in a given position
  void insert(unsigned int pos, const T &data) {
    if (pos > size)
      return;
    else if (pos == size) {
      push_back(data);
      return;
    }
    Node<T> *aux = this->start;
    Node<T> *x = new Node<T>(data);
    if (pos == 0) {
      if (aux == nullptr)
        this->start = x;
      else {
        x->next = this->start;
        this->start = x;
      }
    } else {
      int currentPos = 0;
      while (currentPos < pos - 1) {
        aux = aux->next;
        currentPos++;
      }
      x->next = aux->next;
      aux->next = x;
    }
    size++;
  }

  // Inserts a collection of values in a given position
  void insert(unsigned int pos, int count, const T *data) {
    if (pos > size)
      return;
    int currentPos = pos;
    for (int i = 0; i < count; i++) {
      insert(currentPos, data[i]);
      currentPos++;
    }
  }

  // Removes a value in a given position
  void erase(unsigned int pos) {
    if (pos > size - 1)
      throw std::invalid_argument("Invalid position to remove");
    Node<T> *aux = start;
    if (pos == 0) {
      start = start->next;
      delete aux;
    } else {
      int currentPos = 0;
      while (currentPos != pos - 1) {
        aux = aux->next;
        currentPos++;
      }
      if (pos == size - 1) {
        delete aux->next;
        aux->next = nullptr;
      } else {
        Node<T> *del = aux->next;
        aux->next = del->next;
        delete del;
      }
    }
    size--;
  }

  // Removes a collection of values belonging to a given interval of positions
  void erase(unsigned int interval, unsigned int interval2) {
    if (interval2 > size - 1 || interval > interval2 || interval == interval2)
      throw std::invalid_argument("Invalid position to remove");
    int operations = interval2 - interval + 1;
    int currentOp = 0;
    int currentPos = 0;
    Node<T> *aux = this->start;
    while (currentPos < interval) {
      aux = aux->next;
      currentPos++;
    }
    while (currentOp < operations) {
      erase(currentPos);
      currentOp++;
    }
  }

  // Removes all values in vector and resets all variables
  void clear() {
    if (size == 0)
      return;
    Node<T> *auxRight = start->next;
    Node<T> *auxLeft = start;
    while (auxRight != nullptr) {
      delete auxLeft;
      auxLeft = auxRight;
      auxRight = auxRight->next;
    }
    delete auxLeft;
    this->size = 0;
    this->start = nullptr;
  }

  // Gets a const reference of a value in a given position
  const T &at(unsigned int index) const {
    if (index >= size)
      throw std::out_of_range("index is out_of_range");
    Node<T> *aux = this->start;
    int currentPos = 0;
    while (currentPos < index) {
      aux = aux->next;
      currentPos++;
    }
    return aux->data;
  }

  // Gets a reference of a value in a given position
  T &at(unsigned int index) {
    if (index >= size)
      throw std::out_of_range("index is out_of_range");
    Node<T> *aux = this->start;
    int currentPos = 0;
    while (currentPos < index) {
      aux = aux->next;
      currentPos++;
    }
    return aux->data;
  }

  // Overloads index operator returning a const reference to the value
  const T &operator[](unsigned int index) const {
    Node<T> *aux = this->start;
    int currentPos = 0;
    while (currentPos < index) {
      aux = aux->next;
      currentPos++;
    }
    return aux->data;
  }

  // Overloads index operator returning a reference to the value
  T &operator[](unsigned int index) {
    Node<T> *aux = this->start;
    int currentPos = 0;
    while (currentPos < index) {
      aux = aux->next;
      currentPos++;
    }
    return aux->data;
  }

  // Overloads the << operator
  friend std::ostream &operator<<(std::ostream &os,
                                  const VectorManager<T> &vector) {
    Node<T> *aux = vector.start;
    while (aux != nullptr) {
      os << aux->data;
      aux = aux->next;
    }
    return os;
  }

  // Copy Constructor
  VectorManager(const VectorManager<T> &vector) : VectorManager() {
    Node<T> *aux = vector.start;
    while (aux != nullptr) {
      push_back(aux->data);
      aux = aux->next;
    }
  }

  // Destructor
  ~VectorManager() { clear(); }
};
} // namespace cppforge::vector
