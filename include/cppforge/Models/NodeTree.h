#pragma once

namespace cppforge::models {
template <typename T> struct NodeTree {
  NodeTree *left;
  NodeTree *right;
  T data;

  NodeTree(T data) : data{data}, left{nullptr}, right{nullptr} {}
};
} // namespace cppforge::models
