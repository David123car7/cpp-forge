#include "Vector.h"
#include <iostream>
#include <ostream>
#include <stdexcept>

namespace cppforge::vector {
template <typename T> class VectorManager {
private:
  Vector<T> *start;
  Vector<T> *end;

public:
  int size;
  VectorManager() : start{nullptr}, end{nullptr}, size{0} {}

  T *begin() {
    if (start != nullptr)
      return &start->data;
    return nullptr;
  }

  T *back() {
    if (end != nullptr)
      return &end->data;
    return nullptr;
  }

  void push_back(const T &data) {
    Vector<T> *x = new Vector<T>(data);
    if (this->start == nullptr)
      this->start = x;
    else {
      Vector<T> *aux = start;
      while (aux->next != nullptr) {
        aux = aux->next;
      }
      aux->next = x;
    }
    this->end = x;
    size++;
  }

  void pop_back() {
    if (size == 0)
      return;
    else if (size == 1) {
      delete start;
      this->start = nullptr;
      this->end = nullptr;
      size--;
      return;
    } else {
      Vector<T> *auxRight = start->next;
      Vector<T> *auxLeft = start;
      while (auxRight->next != nullptr) {
        auxLeft = auxLeft->next;
        auxRight = auxRight->next;
      }
      delete auxRight;
      auxLeft->next = nullptr;
      this->end = auxLeft;
      size--;
      return;
    }
  }

  void insert(unsigned int pos, const T &data) {
    if (pos > size)
      return;
    else if (pos == size) {
      push_back(data);
      return;
    }
    Vector<T> *aux = this->start;
    Vector<T> *x = new Vector<T>(data);
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

  void insert(unsigned int pos, int count, const T *data) {
    if (pos > size)
      return;
    int currentPos = pos;
    for (int i = 0; i < count; i++) {
      insert(currentPos, data[i]);
      currentPos++;
    }
  }

  void erase(unsigned int pos) {
    if (pos > size - 1)
      throw std::invalid_argument("Invalid position to remove");
    Vector<T> *aux = start;
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
        this->end = aux;
      } else {
        Vector<T> *del = aux->next;
        aux->next = del->next;
        this->end = del->next;
        delete del;
      }
    }
    size--;
  }

  void erase(unsigned int interval, unsigned int interval2) {
    if (interval2 > size - 1 || interval > interval2 || interval == interval2)
      throw std::invalid_argument("Invalid position to remove");
    int operations = interval2 - interval + 1;
    int currentOp = 0;
    int currentPos = 0;
    Vector<T> *aux = this->start;
    while (currentPos < interval) {
      aux = aux->next;
      currentPos++;
    }
    while (currentOp < operations) {
      erase(currentPos);
      currentOp++;
    }
  }

  void clear() {
    if (size == 0)
      return;
    Vector<T> *auxRight = start->next;
    Vector<T> *auxLeft = start;
    while (auxRight != nullptr) {
      delete auxLeft;
      auxLeft = auxRight;
      auxRight = auxRight->next;
    }
    delete auxLeft;
    this->size = 0;
    this->start = nullptr;
    this->end = nullptr;
  }

  const T &at(unsigned int index) const {
    if (index >= size)
      throw std::out_of_range("index is out_of_range");
    Vector<T> *aux = this->start;
    int currentPos = 0;
    while (currentPos < index) {
      aux = aux->next;
      currentPos++;
    }
    return aux->data;
  }

  T &at(unsigned int index) {
    if (index >= size)
      throw std::out_of_range("index is out_of_range");
    Vector<T> *aux = this->start;
    int currentPos = 0;
    while (currentPos < index) {
      aux = aux->next;
      currentPos++;
    }
    return aux->data;
  }

  const T &operator[](unsigned int index) const {
    Vector<T> *aux = this->start;
    int currentPos = 0;
    while (currentPos < index) {
      aux = aux->next;
      currentPos++;
    }
    return aux->data;
  }

  T &operator[](unsigned int index) {
    Vector<T> *aux = this->start;
    int currentPos = 0;
    while (currentPos < index) {
      aux = aux->next;
      currentPos++;
    }
    return aux->data;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const VectorManager<T> &vector) {
    Vector<T> *aux = vector.start;
    while (aux != nullptr) {
      os << aux->data;
      aux = aux->next;
    }
    return os;
  }

  VectorManager(const VectorManager<T> &vector) : VectorManager() {
    Vector<T> *aux = vector.start;
    while (aux != nullptr) {
      push_back(aux->data);
      aux = aux->next;
    }
  }

  ~VectorManager() { clear(); }
};
} // namespace cppforge::vector
