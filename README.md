# cpp-forge

A collection of custom data structures and core systems utilities implemented from scratch in C++. 

## Implemented Modules

| Implementation | Description |
| :--- | :--- |
| [**Vector`<T>`**](./include/cppforge/Vector.h) | A custom re-implementation of `std::vector` featuring its most popular methods |
| [**Stack`<T>`**](./include/cppforge/Stack.h) | A custom Last-In, First-Out (LIFO) stack container |
| [**Queue`<T>`**](./include/cppforge/Queue.h) | A custom First-In, First-Out (FIFO) queue container |

## How To Run

```bash
cmake -S . -B build
cmake --build build
./build/cpp-forge
```
