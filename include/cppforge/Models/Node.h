namespace cppforge::models {

template <typename T> struct Node {
  Node *next;
  T data;

  Node(T data) : data{data}, next{nullptr} {}
};
} // namespace cppforge::models
