namespace cppforge {

template <typename T> struct Vector {
  Vector *next;
  T data;

  Vector(T data) : data{data}, next{nullptr} {}
};
} // namespace cppforge
