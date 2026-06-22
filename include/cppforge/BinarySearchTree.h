#pragma once

#include "cppforge/Models/NodeTree.h"
#include "cppforge/Stack.h"

using cppforge::models::NodeTree;

namespace cppforge {
template <typename T> class BinarySearchTree {
private:
  NodeTree<T> *root;

public:
  BinarySearchTree() : root{nullptr} {}

  BinarySearchTree(const BinarySearchTree<T> &bst) {
    cppforge::Stack<NodeTree<T> *> originalStack;
    cppforge::Stack<NodeTree<T> *> newTreeStack;
    NodeTree<T> *original = bst.root;
    NodeTree<T> *newTree = nullptr;
    bool isRight = false;
    while (original != nullptr || !newTreeStack.isEmpty()) {
      while (original != nullptr) {
        if (newTree == nullptr) {
          root = new NodeTree<T>(original->data);
          newTree = root;
        } else {
          if (!isRight) {
            newTree->left = new NodeTree<T>(original->data);
            newTree = newTree->left;
          } else {
            newTree->right = new NodeTree<T>(original->data);
            newTree = newTree->right;
            isRight = false;
          }
        }
        originalStack.push(original);
        newTreeStack.push(newTree);
        original = original->left;
      }
      original = originalStack.peek();
      newTree = newTreeStack.peek();
      if (original->right != nullptr) {
        original = original->right;
        isRight = true;
      } else
        original = nullptr;
      originalStack.pop();
      newTreeStack.pop();
    }
  }

  void insert(const T &value) {
    if (root == nullptr)
      root = new NodeTree<T>(value);
    else {
      NodeTree<T> *aux = root;
      while (1) {
        if (value == aux->data) {
          return;
        } else if (value < aux->data) {
          if (aux->left == nullptr) {
            aux->left = new NodeTree<T>(value);
            break;
          }
          aux = aux->left;
        } else {
          if (aux->right == nullptr) {
            aux->right = new NodeTree<T>(value);
            break;
          }
          aux = aux->right;
        }
      }
    }
  }

  void remove(const T &value) {
    if (root == nullptr)
      return;
    NodeTree<T> *front = root;
    NodeTree<T> *back = nullptr;
    while (front != nullptr && front->data != value) {
      back = front;
      if (front->data < value) {
        front = front->right;
      } else
        front = front->left;
    }
    if (front == nullptr)
      return;

    if (front->left == nullptr && front->right == nullptr) {
      if (back == nullptr) {
        root = nullptr;
      } else {
        if (back->left == front)
          back->left = nullptr;
        else
          back->right = nullptr;
      }
    } else if (front->left != nullptr && front->right != nullptr) {
      NodeTree<T> *newValue = front->right;
      NodeTree<T> *holdLeft = front->left;
      if (newValue->left != nullptr) {
        NodeTree<T> *aux = newValue;
        while (aux->left != nullptr) {
          aux = aux->left;
        }
        aux->left = holdLeft;
      } else
        newValue->left = holdLeft;
      if (back == nullptr)
        root = newValue;
      else {
        if (back->left == front)
          back->left = newValue;
        else
          back->right = newValue;
      }
    } else if (front->left != nullptr) {
      if (back == nullptr) {
        root = front->left;
      } else {
        if (back->left == front)
          back->left = front->left;
        else
          back->right = front->left;
      }
    } else if (front->right != nullptr) {
      if (back == nullptr) {
        root = front->right;
      } else {
        if (back->left == front)
          back->left = front->right;
        else
          back->right = front->right;
      }
    }
    delete front;
  }

  void clear() {
    if (root == nullptr)
      return;
    cppforge::Stack<NodeTree<T> *> stack;
    stack.push(root);
    while (!stack.isEmpty()) {
      NodeTree<T> *current = *stack.peek();
      stack.pop();
      if (current->right != nullptr)
        stack.push(current->right);
      if (current->left != nullptr)
        stack.push(current->left);
      delete current;
    }
    root = nullptr;
  }

  bool contains(const T &value) const {
    if (root == nullptr)
      return false;
    NodeTree<T> *aux = root;
    while (aux != nullptr) {
      if (aux->data == value)
        return true;
      else if (aux->data > value)
        aux = aux->left;
      else
        aux = aux->right;
    }
    return false;
  }

  const T *min() const {
    if (root == nullptr)
      return nullptr;
    NodeTree<T> *aux = root;
    while (aux->right != nullptr || aux->left != nullptr) {
      if (aux->left != nullptr)
        aux = aux->left;
      else
        aux = aux->right;
    }
    return &aux->data;
  }

  const T *max() const {
    if (root == nullptr)
      return nullptr;
    NodeTree<T> *aux = root;
    while (aux->right != nullptr || aux->left != nullptr) {
      if (aux->right != nullptr)
        aux = aux->right;
      else
        aux = aux->left;
    }
    return &aux->data;
  }

  friend std::ostream &operator<<(std::ostream &ostream,
                                  const BinarySearchTree<T> &bst) {
    if (bst.root != nullptr) {
      NodeTree<T> *aux = bst.root;
      cppforge::Stack<NodeTree<T> *> stack;
      while (aux != nullptr || !stack.isEmpty()) {
        while (aux != nullptr) {
          stack.push(aux);
          aux = aux->left;
        }
        aux = *stack.peek();
        ostream << aux->data << " ";
        stack.pop();
        aux = aux->right;
      }
    }
    return ostream;
  }

  ~BinarySearchTree() {}
};
} // namespace cppforge
